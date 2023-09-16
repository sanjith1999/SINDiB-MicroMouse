/*
 * sysModes.cpp
 *
 *  Created on: Sep 8, 2023
 *      Author: SAMSUNG
 */
#include "sysModes.h"


void InitMouse() {

}

int idle() {

	while (1) {
		if (buttonPress) {
			buttonPress = false;
			break;
		}
	}
	return 1;
}

int speedAdjust() {
	while (1) {

		if (rightIrBlink()) {
			base_speed_l += 0.1;
			base_speed_r += 0.1;
		}
		if (leftIrBlink()) {
			base_speed_l -= 0.1;
			base_speed_r -= 0.1;
		}

		if (buttonPress) {
			buttonPress = false;
			return 8;
		}
		HAL_Delay(1000);
	}
}

int startPosChange() {
	while (1) {

		if (irBlink()) {
			if (startPos == 3){
				startPos = 0;
			} else {
				startPos += 1;
			}
		}

		if (buttonPress) {
			buttonPress = false;
			return 0;
		}
		HAL_Delay(1000);
	}
}
