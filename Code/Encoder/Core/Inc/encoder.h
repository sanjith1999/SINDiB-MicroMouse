// encoder.h

#ifndef ENCODER_H
#define ENCODER_H

#include "stm32f4xx_hal.h"

// Encoder signal change interrupt callback prototype
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif // ENCODER_H
