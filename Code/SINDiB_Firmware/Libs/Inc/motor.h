/*
 * motor.h
 *
 *  Created on: Sep 11, 2023
 *      Author: SANJITH
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

void motorInit(void);
void setLeftWheel(float l_speed);
void setRightWheel(float r_speed);
void setWheels(float l_speed, float r_speed);
bool straightCounts(int count);
void goLong(int count);

#endif /* INC_MOTOR_H_ */
