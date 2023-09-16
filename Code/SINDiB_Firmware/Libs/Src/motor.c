#include "motor.h"
#include "cppmain.h"
#include "L3GD20.h"

int max_limit = 65534;
float base_speed_l = 0.2;
float base_speed_r = 0.2;
const float StKp = 1.0;
const float StKi = 0.00;
const float StKd = 0.00;
const float RTKp = 1.0;
const float RTKd = 0.6;
const float RTKi = 0.1;

int l_start, r_start;
int l_dist, r_dist;
int error, lastErr;
int I;
int cnt = 0;
float correction = 0;
float run_speed_l;
float run_speed_r;

float min(float a, float b){
	return (a>b)? b:a;
}
float max(float a, float b){
	return (a>b)? a:b;
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

	l_speed = (l_speed == 0)? 0:((l_speed>0) ? min(l_speed,base_speed_l):max(l_speed,-base_speed_l));
	l_pwma = (l_speed >= 0) ? l_speed * max_limit : 0;
	l_pwmb = (l_speed < 0) ? (-l_speed) * max_limit : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, l_pwma); // LPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, l_pwmb); // LPWMB
}

void setRightWheel(float r_speed)
{
	uint16_t r_pwma, r_pwmb;

	r_speed = (r_speed==0)? 0: ((r_speed>0) ? min(r_speed,base_speed_r):max(r_speed,-base_speed_r));
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



void straightCountsPID(int count)
{

	l_start = l_position;
	r_start = r_position;

	while (1)
	{
		l_dist =  l_position - l_start;
		r_dist =  r_position - r_start ;

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
		if (thres && (abs(Angle_Z-angle) >  10.0))
		{
			l_dist = l_start - l_position;
			r_dist = -r_start + r_position;

			error = l_dist - r_dist;
			I = I + error;

			correction = (float)(error * StKp + I * StKi + (error - lastErr) * StKd) / 50.0;
			lastErr = error;

			setWheels(-(base_speed_l - correction), base_speed_r + correction );
		}
		else
		{
			thres = false;
			correction = .002;
			if (abs(correction)>.001 )
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
