#include "buzzer.h"

// BUZZER INITIALIZATION
void buzzerInit(void){
    HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
    TIM9->CNT = 0;
}

// SETTING FREQUECY & AMPLITUDE
int setBuzz(u16 freq, float amp)
{
u16 period = 50000 / freq; 
TIM9->CNT = 0;
TIM9->ARR = period - 1;
TIM9->CCR2 = period*amp;
__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (int)amp*period);
return 0;
}


void playSound(void){

int melodyCount = 2;

  for(int melodyIndex = 0; melodyIndex < melodyCount; melodyIndex++)
  {
	  for(int noteIndex = 0; noteIndex < melodySizes[melodyIndex]; noteIndex++)
  	  {
	  	  setBuzz(melody[melodyIndex][noteIndex],.5);
	  	  HAL_Delay(noteDurations[melodyIndex][noteIndex] * melodySlowfactor[melodyIndex]*2);
  	  }
  }
}
