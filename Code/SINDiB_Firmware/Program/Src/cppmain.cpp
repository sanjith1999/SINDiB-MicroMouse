/*
 MAIN FILE CONTAINING ALL OUR CODES
 TEAM: SINDiB
 AUTHOR: BIYON
 */
#include "cppmain.h"

u32 i,r_pos,l_pos;

bool buttonPress = false;

int mouseState = 2;


void cppmain(void) {
	LED1_ON;

	// INITIALIZATION OF HARDWARES
	motorInit();
	encoderInit();
	resetEncoder();
	ssd1306_Init();
	buzzerInit();

	ALL_LED_ON;
	HAL_Delay(1000);
	ALL_LED_OFF;
	HAL_Delay(1000);


//	straightCountsPID(dist);

	while (1) {
	
		l_pos = l_position;
		r_pos = r_position;
//		clearScreen();
//		printInt_font_6x8(LFSensor, 80, 10);
//		printInt_font_6x8(RFSensor, 2, 10);
//		printInt_font_6x8(DLSensor, 80, 24);
//		printInt_font_6x8(DRSensor, 2, 24);
//		HAL_Delay(500);

		// HAL_Delay(2000);
//		moveStraight(14.2);
//		HAL_Delay(1000);
//		turnGyroLR(90);
//		HAL_Delay(1000);
//		moveStraight(1.8);
		// HAL_Delay(100);


		mouseState = searchForward();

//		switch (mouseState) {
//
//		case 0:
//			mouseState = idle();
//			break;
//
//		case 1:
//			mouseState = searchIdle();
//			break;
//
//		case 2:
//			mouseState = searchForward();
//			break;
//
//		case 3:
//			mouseState = searchBackward();
//			break;
//
//		case 4:
//			mouseState = fastIdle();
//			break;
//
//		case 5:
//			mouseState = fastForward();
//			break;
//
//		case 6:
//			mouseState = fastBackward();
//			break;
//
//		case 7:
//			mouseState = speedAdjust();
//			break;
//
//		case 8:
//			mouseState = startPosChange();
//			break;
//
//		default:
//			break;
//		}

	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == TB1_Pin) {
		buttonPress = true;
	}
}






