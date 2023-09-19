#ifndef __L3GD20_H
#define __L3GD20_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "led.h"
#include "typedefs.h"

// INITIALIZATION OF SPI COMMUNICATION AND CALIBRATION
void L3GD20_Init(void);

int L3GD20_Update(void);

extern float Angle_Z;




	#ifdef __cplusplus
}
#endif

#endif
