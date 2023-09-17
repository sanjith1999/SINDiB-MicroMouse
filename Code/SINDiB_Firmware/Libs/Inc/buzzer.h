#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include "typedefs.h"
#include "melody.h"

#define OFF_BUZZ __HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 0)

void buzzerInit(void);
int setBuzz(u16 D, float amp);
void playSound(BUZZ_Tones tone_index);






#endif /* INC_BUZZER_H_ */
