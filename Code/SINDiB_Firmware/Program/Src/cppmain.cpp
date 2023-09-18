/*
 MAIN FILE CONTAINING ALL OUR CODES
 TEAM: SINDiB
 AUTHOR: BIYON
 */
#include "cppmain.h"

u32 i, r_pos, l_pos;

bool buttonPress = false;

int mouseState = 0;

void cppmain(void)
{
	initialization_block();
	disp_state = LOW_BAT;
	// playSound(WIN_TONE);
	while (1)
	{
	displayUpdate();
	HAL_Delay(500);
	}
}

int initialization_block(void){
	ALL_LED_ON;
	motorInit();
	encoderInit();
	displayInit();
	buzzerInit();


	TIM1_START;
	TIM14_IT_START;
	HAL_Delay(500);

	ALL_LED_OFF;
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
