#ifndef __L3GD20_H
#define __L3GD20_H

#include "led.h"
#include "typedefs.h"
#include <stdint.h>
#include "main.h"
#include "parameters_.h"


#define AVERAGE_WINDOW_SIZE ((uint32_t)10u)
#define CALIBRATION_BUFFER_LENGTH ((uint32_t)2000u)

extern float angle_z;
extern uint8_t gyro_identity;
extern u16 raw_z;

// INITIALIZATION OF SPI COMMUNICATION AND CALIBRATION
void gyroInit(void);

// UPDATING ANGLE EVERY 2ms
int gyroUpdate(void);

// READING GYRO VALUE
float readGyro(void);


#endif
