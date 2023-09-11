#include "main.h"


/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;


TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;

void SystemClock_Config(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
volatile uint16_t adcResultsDMA[5];
int adcChannelCount = sizeof(adcResultsDMA) / sizeof(adcResultsDMA[0]);
volatile int adcConversionComplete = 0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000+4*n)))
uint16_t i = 0;
short z = 0;
short ad = 0;
int mouseState = 0;
bool LF = false;
bool RF = false;
bool LD = false;
bool RD = false;


/* USER CODE END 0 */



/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

 	HAL_Init();
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	ITM_Port32(31) = 1;
	/* USER CODE END SysInit */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI1_Init();
	MX_ADC1_Init();
	MX_SPI2_Init();
	MX_USART1_UART_Init();
	MX_TIM6_Init();
	MX_TIM14_Init();

	encoderInit();
	motorInit();

	/* USER CODE BEGIN 2 */
	printf("hello world\r\n");
	ITM_Port32(31) = 2;

//	L3GD20_Init();




//  UartInit();
//  GyroInit();

//	/* USER CODE END 2 */
//	HAL_TIM_Base_Start_IT(&htim2);
//	HAL_TIM_Base_Start_IT(&htim14);
//
//	hadc1.Instance = ADC1;
//	HAL_ADC_Init(&hadc1);
//	ADC_ChannelConfTypeDef sConfig = { 0 };
//
//	// Configure ADC channel 1
//	sConfig.Channel = 9; // Replace with your desired channel for the first measurement
//	sConfig.Rank = 1;
////    sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES;
//	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
//
//	// Configure ADC channel 2
//	sConfig.Channel = 4; // Replace with your desired channel for the second measurement
//	sConfig.Rank = 2; // You can change the rank to control the order of conversions
//	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
//
//	// Configure ADC channel 1
//	sConfig.Channel = 8; // Replace with your desired channel for the first measurement
//	sConfig.Rank = 3;
////    sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES;
//	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
//
//	// Configure ADC channel 2
//	sConfig.Channel = 14; // Replace with your desired channel for the second measurement
//	sConfig.Rank = 4; // You can change the rank to control the order of conversions
//	HAL_ADC_ConfigChannel(&hadc1, &sConfig);




	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
//		l_encoder_count = TIM2->CNT;
//		r_encoder_count = TIM5->CNT;
//		/* USER CODE END WHILE */
//
//		/* USER CODE BEGIN 3 */
////	  	z = DisplayAxisValues();
////	  	HAL_Delay(100);
////		L3GD20_loop();
////		HAL_Delay(1);
//		switch (mouseState) {
//
//		case 0:
//			mouseState = idle();
//			break;
//
//		case 1:
//			mouseState = searchIdle();
//			break;
//
//		case 2:
//			mouseState = searchForward();
//			break;
//
//		case 3:
//			mouseState = searchBackward();
//			break;
//
//		case 4:
//			mouseState = fastIdle();
//			break;
//
//		case 5:
//			mouseState = fastForward();
//			break;
//
//		case 6:
//			mouseState = fastBackward();
//			break;
//
//		case 7:
//			mouseState = speedAdjust();
//			break;
//
//		default:
//			break;
//		}
//		HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port, LF_EMITTER_Pin, GPIO_PIN_SET);
////		HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port, RF_EMITTER_Pin, GPIO_PIN_SET);
////		HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port, DIAGONAL_EMITTER_Pin, GPIO_PIN_SET);
//		HAL_Delay(1);
		printf("i value : %i\r\n", i);
		i = i + 1;
		setWheels(1,1);
		HAL_Delay(1000);
		setWheels(0,0);
		HAL_Delay(1000);
//		HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcResultsDMA, adcChannelCount);
//		adcConversionComplete = 0;
//		adcChannelCount = adcChannelCount;
//		HAL_Delay(1);
//		HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port, LF_EMITTER_Pin, GPIO_PIN_RESET);
//		HAL_Delay(1);
//		HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port, RF_EMITTER_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port, DIAGONAL_EMITTER_Pin, GPIO_PIN_SET);
//		HAL_Delay(100);



	}
	/* USER CODE END 3 */
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	if (htim == &htim14) {
//		HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcResultsDMA, adcChannelCount);
//		while (adcConversionComplete == 0) {
//
//		}
//		adcConversionComplete = 0;
//
//		if (adcResultsDMA[0] > 1000) {
//			LF = true;
//		} else {
//			LF = false;
//		}
//		if (adcResultsDMA[1] > 1000) {
//			RF = true;
//		} else {
//			RF = false;
//		}
//		if (adcResultsDMA[2] > 1000) {
//			LD = true;
//		} else {
//			LD = false;
//		}
//		if (adcResultsDMA[3] > 1000) {
//			RD = true;
//		} else {
//			RD = false;
//		}
//
//	}
//
//}

__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	/* Prevent unused argument(s) compilation warning */
	adcConversionComplete = 1;
//  UNUSED(hadc);
	/* NOTE : This function Should not be modified, when the callback is needed,
	 the HAL_ADC_ConvCpltCallback could be implemented in the user file
	 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == TB1_Pin) {
		switch (mouseState) {
		case 0: // Idle
			// Transition to Search state (2) on TB1 press
			mouseState = 1;
			HAL_Delay(1000);
			break;
		case 1: // Search
			// Transition to Fast state (3) on TB1 press
			mouseState = 4;
			HAL_Delay(1000);
			break;
		case 2: // Fast
			// Transition to Speed Adjustment state (4) on TB1 press
			mouseState = 4;
			HAL_Delay(1000);
			break;
		case 3: // Speed Adjustment
			// Transition back to Idle state (1) on TB1 press
			mouseState = 4;
			HAL_Delay(1000);
			break;
		case 4: // Search
			// Transition to Fast state (3) on TB1 press
			mouseState = 7;
			HAL_Delay(1000);
			break;
		case 5: // Fast
			// Transition to Speed Adjustment state (4) on TB1 press
			mouseState = 7;
			HAL_Delay(1000);
			break;
		case 6: // Speed Adjustment
			// Transition back to Idle state (1) on TB1 press
			mouseState = 7;
			HAL_Delay(1000);
			break;
		case 7: // Speed Adjustment
			// Transition back to Idle state (1) on TB1 press
			mouseState = 0;
			HAL_Delay(1000);
			break;
		}
	}
}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};
  ADC_InjectionConfTypeDef sConfigInjected = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 5;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_4;
  sConfigInjected.InjectedRank = 1;
  sConfigInjected.InjectedNbrOfConversion = 4;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_84CYCLES;
  sConfigInjected.ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONVEDGE_NONE;
  sConfigInjected.ExternalTrigInjecConv = ADC_INJECTED_SOFTWARE_START;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
  sConfigInjected.InjectedOffset = 0;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedRank = 2;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedRank = 3;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedRank = 4;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}


static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

static void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_1LINE;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}




/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void) {

	/* USER CODE BEGIN TIM6_Init 0 */

	/* USER CODE END TIM6_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM6_Init 1 */

	/* USER CODE END TIM6_Init 1 */
	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 0;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 65535;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM6_Init 2 */

	/* USER CODE END TIM6_Init 2 */

}

static void MX_TIM14_Init(void) {

	/* USER CODE BEGIN TIM14_Init 0 */

	/* USER CODE END TIM14_Init 0 */

	/* USER CODE BEGIN TIM14_Init 1 */

	/* USER CODE END TIM14_Init 1 */
	htim14.Instance = TIM14;
	htim14.Init.Prescaler = 8;
	htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim14.Init.Period = 65535;
	htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim14) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM14_Init 2 */

	/* USER CODE END TIM14_Init 2 */

}

static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}


void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
