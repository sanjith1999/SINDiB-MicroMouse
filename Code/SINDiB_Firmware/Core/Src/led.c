#include "led.h"

// INITIALIZING GPIO PINS
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC,
			LED10_Pin | RF_EMITTER_Pin | D_C_Pin | DIAGONAL_EMITTER_Pin | CE_Pin
					| LF_EMITTER_Pin | CS_Pin | LED3_Pin | LED4_Pin | LED5_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LED11_Pin | LED9_Pin | LED8_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LED7_Pin | LED1_Pin | LED2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : TB1_Pin */
	GPIO_InitStruct.Pin = TB1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TB1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LED10_Pin RF_EMITTER_Pin D_C_Pin DIAGONAL_EMITTER_Pin
	 CE_Pin LF_EMITTER_Pin CS_Pin LED3_Pin
	 LED4_Pin LED5_Pin */
	GPIO_InitStruct.Pin = LED10_Pin | RF_EMITTER_Pin | D_C_Pin
			| DIAGONAL_EMITTER_Pin | CE_Pin | LF_EMITTER_Pin | CS_Pin | LED3_Pin
			| LED4_Pin | LED5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : RENCHA_Pin RENCHB_Pin DRDY_Pin LENCHA_Pin */
	GPIO_InitStruct.Pin = DRDY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB2 INT_Pin MISO_Pin LENCHB_Pin
	 BOOT0_Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_2 | INT_Pin | MISO_Pin | BOOT0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : LED11_Pin LED9_Pin LED8_Pin */
	GPIO_InitStruct.Pin = LED11_Pin | LED9_Pin | LED8_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : LED7_Pin LED1_Pin LED2_Pin */
	GPIO_InitStruct.Pin = LED7_Pin | LED1_Pin | LED2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : LED6_Pin */
	GPIO_InitStruct.Pin = LED6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED6_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}
