/*
 * motor.h
 *
 *  Created on: Sep 11, 2023
 *      Author: SANJITH
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f4xx_hal.h"

void motorInit(void);
void setLeftWheel(float l_speed);
void setRightWheel(float r_speed);
void setWheels(float l_speed, float r_speed);


#endif /* INC_MOTOR_H_ */
