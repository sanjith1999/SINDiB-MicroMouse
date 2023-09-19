#ifndef INC_PID_H_
#define INC_PID_H_

#include "motor.h"
#include "typedefs.h"
#include "encoder.h"
#include "L3GD20.h"

#define PID_RED_FACTOR 50


// ULTIMATE PID CONTROLLING STRATEGY
int PID_Controller(void);

// GOING STRAIGHT SPECIFIED DISTANCE
bool moveStraight(float dist_cm);


#endif /* INC_PID_H_ */
