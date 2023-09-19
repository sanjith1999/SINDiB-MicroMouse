#include "PID.h"

const float STKp = 1.0; // PID PARAMETERS FOR STRAIGHT MOVEMENT
const float STKd = 0.8;
const float STKi = 0.1;

// VARIABLES
static unsigned long int start_l = 0, start_r = 0;		// STORE STARTING POSITION
static float PID_correction = 0, I = 0, last_error = 0; // STORE INTEGRAL ERROR
PID_State pid_state = IDLE;


int PID_Controller(void)
{
	float error;
	switch (pid_state)
	{
	case (IDLE):
		I = 0, last_error = 0;
		STOP_ROBOT;
		break;
	case (MOVE_STRAIGHT):
		error = l_position, error -= r_position;
		I = I + error;
		PID_correction = (error * STKp + I * STKi + (error - last_error) * STKd) / PID_RED_FACTOR;
		last_error = error;
		break;
	}
	return 0;
}

bool moveStraight(float dist_cm)
{
	if (start_l == 0)
		start_l = l_position;
	if (start_r == 0)
		start_r = r_position;

	if (abs(l_position - start_l) >= dist_cm * LINEAR_SENSITIVITY && abs(r_position - start_r) >= dist_cm * LINEAR_SENSITIVITY)
	{
		start_l = 0, start_r = 0;
		pid_state = IDLE;
		PID_Controller();
		return true;
	}
	pid_state = MOVE_STRAIGHT;
	PID_Controller();
	l_speed = (dist_cm > 0) ? base_l_speed - PID_correction : -base_l_speed - PID_correction, r_speed = (dist_cm > 0) ? base_r_speed + PID_correction : -base_r_speed + PID_correction;
	setWheels();
	return false;
}