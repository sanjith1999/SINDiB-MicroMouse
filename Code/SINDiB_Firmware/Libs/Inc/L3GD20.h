#ifndef __L3GD20_H
#define __L3GD20_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "led.h"
#include "typedefs.h"
#include <stdint.h>
#include "main.h"
#include "parameters_.h"


#define AVERAGE_WINDOW_SIZE ((uint32_t)10u)
#define CALIBRATION_BUFFER_LENGTH ((uint32_t)2000u)

// INITIALIZATION OF SPI COMMUNICATION AND CALIBRATION
void L3GD20_Init(void);

// UPDATING ANGLE EVERY 1ms
int L3GD20_Update(void);

extern float angle_z;


#ifdef __cplusplus
}
#endif

#endif
