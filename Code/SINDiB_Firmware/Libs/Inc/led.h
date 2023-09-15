// DEDICATED FOR INITIALIZATION OF GPIO PINS AND

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

#define LF_EM_ON   HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port, LF_EMITTER_Pin, GPIO_PIN_SET)
#define LF_EM_OFF  HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port, LF_EMITTER_Pin, GPIO_PIN_RESET)
#define RF_EM_ON   HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port, RF_EMITTER_Pin, GPIO_PIN_SET)
#define RF_EM_OFF  HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port, RF_EMITTER_Pin, GPIO_PIN_RESET)
#define SIDE_EM_ON  HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port, DIAGONAL_EMITTER_Pin, GPIO_PIN_SET)
#define SIDE_EM_OFF HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port, DIAGONAL_EMITTER_Pin, GPIO_PIN_RESET)

#define LED1_ON    GPIO_SetBits(LED1_GPIO_Port, LED1_Pin)
#define LED1_OFF   GPIO_ResetBits(LED1_GPIO_Port, LED1_Pin)
#define LED2_ON    GPIO_SetBits(LED2_GPIO_Port, LED2_Pin)
#define LED2_OFF   GPIO_ResetBits(LED2_GPIO_Port, LED2_Pin)
#define LED3_ON    GPIO_SetBits(LED3_GPIO_Port, LED3_Pin)
#define LED3_OFF   GPIO_ResetBits(LED3_GPIO_Port, LED3_Pin)
#define LED4_ON    GPIO_SetBits(LED4_GPIO_Port, LED4_Pin)
#define LED4_OFF   GPIO_ResetBits(LED4_GPIO_Port, LED4_Pin)
#define LED5_ON    GPIO_SetBits(LED5_GPIO_Port, LED5_Pin)
#define LED5_OFF   GPIO_ResetBits(LED5_GPIO_Port, LED5_Pin)
#define LED6_ON    GPIO_SetBits(LED6_GPIO_Port, LED6_Pin)
#define LED6_OFF   GPIO_ResetBits(LED6_GPIO_Port, LED6_Pin)
#define LED7_ON    GPIO_SetBits(LED7_GPIO_Port, LED7_Pin)
#define LED7_OFF   GPIO_ResetBits(LED7_GPIO_Port, LED7_Pin)
#define LED8_ON    GPIO_SetBits(LED8_GPIO_Port, LED8_Pin)
#define LED8_OFF   GPIO_ResetBits(LED8_GPIO_Port, LED8_Pin)
#define LED9_ON    GPIO_SetBits(LED9_GPIO_Port, LED9_Pin)
#define LED9_OFF   GPIO_ResetBits(LED9_GPIO_Port, LED9_Pin)
#define LED10_ON    GPIO_SetBits(LED10_GPIO_Port, LED10_Pin)
#define LED10_OFF   GPIO_ResetBits(LED10_GPIO_Port, LED10_Pin)
#define LED11_ON    GPIO_SetBits(LED11_GPIO_Port, LED11_Pin)
#define LED11_OFF   GPIO_ResetBits(LED11_GPIO_Port, LED11_Pin)

#define ALL_LED_ON  LED1_ON; \
                    LED2_ON; \
					LED3_ON; \
					LED4_ON; \
					LED5_ON; \
					LED6_ON; \
                    LED7_ON; \
                    LED8_ON; \
					LED9_ON; \
					LED10_ON;\
					LED11_ON


#define ALL_LED_OFF LED1_OFF; \
                    LED2_OFF; \
                    LED3_OFF; \
					LED4_OFF; \
					LED5_OFF; \
					LED6_OFF; \
                    LED7_OFF; \
                    LED8_OFF; \
					LED9_OFF; \
					LED10_OFF;\
					LED11_OFF


#endif /* INC_LED_H_ */
