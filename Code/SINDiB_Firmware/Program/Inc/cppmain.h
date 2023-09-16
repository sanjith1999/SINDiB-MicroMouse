#ifndef INC_CPPMAIN_H_
#define INC_CPPMAIN_H_



#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"
#include "display.h"
#include "L3GD20.h"
#include "sysModes.h"
#include "searchModes.h"
#include "fastModes.h"
#include "read_sensors.h"
#include "typedefs.h"
#include "ssd1306.h"

extern bool buttonPress;

void cppmain(void);


#ifdef __cplusplus
}
#endif


#endif /* INC_LED_H_ */


