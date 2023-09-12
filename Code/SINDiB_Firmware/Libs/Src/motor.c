#include "motor.h"

uint16_t max_limit = 65534;
float base_speed = 0.2;

// INITIALIZATIONS
void motorInit(void){
	// Start PWM for TIM4 channels (you may need to adjust this based on your application)
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);  // LPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);  // LPWMB
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);  // RPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);  // RPWMB
	setWheels(0,0);
}

// LEFT WHEEL PLANNER
void setLeftWheel(float l_speed) {
	uint16_t l_pwma, l_pwmb;
	l_pwma = (l_speed>=0) ? l_speed * max_limit : 0;
	l_pwmb = (l_speed<0) ?(-l_speed) * max_limit: 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, l_pwma);  // LPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, l_pwmb);  // LPWMB
}

void setRightWheel(float r_speed){
	uint16_t r_pwma, r_pwmb;

	r_pwma = (r_speed>=0) ? r_speed * max_limit : 0;
	r_pwmb = (r_speed<0) ?(-r_speed) * max_limit: 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, r_pwma);  // RPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, r_pwmb);  // RPWMB
}


void setWheels(float l_speed, float r_speed){
	setLeftWheel(l_speed);
	setRightWheel(r_speed);
}

bool straightCounts(int count){
	uint16_t l_temp,r_temp;
	bool l_away=true,r_away = true;
	l_temp = l_position;
	r_temp = r_position;

	while(l_away || r_away){
		if (l_position - l_temp < count) setLeftWheel(base_speed);else {setLeftWheel(0);l_away= false;}
		if (r_position - r_temp < count) setRightWheel(base_speed);else {setRightWheel(0);r_away=false;}
	}
	return true;
}

void goLong(int count)
{
	for (int i =0;i<count/100;i++)straightCounts(100);
}




