#include "read_sensors.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//  if (htim == &htim14 )
//  {
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
//
//
//  }

  if (htim == &htim13){
		L3GD20_loop();
//		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
  }

}



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

