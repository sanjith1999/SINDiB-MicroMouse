#include "buzzer.h"

void buzzerInit(void){
    HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
}

// 0 ---> 1000
void setBuzPWM(u16 D){
    __HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, D);
}


