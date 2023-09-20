/*
 MAIN FILE CONTAINING ALL OUR CODES
 TEAM: SINDiB
 AUTHOR: BIYON
 */
#include "cppmain.h"

u32 i;
bool buttonPress = false;
int mouseState = 0;


int cppmain(void)
{
	initialization_block();
	HAL_Delay(1000);
	disp_state = SENSOR_READ;

	while (1)
	{
		i++;
	}
}

int initialization_block(void)
{
	ALL_LED_ON;
	TIM1_START; ////////////////// CRUCIAL PART DON"T OFFFFFFFFFFFFFFFF ///////////////////////////
	TIM6_IT_START;

	motorInit();
	encoderInit();
	gyroInit();
	displayInit();
	// buzzerInit();
	PID_Controller(IDLE);

	ALL_LED_OFF;
	HAL_Delay(1000);
	gyroCalibration();
	disp_state = GYRO_CALIB;
	TIM14_IT_START;

	return 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(1000);
	if (GPIO_Pin == TB1_Pin)
	{
		buttonPress = true;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim14)
		readSensor();
	else if (htim == &htim13)
		gyroUpdate(),
			readSensor();
	else if (htim == &htim6)
		displayUpdate();
}
