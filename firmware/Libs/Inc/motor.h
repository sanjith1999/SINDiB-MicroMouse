#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "stdlib.h"
#include "parameters_.h"
#include "typedefs.h"

#define STOP_ROBOT \
    l_speed = 0;   \
    r_speed = 0;   \
    setWheels()

// GLOBAL VARIABLES
extern float l_speed,
    r_speed;

// BASE SPEEDS
extern float st_speed,
    rt_speed,
    al_speed;

// INITIALIZATION OF MOTOR
void motorInit(void);

// SET SPEED OF LEFT MOTOR
void setLeftWheel(float l_speed);

// SET SPEED OF RIGHT MOTOR
void setRightWheel(float r_speed);

// SET SPEED OF BOTH MOTOR
int setWheels();

#endif /* INC_MOTOR_H_ */
