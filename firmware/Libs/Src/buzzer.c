#include "buzzer.h"

const float BUZZ_LOUDNESS = BUZZ_LOUDNESS_;  // SOUND LEVEL OF BUZZER
const int SLOW_FACTOR = 30;        // PARAMETER: BUZZER SOUND DURATION

void buzzerInit(void)
{
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
  playSound(TONE2);
}

int setBuzz(u16 freq, float amp)
{
  u16 period = 500000 / freq;
  TIM9->CNT = 0;
  TIM9->ARR = period - 1;
  __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, period * amp);
  return 0;
}

void playSound(BUZZ_Tones tone_index)
{
  int tone_ = 0;
  switch (tone_index)
  {
  case WIN_TONE:
    tone_ = 0;
    break;

  case TONE1:
    tone_ = 1;
    break;

  case TONE2:
    tone_ = 2;
    break;

  case TONE3:
    tone_ = 3;
    break;

  case TONE4:
    tone_ = 4;
    break;
  }
  for (int noteIndex = 0; noteIndex < melodySizes[tone_]; noteIndex++)
  {
    setBuzz(melody[tone_][noteIndex], BUZZ_LOUDNESS);
    HAL_Delay(noteDurations[tone_][noteIndex] * SLOW_FACTOR);
  }
  OFF_BUZZ;
}
