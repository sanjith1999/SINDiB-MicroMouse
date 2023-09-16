#include "motor.h"
#include "cppmain.h"
#include "L3GD20.h"
#include "read_sensors.h"

int max_limit = 4095;
float base_speed_l = 0.2;
float base_speed_r = 0.2;

const lin_sens = 12.124;

const float lmax_speed = 0.3;
const float rmax_speed = 0.3;
const float StKp = 1.0;
const float StKi = 0.00;
const float StKd = 0.00;
const float RTKp = 1.0;
const float RTKd = 0.6;
const float RTKi = 0.1;

const float AlKp = 1.0;
const float AlKd = 0.9;
const float AlKi = 0.0;

const float Al1Kp = 1.0;
const float Al1Kd = 0.6;
const float Al1Ki = 0.0;

int l_start, r_start;
int l_dist, r_dist;
int error, lastErr, error1, lastErr1;
int I, I1;
int cnt = 0;
float correction = 0, correction1 = 0;
float run_speed_l;
float run_speed_r;

float min(float a, float b)
{
	return (a > b) ? b : a;
}
float max(float a, float b)
{
	return (a > b) ? a : b;
}

// INITIALIZATIONS
void motorInit(void)
{
	// Start PWM for TIM4 channels (you may need to adjust this based on your application)
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // LPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2); // LPWMB
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); // RPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4); // RPWMB
	setWheels(0, 0);
}

// LEFT WHEEL PLANNER
void setLeftWheel(float l_speed)
{
	uint16_t l_pwma, l_pwmb;

	if (abs(l_speed) > lmax_speed)
		l_speed = (l_speed > 0) ? lmax_speed : -lmax_speed;

	l_pwma = (l_speed >= 0) ? l_speed * max_limit : 0;
	l_pwmb = (l_speed < 0) ? (-l_speed) * max_limit : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, l_pwma); // LPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, l_pwmb); // LPWMB
}

void setRightWheel(float r_speed)
{
	uint16_t r_pwma, r_pwmb;

	if (abs(r_speed) > rmax_speed)
		r_speed = (r_speed > 0) ? rmax_speed : -rmax_speed;
	r_pwma = (r_speed >= 0) ? r_speed * max_limit : 0;
	r_pwmb = (r_speed < 0) ? (-r_speed) * max_limit : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, r_pwma); // RPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, r_pwmb); // RPWMB
}

void setWheels(float l_speed, float r_speed)
{
	setLeftWheel(l_speed);
	setRightWheel(r_speed);
}

void moveStraight(float dist_cm)
{
	int count = dist_cm*lin_sens;
	l_start = l_position;
	r_start = r_position;

	while (1)
	{
		l_dist = l_position - l_start;
		r_dist = r_position - r_start;

		error = l_dist - r_dist;
		I = I + error;

		correction = (float)(error * StKp + I * StKi + (error - lastErr) * StKd) / 50.0;
		lastErr = error;

		if (l_dist < count && r_dist < count)
		{
			setLeftWheel(base_speed_l - correction);
			setRightWheel(base_speed_r + correction);
		}
		else
		{
			STOP_ROBOT;
			break;
		}
	}
	//	return true;
}

void keepItPointed(float angle)
{
	while (1)
	{

		error = Angle_Z - angle;
		I = I + error;

		correction =
			(float)(error * StKp + I * StKi + (error - lastErr) * StKd) / 20.0;
		correction = (correction > .2) ? .2 : correction;
		lastErr = error;

		setLeftWheel(correction);
		setRightWheel(-correction);
	}
}

// TURN USING GYRO
void turnGyroLR(float angle)
{
	bool thres = true;
	TIM13_IT_START;
	LED6_ON;

	Angle_Z = 0;
	l_start = l_position;
	r_start = r_position;

	while (1)
	{
		if (thres && (abs(Angle_Z - angle) > 10.0))
		{
			l_dist = l_start - l_position;
			r_dist = -r_start + r_position;

			error = l_dist - r_dist;
			I = I + error;

			correction = (float)(error * StKp + I * StKi + (error - lastErr) * StKd) / 50.0;
			lastErr = error;

			setWheels(-(base_speed_l - correction), base_speed_r + correction);
		}
		else
		{
			thres = false;
			correction = .002;
			if (abs(correction) > .001)
			{
				error = Angle_Z - angle;
				I = I + error;

				correction = (float)(error * RTKp + I * RTKi + (error - lastErr) * RTKd) / 10;
				correction = (correction > base_speed_l) ? .2 : base_speed_l;
				lastErr = error;

				setWheels(-correction, correction);
			}
			else
			{
				STOP_ROBOT;
				break;
			}
		}
	}
	TIM13_IT_STOP;
	LED6_OFF;
}

void AlignFrontRotate(float distance)
{
	correction1 = 0.01;
	while (1)
	{
		error = LFSensor - RFSensor;
		I = I + error;

		correction = (float)(error * AlKp + I * Al1Ki + (error - lastErr) * AlKd) / 30.0;
		lastErr = error;

		error1 = distance - (float)((LFSensor + RFSensor) / 2);
		I1 = I1 + error1;

		correction1 = (float)(error1 * Al1Kp + I1 * Al1Ki + (error1 - lastErr1) * Al1Kd) /20.0;
		lastErr1 = error1;

		setLeftWheel(-correction + correction1);
		setRightWheel(correction + correction1);
	}

	STOP_ROBOT;
}

void cellTurnLeft(){
	moveStraight(14.2);
	HAL_Delay(1000);
	turnGyroLR(90);
	HAL_Delay(1000);
	moveStraight(1.8);
}

void cellTurnRight(){
	moveStraight(14.2);
	HAL_Delay(1000);
	turnGyroLR(-90);
	HAL_Delay(1000);
	moveStraight(1.8);
}

void cellTurnBack(){
	turnGyroLR(90);
	HAL_Delay(1000);
	turnGyroLR(90);
	HAL_Delay(1000);
	moveStraight(6.1);
}
