#ifndef INC_CPPMAIN_H_
#define INC_CPPMAIN_H_

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"
#include "motor.h"
#include "encoder.h"
#include "L3GD20.h"
#include "sysModes.h"
#include "searchModes.h"
#include "fastModes.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

void cppmain(void);


#ifdef __cplusplus
}
#endif


#endif /* INC_LED_H_ */


