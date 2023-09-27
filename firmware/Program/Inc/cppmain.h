#ifndef INC_CPPMAIN_H_
#define INC_CPPMAIN_H_



#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "floodfill.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"
#include "display.h"
#include "L3GD20.h"


#include "read_sensors.h"

#include "typedefs.h"
#include "ssd1306.h"
#include "buzzer.h"
#include "PD.h"

extern bool buttonPress;
extern int mouseState;
extern int runState;
extern int ORIENT;
extern char direction;


extern char back_path[ROWS*COLUMNS];
extern char fwd_path[ROWS*COLUMNS];
extern int ptr;

extern int backPtr;
extern int fwdPtr;


// MAIN LOOP
int cppmain(void);

// INITIALIZATION OF HARDWARE
int initialization_block(void);

// INTERRUPTS
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif


#endif /* INC_LED_H_ */


