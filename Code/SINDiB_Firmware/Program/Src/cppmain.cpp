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
	disp_state = DEFAULT;

	while (1)
	{
		i++;
		if (pointTurnLR(90))
			return 0;
		displayUpdate();
	}
}

int initialization_block(void)
{
	ALL_LED_ON;
	motorInit();
	encoderInit();
	displayInit();
	// buzzerInit();
	L3GD20_Init();
	PID_Controller(IDLE);

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
