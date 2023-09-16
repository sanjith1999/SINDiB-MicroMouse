#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

#define OFF_BUZZER __HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 0)

void buzzerInit(void);
void setBuzPwm(u16 D);




#endif /* INC_BUZZER_H_ */
