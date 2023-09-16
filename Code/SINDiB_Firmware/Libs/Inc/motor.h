/*
 * motor.h
 *
 *  Created on: Sep 11, 2023
 *      Author: SANJITH
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "stdlib.h"

#define STOP_ROBOT setWheels(0,0)


void motorInit(void);
void setLeftWheel(float l_speed);
void setRightWheel(float r_speed);
void setWheels(float l_speed, float r_speed);
void moveStraight(float dist_cm);
void keepItPointed(float angle);
void turnGyroLR(float angle);
void AlignFrontRotate(float distance);
void cellTurnLeft();
void cellTurnRight();
void cellTurnBack();

//extern uint16_t pos_l, pos_r;

extern int l_start, r_start;
extern int l_dist, r_dist;
extern int error,  lastErr;
extern int I;
extern float correction;
extern int cnt;
extern float run_speed_l;
extern float run_speed_r;
extern float base_speed_l;
extern float base_speed_r;

#endif /* INC_MOTOR_H_ */
