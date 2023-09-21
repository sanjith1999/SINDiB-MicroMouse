#include "PD.h"

// PID PARAMETERS FOR ANGULAR CONTROLLER
const float ACKp[] = {S1Kp_, S2Kp_};
const float ACKd[] = {S1Kd_, S2Kd_};
const int AC_RED[] = {AC_RED_S1_, AC_RED_S2_ * 10};

// PID PARAMETERS FOR SPEED CONTROLLER
const float SCKp[] = {1, 1};
const float SCKd[] = {1, .8};
const int SC_RED[] = {20, 30};        // 50

// VARIABLES
static u32 l_start = 0, r_start = 0; // STORE STARTING POSITION
static float start_angle = 0;

static float PD_correction_ac = 0, PD_correction_sc = 0,
			 a_last_error = 0, s_last_error; // STORE INTEGRAL ERROR

static int sc_counter = 0;

int angularController(AC_State ac_state)
{
	float a_error;
	float AC_Kp = ACKp[0], AC_Kd = ACKd[0], AC_RED_ = AC_RED[1];
	switch (ac_state)
	{
	// TERMINATION OPERATION
	case (IDLE):
		a_last_error = 0;
		break;

	// SPEED 1
	case (STRAIGHT_RUN):
		a_error = l_position, a_error -= r_position;
		break;

	// POINT-ROTATION
	case (POINT_TURN):
		a_error -= l_position, a_error -= r_position, a_error += (l_start + r_start); // a_error = -(l_position - l_start) - (r_position - r_start)
		break;
	}

	PD_correction_ac = (a_error * AC_Kp + (a_error - a_last_error) * AC_Kd) / (2 * AC_RED_);
	l_speed -= PD_correction_ac, r_speed += PD_correction_ac;
	a_last_error = a_error;

	return 0;
}

bool moveStraight(float dist_cm)
{
	LED1_ON;
	u32 counts_ = abs(dist_cm * LINEAR_SENSITIVITY);

	// STARTING POSITION ASSIGNMENT
	if (l_start == 0)
		l_start = l_position, r_start == r_position;

	// BASE SPEED ADJUSTMENT
	if (dist_cm > 0)
		l_speed = st_speed, r_speed = st_speed;
	else if (dist_cm == 0)
		l_speed = 0, r_speed = 0;
	else
		l_speed = -st_speed, r_speed = -st_speed;

	// THRESHOLDING
	if (abs(l_position - l_start) >= counts_ && abs(r_position - r_start) >= counts_)
	{
		l_start = 0, r_start = 0;
		STOP_ROBOT;
		angularController(IDLE);
		LED1_OFF;
		return true;
	}

	// REDUCING THE SPEED JUST BEFORE THE DESTINATION
	else if (abs(l_position - l_start) >= counts_ * .95)
		l_speed = l_speed / 2, r_speed = r_speed / 2;
	angularController(STRAIGHT_RUN);
	setWheels();
	return false;
}

bool pointTurnLR(float angle)
{
	float s_error = 0;

	if (start_angle == 0)
		LED2_ON,
			start_angle = angle_z, l_start = l_position, r_start = r_position,
			s_last_error = 0;

	s_error = (start_angle + angle) - angle_z;
	PD_correction_sc = (float)(s_error * SCKp[1] + (s_error - s_last_error) * SCKd[1]) / SC_RED[1];
	s_last_error = s_error;


	if (abs(PD_correction_sc) < 1e-8 && abs(s_error)<1e-2)
	{
		if (sc_counter < 10)
		{
			sc_counter++;
			HAL_Delay(20);
			return false;
		}
		// angularController(IDLE);
		LED2_OFF,
		start_angle = 0, l_start = 0, r_start = 0;
		resetEncoder();
		sc_counter = 0;
		return true;
	}
	
	if (abs(PD_correction_sc) > .3) PD_correction_sc = (PD_correction_sc > 0) ? .3 : -.3;
	l_speed = -PD_correction_sc, r_speed = +PD_correction_sc;
	// angularController(POINT_TURN);
	setWheels();
	return false;
}