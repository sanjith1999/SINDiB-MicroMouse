#include "PD.h"

// VARIABLES
static u32 l_start = 0, r_start = 0; // STORE STARTING POSITION
static float start_angle = 0;

static MV_Type mv_type = IDLE;
static float dist_ang;

static float PD_correction_sc = 0, PD_correction_ac = 0, PD_correction_ir = 0;
static float sc_last_error = 0, ac_last_error = 0, ir_last_error = 0;

/////////////////////////////////////////////////// CONTROLLER /////////////////////////////////////////////////////////////////
bool finishMove(MV_Type mv_type_, float dist_ang_) //////////////////////////////////////// NO LOOP EXIT YET //////////////////////////////////////////
{
	mv_type = mv_type_, dist_ang = dist_ang_;

	// FIRST CALL
	if (l_start == 0)
	{
		l_start = l_position, r_start = r_position, start_angle = angle_z;
		(mv_type == STRAIGHT_RUN) ? LED1_ON : LED2_ON;
		sc_last_error = 0, ac_last_error = 0;
	}

	// DO ALL THE ADJUSTMENTS
	assignParameter();
	speedController();
	// angularController();

	// SET WHEEL
	l_speed = (mv_type == STRAIGHT_RUN) ? PD_correction_sc - PD_correction_ac : -PD_correction_ac - PD_correction_sc;
	r_speed = (mv_type == STRAIGHT_RUN) ? PD_correction_sc + PD_correction_ac : +PD_correction_ac + PD_correction_sc;
	setWheels();
	return false;
}

////////////////////////////////////////////////// PARAMETER CHOICE ///////////////////////////////////////////////////////////////
//  PARAMETERS
static float sc_kp = 1, sc_kd = 0, sc_red = 1e3;
static float ac_kp = 1, ac_kd = 0, ac_red = 1e3;
static int counts_ = 0; // CONVERTING ANGLE/ DISTANCE TO ENCODER COUNTS
static float speed_th_ = 0;

void assignParameter(void)
{
	switch (mv_type)
	{
	case STRAIGHT_RUN:
		speed_th_ = st_speed;
		counts_ = dist_ang * LINEAR_SENSITIVITY;
		if (st_speed == .25)
		{
			sc_kp = 1, sc_kd = .6, sc_red = 20;
			ac_kp = 1, ac_kd = .6, ac_red = 20;
		}
		else
		{
			sc_kp = 1, sc_kd = .6, sc_red = 20;
			ac_kp = 1, ac_kd = .6, ac_red = 20;
		}
		break;
	case POINT_TURN:
		counts_ = dist_ang * TURN_SENSITIVITY;
		speed_th_ = rt_speed;
		sc_kp = 1, sc_kd = .6, sc_red = 30;
		ac_kp = 1, ac_kd = .6, ac_red = 300;
		break;
	case IDLE:
		speed_th_ = 0;
		ac_red = 1e3, sc_red = 1e3;
		break;
	}
	return;
}
/////////////////////////////////////////////////// SPEED CONTROLLER /////////////////////////////////////////////////////////////
static float sc_error = 0;

void speedController(void)
{
	switch (mv_type)
	{
	case STRAIGHT_RUN:
		sc_error = l_start + r_start + 2 * counts_, sc_error -= l_position, sc_error -= r_position; // sc_error = (l_start + r_start + 2*counts_) - l_position - r_position
		break;

	case POINT_TURN:
		// ENCODER BASED TURN : sc_error  = (counts_ - (l_start - l_position)) + (counts_ - (r_position - r_start))
		// sc_error = 2*counts_ - l_start + r_start, sc_error += l_position, sc_error -=r_position;                                    // BACK UP : ENCODER BASED TURN
		// GYRO BASED TURN
		sc_error = (start_angle + dist_ang) - angle_z;
		break;

	case IDLE:
		PD_correction_sc = 0;
		break;
	}

	PD_correction_sc = (float)(sc_error * sc_kp + (sc_error - sc_last_error) * sc_kd) / sc_red;
	sc_last_error = sc_error;
	if (abs(PD_correction_sc) > speed_th_)
		PD_correction_sc = (PD_correction_sc > 0) ? .5 * speed_th_ : .5 * -speed_th_;
}

////////////////////////////////////////// ANGULAR CONTROLLER //////////////////////////////////////////////////////////
static float ac_error = 0;

void angularController(void)
{
	switch (mv_type)
	{

	// STRAIGHT RUN
	case (STRAIGHT_RUN):
		ac_error = l_position, ac_error -= r_position;
		break;

	// POINT-ROTATION
	case (POINT_TURN):
		ac_error += l_position, ac_error += r_position, ac_error -= (l_start + r_start); // a_error = (l_position - l_start) + (r_position - r_start)
		break;

	// AT THE END
	case (IDLE):
		ac_last_error = 0;
		break;
	}

	PD_correction_ac = (ac_error * ac_kp + (ac_error - ac_last_error) * ac_kd) / ac_red;
	ac_last_error = ac_error;
	if (abs(PD_correction_ac) > .3 * speed_th_)
		PD_correction_ac = (PD_correction_ac > 0) ? .3 * speed_th_ : -.3 * speed_th_;

	return;
}

///////////////////////////////////////////////////////  IR-CONTROLLER /////////////////////////////////////////////////////////////////////////////////
static float ir_error = 0;
static float ir_kp =1, ir_kd= 0, ir_red = 100;

void irController(void)
{
	ir_error = LFSensor - RFSensor;
	PD_correction_ir = (ir_error * ir_kp + (ir_error - ir_last_error) * ir_kd) / ir_red;
	ir_last_error = ir_error;
	l_speed = -PD_correction_ir;r_speed = PD_correction_ir;
	setWheels();
}