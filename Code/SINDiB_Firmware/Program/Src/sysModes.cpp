/*
 * sysModes.cpp
 *
 *  Created on: Sep 8, 2023
 *      Author: SAMSUNG
 */
//#include "sysModes.h"
#include "sysModes.h"

void InitMouse() {

}

int idle() {

	while (1) {
		if (HAL_GPIO_ReadPin(TB1_GPIO_Port, TB1_Pin)) {
			break;
		}
	}
	HAL_Delay(1000);
	return 1;
	//if button press return 1
}

int speedAdjust() {
	 while(1)
	 {
//	     if(leftIrBlink())
//	     {
//	         speed+=10;
//	     }
//	     if(RighIrBlink())
//	     {
//	         speed-=10;
//	     }
			if (HAL_GPIO_ReadPin(TB1_GPIO_Port, TB1_Pin)) {
				break;
			}

	 }
	 HAL_Delay(1000);
	 return 0;

}
