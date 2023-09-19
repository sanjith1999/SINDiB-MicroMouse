#include "motor.h"

uint16_t u12_max = 4095;
float l_speed, r_speed;
float base_l_speed = .4, base_r_speed = .4;

void motorInit(void)
{
	// Start PWM for TIM4 channels (you may need to adjust this based on your application)
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // LPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2); // LPWMB
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); // RPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4); // RPWMB
	STOP_ROBOT;
}

void setLeftWheel(float l_speed)
{
	uint16_t l_pwma, l_pwmb;

	if (abs(l_speed) > SPEED_THRESHOLD)
		l_speed = (l_speed > 0) ? SPEED_THRESHOLD : -SPEED_THRESHOLD;

	l_pwma = (l_speed < 0) ? (-l_speed) * u12_max : 0;
	l_pwmb = (l_speed >= 0) ? l_speed * u12_max : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, l_pwma); // LPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, l_pwmb); // LPWMB
}

void setRightWheel(float r_speed)
{
	uint16_t r_pwma, r_pwmb;

	if (abs(r_speed) > SPEED_THRESHOLD)
		r_speed = (r_speed > 0) ? SPEED_THRESHOLD : -SPEED_THRESHOLD;
	r_pwma = (r_speed < 0) ? (-r_speed) * u12_max : 0;
	r_pwmb = (r_speed >= 0) ? r_speed * u12_max : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, r_pwma); // RPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, r_pwmb); // RPWMB
}

int setWheels()
{
	setLeftWheel(l_speed);
	setRightWheel(r_speed);
	return 0;
}

