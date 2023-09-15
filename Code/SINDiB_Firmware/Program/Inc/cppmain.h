#ifndef INC_CPPMAIN_H_
#define INC_CPPMAIN_H_



#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <adc.h>
#include "motor.h"
#include "encoder.h"
#include "L3GD20.h"
#include "sysModes.h"
#include "searchModes.h"
#include "fastModes.h"
#include "read_sensors.h"
#include <typedefs.h>

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim14;

extern uint16_t pos_l, pos_r;

extern bool buttonPress;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern volatile uint16_t adcResultsDMA[5];
extern int adcChannelCount;
extern volatile int adcConversionComplete;

void cppmain(void);


#ifdef __cplusplus
}
#endif


#endif /* INC_LED_H_ */


