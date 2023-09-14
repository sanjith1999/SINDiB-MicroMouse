/*
 * sensors.h
 *
 *  Created on: Sep 13, 2023
 *      Author: SAMSUNG
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "stm32f4xx.h"
#include "main.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern volatile uint16_t adcResultsDMA[5];
extern int adcChannelCount;
extern volatile int adcConversionComplete;

extern uint32_t lf;
extern uint32_t rf;
extern uint32_t ld;
extern uint32_t rd;

extern bool L;
extern bool R;
extern bool F;

void getSensorReadings();
bool irBlink();
bool rightIrBlink();
bool leftIrBlink();


#define LF_EM_ON   HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port, LF_EMITTER_Pin, GPIO_PIN_SET)
#define LF_EM_OFF  HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port, LF_EMITTER_Pin, GPIO_PIN_RESET)
#define RF_EM_ON   HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port, RF_EMITTER_Pin, GPIO_PIN_SET)
#define RF_EM_OFF  HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port, RF_EMITTER_Pin, GPIO_PIN_RESET)
#define SIDE_EM_ON  HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port, DIAGONAL_EMITTER_Pin, GPIO_PIN_SET)
#define SIDE_EM_OFF HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port, DIAGONAL_EMITTER_Pin, GPIO_PIN_RESET)

#define systemFrequency 16   //MHz

#endif /* INC_SENSORS_H_ */
