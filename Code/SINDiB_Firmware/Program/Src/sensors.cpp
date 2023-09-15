///*
// * sensors.cpp
// *
// *  Created on: Sep 13, 2023
// *      Author: SAMSUNG
// */
#include "main.h"
#include "sensors.h"


volatile uint16_t adcResultsDMA[5],l_value,r_value;
int adcChannelCount = sizeof(adcResultsDMA) / sizeof(adcResultsDMA[0]);
volatile int adcConversionComplete = 0;

uint32_t sel = 0;

uint32_t lf;
uint32_t rf;
uint32_t ld;
uint32_t rd;

uint32_t curt;
volatile uint32_t Micros;
volatile uint32_t Millis;

uint32_t micros(void)
{
	Micros = Millis*1000 + 1000 - SysTick->VAL/systemFrequency;//=Millis*1000+(SystemCoreClock/1000-SysTick->VAL)/168;
	return Micros;
}

void elapseMicros(uint32_t targetTime, uint32_t oldt)
{
	while((micros()-oldt)<targetTime);
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  if (htim == &htim14 )
//  {
////	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
////	HAL_GPIO_TogglePin (LED1_GPIO_Port, LED1_Pin);
//
//	curt = micros();
//
//	if(sel==0){
//		LF_EM_ON;
//		elapseMicros(60,curt);
//		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
//		elapseMicros(260,curt);
//		lf = adcResultsDMA[2];//9
//		LF_EM_OFF;
//		sel = 1;
//
//	}
//	else if(sel==1){
//		RF_EM_ON;
//		elapseMicros(60,curt);
//		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
//		elapseMicros(260,curt);
//		rf = adcResultsDMA[0];//4
//		RF_EM_OFF;
//		sel = 2;
//
//	}
//	else if(sel==2){
//		SIDE_EM_ON;
//		elapseMicros(60,curt);
//		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
//		elapseMicros(260,curt);
//		rd = adcResultsDMA[4];//8
//		ld = adcResultsDMA[1];//14
//		SIDE_EM_OFF;
//		sel = 0;
//	}
//
//
////	RF_EM_ON;
////	elapseMicros(200,curt);
////	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
////	elapseMicros(280,curt);
////	rf = adcResultsDMA[0];//4
////	RF_EM_OFF;
//
//
////	SIDE_EM_ON;
////	HAL_Delay(1);
////	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcResultsDMA, adcChannelCount);
////	ld = adcResultsDMA[1];//8
////	rd = adcResultsDMA[4];//14
////	SIDE_EM_OFF;
////	HAL_Delay(1);
//
//
//
//  }
//
//}

//__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
//	/* Prevent unused argument(s) compilation warning */
//	adcConversionComplete = 1;
////  UNUSED(hadc);
//	/* NOTE : This function Should not be modified, when the callback is needed,
//	 the HAL_ADC_ConvCpltCallback could be implemented in the user file
//	 */
//}



bool F = false;
bool R = false;
bool L = false;

bool irBlink() {
	static uint32_t t3 = 76;
	if (lf < t3 && rf < t3) {
			return true;
		}
	return false;
}

bool rightIrBlink(){
	static uint32_t t2 = 32;
	if (rd < t2) {
			return true;
		}
	return false;
}

bool leftIrBlink(){
	static uint32_t t1 = 32;
	if (ld < t1) {
			return true;
		}
	return false;
}

void getSensorReadings() {
	static uint32_t t1 = 24;
	static uint32_t t2 = 32;
	static uint32_t t3 = 76;

	if (ld > t1 && rd > t2 && lf < t3 && rf < t3) {
		F = true;
		R = false;
		L = false;
	} else if (ld > t1 && rd < t2 && lf > t3) {
		F = false;
		R = true;
		L = false;
	} else if (ld < t1 && rd > t2 && rf > t3) {
		F = false;
		R = false;
		L = true;
	} else if (ld > t1 && rd < t2 && lf < t3 && rf < t3) {
		F = true;
		R = true;
		L = false;
	} else if (ld < t1 && rd > t2 && lf < t3 && rf < t3) {
		F = true;
		R = false;
		L = true;
	} else if (ld < t1 && rd < t2 && lf > t3 && rf > t3) {
		F = false;
		R = true;
		L = true;
	} else if (ld < t1 && rd < t2 && lf < t3 && rf < t3) {
		F = true;
		R = true;
		L = true;
	} else if (ld > t1 && rd > t2 && lf > t3 && rf > t3) {
		F = false;
		R = false;
		L = false;
	}
}
