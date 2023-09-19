#include "PID.h"

// PID PARAMETERS FOR STRAIGHT MOVEMENT
const float STKp = STKp_, RTKp = RTKp_;
const float STKd = STKd_, RTKd = RTKd_;
const float STKi = STKi_, RTKi = RTKi_;
const int PID_RED_ST = PID_RED_ST_, PID_RED_RT = PID_RED_RT_;

// VARIABLES
static u32 start_l = 0, start_r = 0; // STORE STARTING POSITION
static float start_angle = 0;

static float PID_correction = 0, I = 0, last_error = 0; // STORE INTEGRAL ERROR

int PID_Controller(PID_State pid_state)
{
	float error;
	switch (pid_state)
	{
		error = l_position, error -= r_position;
		I = I + error;
	// TERMINATION OPERATION
	case (IDLE):
		I = 0, last_error = 0;
		STOP_ROBOT;
		break;

	// STRAIGHT MOVEMENT
	case (MOVE_STRAIGHT):
		PID_correction = (error * STKp + I * STKi + (error - last_error) * STKd) / PID_RED_ST;
		break;

	// POINT-ROTATION
	case (POINT_TURN):
		PID_correction = (error * RTKp + I * RTKi + (error - last_error) * RTKd) / PID_RED_RT;
		break;
	}
	l_speed -= PID_correction, r_speed += PID_correction;
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
	LED2_ON;
	TIM13_IT_START;
	start_angle = (start_angle == 0) ? angle_z : start_angle;

	if (abs(start_angle - angle_z) >= abs(angle-.1))
	{
		PID_Controller(IDLE);
		LED2_OFF;
		TIM13_IT_STOP;
		start_angle = 0;
		return true;
	}
	l_speed = (angle > 0) ? -rt_speed : rt_speed, r_speed = (angle > 0) ? rt_speed : -rt_speed;
	PID_Controller(POINT_TURN);
	setWheels();
	return false;
}