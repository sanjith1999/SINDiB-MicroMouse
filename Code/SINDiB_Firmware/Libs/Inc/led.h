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

#define LED1_ON    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED1_OFF   HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LED2_ON    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED2_OFF   HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#define LED3_ON    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET)
#define LED3_OFF   HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET)
#define LED4_ON    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET)
#define LED4_OFF   HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET)
#define LED5_ON    HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET)
#define LED5_OFF   HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET)
#define LED6_ON    HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET)
#define LED6_OFF   HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET)
#define LED7_ON    HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET)
#define LED7_OFF   HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET)
#define LED8_ON    HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET)
#define LED8_OFF   HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET)
#define LED9_ON    HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, GPIO_PIN_SET)
#define LED9_OFF   HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, GPIO_PIN_RESET)
#define LED10_ON    HAL_GPIO_WritePin(LED10_GPIO_Port, LED10_Pin, GPIO_PIN_SET)
#define LED10_OFF   HAL_GPIO_WritePin(LED10_GPIO_Port, LED10_Pin, GPIO_PIN_RESET)
#define LED11_ON    HAL_GPIO_WritePin(LED11_GPIO_Port, LED11_Pin, GPIO_PIN_SET)
#define LED11_OFF   HAL_GPIO_WritePin(LED11_GPIO_Port, LED11_Pin, GPIO_PIN_RESET)

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
