#include "stm32f4xx_hal.h"
#include "encoder.h"
#include "main.h"
#include "globals.h"

// Encoder signal change interrupt callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	// right encoder
	if (GPIO_Pin == RENCHA_Pin) {
		// is it a falling edge?
		if (HAL_GPIO_ReadPin(RENCHA_GPIO_Port, RENCHA_Pin) == GPIO_PIN_RESET) {
			// is other channel (B) is high logic
			if (HAL_GPIO_ReadPin(RENCHB_GPIO_Port, RENCHB_Pin)
					== GPIO_PIN_SET) {
				right_encoderPosition++;
			}
		}
	}
	if (GPIO_Pin == RENCHB_Pin) {
		// is it a falling edge?
		if (HAL_GPIO_ReadPin(RENCHB_GPIO_Port, RENCHB_Pin) == GPIO_PIN_RESET) {
			// is other channel (A) is high logic
			if (HAL_GPIO_ReadPin(RENCHA_GPIO_Port, RENCHA_Pin)
					== GPIO_PIN_SET) {
				right_encoderPosition--;
			}
		}
	}

	// left encoder
	if (GPIO_Pin == LENCHA_Pin) {
		// is it a falling edge?
		if (HAL_GPIO_ReadPin(LENCHA_GPIO_Port, LENCHA_Pin) == GPIO_PIN_RESET) {
			// is other channel (B) is high logic
			if (HAL_GPIO_ReadPin(LENCHB_GPIO_Port, LENCHB_Pin)
					== GPIO_PIN_SET) {
				left_encoderPosition++;
			}
		}
	}
	if (GPIO_Pin == LENCHB_Pin) {
		// is it a falling edge?
		if (HAL_GPIO_ReadPin(LENCHB_GPIO_Port, LENCHB_Pin) == GPIO_PIN_RESET) {
			// is other channel (A) is high logic
			if (HAL_GPIO_ReadPin(LENCHA_GPIO_Port, LENCHA_Pin)
					== GPIO_PIN_SET) {
				left_encoderPosition--;
			}
		}
	}
}
