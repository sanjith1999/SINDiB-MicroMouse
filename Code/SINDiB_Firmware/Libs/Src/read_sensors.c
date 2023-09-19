#include "read_sensors.h"

int reflectionRate = 1000;//which is 1.000 (converted to ingeter)

int32_t volMeter=0;
float voltage = 0;
int32_t LFSensor = 0;
int32_t RFSensor = 0;
int32_t DLSensor=0;
int32_t DRSensor=0;

bool L = false;
bool R = false;
bool F = false;

/*read IR sensors*/
void readSensor(void)
{
	LED7_ON;

	__HAL_TIM_SET_COUNTER(&htim1,0);
	//read DC value	
	LFSensor = read_LF_Sensor;	
	RFSensor = read_RF_Sensor;	
	DLSensor = read_DL_Sensor;
	DRSensor = read_DR_Sensor;	
	
	
    //left front sensor
	LF_EM_ON;
	LFSensor = read_LF_Sensor - LFSensor;
	while(__HAL_TIM_GET_COUNTER(&htim1)<60);
	LF_EM_OFF;
	if(LFSensor < 0)//error check
		LFSensor = 0;
	while(__HAL_TIM_GET_COUNTER(&htim1)<140);

	//right front sensor
	RF_EM_ON;
	RFSensor = read_RF_Sensor - RFSensor;
	while(__HAL_TIM_GET_COUNTER(&htim1)<200);
	RF_EM_OFF;
	if(RFSensor < 0)
		RFSensor = 0;
	while(__HAL_TIM_GET_COUNTER(&htim1)<280);

    //diagonal sensors
	SIDE_EM_ON;
	while(__HAL_TIM_GET_COUNTER(&htim1)<340);
	DLSensor = read_DL_Sensor - DLSensor;
	DRSensor = read_DR_Sensor - DRSensor;
    SIDE_EM_OFF;
	if(DLSensor < 0)
		DLSensor = 0;
	if(DRSensor < 0)
		DRSensor = 0;
	// while(__HAL_TIM_GET_COUNTER(&htim1)<500);
	
	readVolMeter();
	
	LFSensor = LFSensor*reflectionRate/1000;
	RFSensor = RFSensor*reflectionRate/1000;
	DLSensor = DLSensor*reflectionRate/1000;
	DRSensor = DRSensor*reflectionRate/1000;
	
	LED7_OFF;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim14 )
  {
    readSensor();
  }
  if (htim == &htim13)
  {
	L3GD20_Update();
  }
}




/*read voltage meter*/
void readVolMeter(void)
{          //3240 = 7.85V
	volMeter = read_Vol_Meter;//raw value
	voltage = (volMeter*ADC_REF_VOL/4095)* 2.8;//actual voltage value  ex) 8.2V = 8200
}





bool irBlink() {
	static uint32_t t3 = 1000;
	if (LFSensor > t3 || RFSensor > t3) {
			return true;
		}
	return false;
}

bool rightIrBlink(){
	static uint32_t t2 = 1000;
	if (DRSensor > t2) {
			return true;
		}
	return false;
}

bool leftIrBlink(){
	static uint32_t t1 = 1000;
	if (DLSensor > t1) {
			return true;
		}
	return false;
}

void getSensorReadings() {
	static uint32_t t1 = 150;
	static uint32_t t2 = 100;

	if (DLSensor > t1 && DRSensor > t1 && DRSensor > t1 && RFSensor > t1){
		F = true;
		R = true;
		L = true;
	} else if (DLSensor > t1 && DRSensor > t1){
		F = false;
		R = true;
		L = true;
	} else if (LFSensor > t1 && DLSensor > t1){
		F = true;
		R = false;
		L = true;
	} else if (RFSensor > t1 && DRSensor > t1){
		F = true;
		R = true;
		L = false;
	} else if (DLSensor > t1){
		F = false;
		R = false;
		L = true;
	} else if (DRSensor > t1){
		F = false;
		R = true;
		L = false;
	} else if (RFSensor > t2 || LFSensor > t2){
		F = true;
		R = false;
		L = false;
	} else {
		F = false;
		R = false;
		L = false;
	}


}
