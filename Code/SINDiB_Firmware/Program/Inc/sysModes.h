/*
 * sysModes.h
 *
 *  Created on: Sep 8, 2023
 *      Author: SAMSUNG
 */

#ifndef INC_SYSMODES_H_
#define INC_SYSMODES_H_

#include "main.h"
#include "floodfill.hpp"
#include "motor.h"
#include "cppmain.h"
#include "read_sensors.h"

void InitMouse();
int idle();
int speedAdjust();
int startPosChange();


#endif /* INC_SYSMODES_H_ */
