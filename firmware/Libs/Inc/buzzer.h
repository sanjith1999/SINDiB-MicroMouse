#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include "typedefs.h"
#include "melody.h"

#define OFF_BUZZ __HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 0)

// INITIALIZING BUZZER PWM CHANNEL
void buzzerInit(void);

// GIVING PWM OF CERTAIN FREQUENCY TO BUZZER
int setBuzz(u16 freq, float amp);

// SELECTING SOUND PATTERN TO PLAY IN BUZZER
void playSound(BUZZ_Tones tone_index);






#endif /* INC_BUZZER_H_ */
