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


	int dist = 170;
	ALL_LED_ON;
	HAL_Delay(1000);
	ALL_LED_OFF;

//	straightCountsPID(dist);

	while (1) {
		l_pos = l_position;
		r_pos = r_position;



//		turnGyro(0);
//		searchForward();


//		straightCountsPID(dist);
//		HAL_Delay(1000);

//		straightCountsPID(dist/2);
//		HAL_Delay(1000);
//		turnLeft(67);
//		HAL_Delay(1000);
//		straightCountsPID(dist/2);
//		HAL_Delay(1000);
//
//		straightCountsPID(dist/2);
//		HAL_Delay(1000);
//		turnRight(67);
//		HAL_Delay(1000);
//		straightCountsPID(dist/2);
//		HAL_Delay(1000);

//		turnLeftGyro(0);

		// goLong(500);

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
//		default:
//			break;
//		}
//		straightCountsPID(100);
//		HAL_Delay(1000);
//		turnLeft(67);
//		turnRight(67);
//		HAL_Delay(1000);
//		i++;
//		pos_l = l_position;
//		pos_r = r_position;
//		l_value = adcResultsDMA[0];
//		r_value = adcResultsDMA[1];


//		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
		i++;
//		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//		HAL_Delay(1000);
//		while(adcConversionComplete == 0){
//
//		}
//		adcConversionComplete = 0;
//		LF_EM_ON;
//		HAL_Delay(1000);
//		RF_EM_ON;
//		HAL_Delay(1000);
//		SIDE_EM_ON;
//		HAL_Delay(1000);
//
//		LF_EM_OFF;
//		HAL_Delay(1000);
//		RF_EM_OFF;
//		HAL_Delay(1000);
//		SIDE_EM_OFF;
//		HAL_Delay(1000);
//	    HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
//	    HAL_Delay(500);

	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == TB1_Pin) {
		buttonPress = true;
	}
}






