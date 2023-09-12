#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"

#define l_position TIM2-> CNT
#define r_position TIM5-> CNT

void encoderInit(void);
void encoderUpdate(void);
void resetEncoder(void);


#endif /* INC_ENCODER_H_ */
