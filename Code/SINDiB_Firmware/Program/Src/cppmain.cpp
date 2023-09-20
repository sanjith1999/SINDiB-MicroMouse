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
<<<<<<< HEAD
		// if (moveStraight(12))
		// 	HAL_Delay(2000);

		// testing the interrupt
		if (buttonPress){
			buttonPress = false;
			clearScreen();
			putString("button pressed",74,2,SMALL);
			HAL_Delay(1000);
			clearScreen();
		}
=======
>>>>>>> 0b259ad6052df66cd732286fc31aa10d4f561300
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
