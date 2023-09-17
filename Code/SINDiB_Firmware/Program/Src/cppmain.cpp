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
	LED1_ON;
	// INITIALIZATION OF HARDWARES
	// motorInit();
	// encoderInit();
	// resetEncoder();
	// ssd1306_Init();
	buzzerInit();

	ALL_LED_ON;
	HAL_Delay(1000);
	ALL_LED_OFF;
	HAL_Delay(1000);


	while (1)
	{
		
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	clearScreen();
	printString_font_6x8("Interrupt", 80, 0);
	HAL_Delay(1000);
	if (GPIO_Pin == TB1_Pin)
	{
		buttonPress = true;
	}
}
