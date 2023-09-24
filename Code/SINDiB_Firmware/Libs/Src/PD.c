#include "PD.h"

// VARIABLES
static u32 l_start = 0, r_start = 0, previous_time = 0, current_time = 0, last_exit_time = 0; // STORE STARTING POSITION
static float start_angle = 0;

static MV_Type mv_type = IDLE;
static float dist_ang;

static float PD_correction_sc = 0, PD_correction_ac = 0, PD_correction_ir = 0;
static float sc_last_error = 0, ac_last_error = 0, ir_last_error = 0;

/////////////////////////////////////////////////// CONTROLLER /////////////////////////////////////////////////////////////////
static int fm_counter = 0;
const float TERMINATION_TH = 4e-2;

bool finishMove(MV_Type mv_type_, float dist_ang_)
{
	mv_type = mv_type_, dist_ang = dist_ang_;
	current_time = HAL_GetTick();

	// FIRST CALL
	if (l_start == 0)
	{
		l_start = l_position, r_start = r_position, start_angle = angle_z;
		(mv_type == STRAIGHT_RUN) ? LED1_ON : ((mv_type == POINT_TURN) ? LED2_ON : LED3_ON);
		sc_last_error = 0, ac_last_error = 0, fm_counter = 0;
		previous_time = current_time;
		assignParameters();
		return false;
	}

	// CORRECTIONS
	speedController();

	//	 TERMINATION CODITION
	if (fabs(PD_correction_sc) < fabs(TERMINATION_TH) || (last_exit_time - current_time) > 300)
	{
		if (fm_counter > 5)
		{
			l_start = 0, r_start = 0;
			fm_counter = 0;
			(mv_type == STRAIGHT_RUN) ? LED1_OFF : ((mv_type == POINT_TURN) ? LED2_OFF : LED3_OFF);
			return true;
		}
		fm_counter++;
		last_exit_time = current_time;
		HAL_Delay(20);
	}

	// SET WHEEL
	switch (mv_type)
	{
	case STRAIGHT_RUN:
		l_speed = PD_correction_sc - PD_correction_ac + PD_correction_ir;
		r_speed = PD_correction_sc + PD_correction_ac - PD_correction_ir;
		break;
	case POINT_TURN:
		l_speed = -PD_correction_sc + PD_correction_ac;
		r_speed = +PD_correction_sc - PD_correction_ac;
		break;
	case FRONT_ALIGN:
		l_speed = PD_correction_sc - PD_correction_ac;
		r_speed = PD_correction_sc + PD_correction_ac;
		break;
	}
	setWheels();
	previous_time = current_time;
	return false;
}

////////////////////////////////////////////////// PARAMETER CHOICE ///////////////////////////////////////////////////////////////
//  PARAMETERS
static float sc_kp = 0, sc_kd = 0, sc_red = 1e3;
static float ac_kp = 0, ac_kd = 0, ac_red = 1e3;
static float counts_ = 0; // CONVERTING ANGLE/ DISTANCE TO ENCODER COUNTS
static float speed_th_ = 0;

void assignParameters(void)
{
	switch (mv_type)
	{
	case IDLE:
		sc_red = 1e5, ac_red = 1e5;
		break;

	case STRAIGHT_RUN:
		speed_th_ = st_speed;
		counts_ = dist_ang * LINEAR_SENSITIVITY;

		if (fabs(st_speed - 0.3) < .1)
		{
			sc_kp = 1, sc_kd = 5e-3, sc_red = 100;
			ac_kp = 1.1, ac_kd = 5e-3, ac_red = 10;
		}
		else
		{
			sc_kp = 1, sc_kd = 1e-2, sc_red = 90;
			ac_kp = 1.2, ac_kd = 1e-3, ac_red = 2;
		}
		break;

	case POINT_TURN:
		counts_ = dist_ang * TURN_SENSITIVITY;
		speed_th_ = rt_speed;

		sc_kp = 1.2, sc_kd = 2e-3, sc_red = 70; // 2e-3
		ac_kp = 1, ac_kd = 3e-3, ac_red = 100;
		break;

	case FRONT_ALIGN:
		speed_th_ = al_speed;
		counts_ = 320;
		sc_kp = 1, sc_kd = 0, sc_red = 100;
		ac_kp = 1, ac_kd = 0, ac_red = 150;
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
	case IDLE:
		sc_error = 0;
		break;

	case STRAIGHT_RUN:
		sc_error = l_start + r_start + 2 * counts_, sc_error -= l_position, sc_error -= r_position; // sc_error = (l_start + r_start + 2*counts_) - l_position - r_position
		break;

	case POINT_TURN:
		// ENCODER BASED TURN : sc_error  = (counts_ - (l_start - l_position)) + (counts_ - (r_position - r_start))
		// sc_error = 2*counts_ - l_start + r_start, sc_error += l_position, sc_error -=r_position;                                    // BACK UP : ENCODER BASED TURN
		// GYRO BASED TURN
		sc_error = (start_angle + dist_ang) - angle_z;
		break;

	case FRONT_ALIGN:
		sc_error = counts_ - (float)(LFSensor + RFSensor) / 2;
		break;
	}

	PD_correction_sc = (float)(sc_kp * sc_error + sc_kd * 1e3 * (sc_error - sc_last_error) / (current_time - previous_time)) / sc_red;
	sc_last_error = sc_error;
	if (fabs(PD_correction_sc) > speed_th_)
	{
		PD_correction_sc = (PD_correction_sc > 0) ? speed_th_ : -speed_th_;
		if (irController())
		{
			PD_correction_ac = 0;
			irController();
		}
		else
		{
			PD_correction_ir = 0;
			angularController();
		}
		return;
	}
	PD_correction_ac = 0;
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
		ac_error = r_position, ac_error += l_position, ac_error -= (l_start + r_start), ac_error = (float)ac_error; // a_error = (l_position - l_start) + (r_position - r_start)
		break;

	// AT THE END
	case (FRONT_ALIGN):
		ac_error = (LFSensor - RFSensor) / 10;
		break;
	}

	PD_correction_ac = (ac_kp * ac_error + sc_kd * 1e3 * (sc_error - sc_last_error) / (current_time - previous_time)) / ac_red;
	ac_last_error = ac_error;
	if (fabs(PD_correction_ac) > .6 * speed_th_)
		PD_correction_ac = (PD_correction_ac > 0) ? .5 * speed_th_ : -.5 * speed_th_;

	return;
}

///////////////////////////////////////////////////////  IR-CONTROLLER /////////////////////////////////////////////////////////////////////////////////
static float ir_error = 0;
static float ir_kp = 1, ir_kd = 0, ir_red = 100;
const float MIDDLE_VALUE_DL = 160;

bool twoWalls(void)
{
	if (((averageL - 500) * (averageL - 2000) < 0) && ((averageR - 500) * (averageR - 2000) < 0))
		return true;
	return false;
}

bool leftwall(void)
{
	if ((averageL - 500) * (averageR - 2000) < 0)
		return true;
	return false;
}

bool rightWall(void)
{
	if ((averageR - 500) * (averageR - 2000) < 0)
		return true;
	return false;
}

// DL SENSOR ALIGNMENT
bool irController(void)
{
	if ((mv_type != STRAIGHT_RUN))
	{
		if (twoWalls())
			ir_error = averageL - averageR;
		else if (leftWall())
			ir_error = 2 * (averageL - MIDDLE_VALUE_DL);
		else if (rightWall())
			ir_error = 2 * (MIDDLE_VALUE_DL - averageR);
		else
			return false;
		PD_correction_ir = (ir_kp * ir_error + ir_kd * 1e3 * (ir_error - ir_last_error) / (current_time - previous_time)) / ir_red;
		ir_last_error = ir_error;
		return true;
	}
	PD_correction_ir = 0;
	return false;
}
