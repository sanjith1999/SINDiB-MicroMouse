#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "stdlib.h"

#define SPEED_THRESHOLD 0.5
#define STOP_ROBOT \
    l_speed = 0;   \
    r_speed = 0;   \
    setWheels()

// GLOBAL VARIABLES
extern float l_speed,
    r_speed;

// BASE SPEEDS
extern float base_l_speed,
    base_r_speed;

// INITIALIZATION OF MOTOR
void motorInit(void);

// SET SPEED OF LEFT MOTOR
void setLeftWheel(float l_speed);

// SET SPEED OF RIGHT MOTOR
void setRightWheel(float r_speed);

// SET SPEED OF BOTH MOTOR
int setWheels();

#endif /* INC_MOTOR_H_ */
