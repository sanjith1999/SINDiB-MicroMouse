#ifndef INC_PD_H_
#define INC_PD_H_

#include "motor.h"
#include "typedefs.h"
#include "encoder.h"
#include "L3GD20.h"
#include "parameters_.h"
#include "led.h"
#include "main.h"
#include "read_sensors.h"

// ULTIMATE PID CONTROLLING STRATEGY
bool finishMove(MV_Type mv_type_, float dist_ang);

void assignParameters(void);

void speedController(void);
void angularController(void);
void irController(void);

#endif /* INC_PD_H_ */
