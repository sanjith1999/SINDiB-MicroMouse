#ifndef INC_PID_H_
#define INC_PID_H_

#include "motor.h"
#include "typedefs.h"
#include "encoder.h"
#include "L3GD20.h"
#include "parameters_.h"
#include "led.h"
#include "main.h"


// ULTIMATE PID CONTROLLING STRATEGY
int PID_Controller(PID_State pid_state);

// GOING STRAIGHT SPECIFIED DISTANCE
bool moveStraight(float dist_cm);

// TAKING A TURN AT THE POINT - L-PRIORATIZED
bool pointTurnLR(float angle);

#endif /* INC_PID_H_ */
