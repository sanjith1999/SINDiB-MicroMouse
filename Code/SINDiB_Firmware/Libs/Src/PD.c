#include "PD.h"

// PID PARAMETERS FOR STRAIGHT MOVEMENT
const float Kp[] = {STKp_, RTKp_};
const float Kd[] = {STKd_, RTKd_};
const int PD_RED_ST = PD_RED_ST_, PD_RED_RT = PD_RED_RT_;

// VARIABLES
static u32 start_l = 0, start_r = 0; // STORE STARTING POSITION
static float start_angle = 0;

static float PD_correction = 0, last_error = 0; // STORE INTEGRAL ERROR

int PD_Controller(PD_State pd_state)
{
	float error;
	error = l_position, error -= r_position;
	switch (pd_state)
	{
	// TERMINATION OPERATION
	case (IDLE):
		last_error = 0;
		STOP_ROBOT;
		break;

	// STRAIGHT MOVEMENT
	case (MOVE_STRAIGHT):
		PD_correction = (error * Kp[0] + (error - last_error) * Kd[0]) / PD_RED_ST;
		break;

	// POINT-ROTATION
	case (POINT_TURN):
		PD_correction = (error * Kp[1] + (error - last_error) * Kd[1]) / PD_RED_RT;
		break;
	}

	l_speed -= PD_correction, r_speed += PD_correction;
	last_error = error;

	return 0;
}

bool moveStraight(float dist_cm)
{
	LED1_ON;
	u32 counts_ = abs(dist_cm * LINEAR_SENSITIVITY);
	start_l = (start_l == 0) ? l_position : start_l;
	start_r = (start_r == 0) ? r_position : start_r;
	l_speed = (dist_cm > 0) ? st_speed : -st_speed, r_speed = (dist_cm > 0) ? st_speed : -st_speed;

	if (abs(l_position - start_l) >= counts_ && abs(r_position - start_r) >= counts_)
	{
		start_l = 0, start_r = 0;
		PID_Controller(IDLE);
		LED1_OFF;
		return true;
	}

	// REDUCING THE SPEED JUST BEFORE THE DESTINATION
	else if (abs(l_position - start_l) >= counts_ * .95)
		l_speed = l_speed / 2, r_speed = r_speed / 2;
	PID_Controller(MOVE_STRAIGHT);
	setWheels();
	return false;
}

bool pointTurnLR(float angle)
{
	if (start_angle == 0)
		LED2_ON, TIM13_IT_START, TIM14_IT_STOP, start_angle = angle_z;

	if (abs(start_angle - angle_z) >= abs(angle - .1))
	{
		PD_Controller(IDLE);
		LED2_OFF;
		TIM13_IT_STOP, TIM14_IT_START;
		start_angle = 0;
		return true;
	}
	l_speed = (angle > 0) ? -rt_speed : rt_speed, r_speed = (angle > 0) ? rt_speed : -rt_speed;
	PD_Controller(POINT_TURN);
	setWheels();
	return false;
}