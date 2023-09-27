#ifndef __L3GD20_H
#define __L3GD20_H

#include "led.h"
#include "typedefs.h"
#include <stdint.h>
#include "main.h"
#include "parameters_.h"
#include <math.h>


#define BUFFER_LENGTH ((u32)1000u)  // 1000u

extern float angle_z;
extern uint8_t gyro_identity;
extern float offset, noise;

// INITIALIZATION OF SPI COMMUNICATION AND CALIBRATION
void gyroInit(void);

// UPDATING ANGLE EVERY 2ms
int gyroUpdate(void);

// READING GYRO VALUE
int16_t readGyro(void);

// CALIBRATION IN THE BEGINNING
void gyroCalibration(void);


#endif
