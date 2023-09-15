#include "read_sensors.h"

int reflectionRate = 1000;//which is 1.000 (converted to ingeter)

int32_t volMeter=0;
int32_t voltage = 0;
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
	u32 curt;
	
	//read DC value	
	LFSensor = read_LF_Sensor;	
	RFSensor = read_RF_Sensor;	
	DLSensor = read_DL_Sensor;
	DRSensor = read_DR_Sensor;	
	
	curt = micros();
	
    //left front sensor
	LF_EM_ON;
	elapseMicros(60,curt);
	LFSensor = read_LF_Sensor - LFSensor;
	LF_EM_OFF;
	if(LFSensor < 0)//error check
		LFSensor = 0;
 	elapseMicros(140,curt);

	//right front sensor
	RF_EM_ON;
	elapseMicros(200,curt);	
	RFSensor = read_RF_Sensor - RFSensor;
	RF_EM_OFF;
	if(RFSensor < 0)
		RFSensor = 0;
 	elapseMicros(280,curt);

    //diagonal sensors
	SIDE_EM_ON;
	elapseMicros(340,curt);	
	DLSensor = read_DL_Sensor - DLSensor;
	DRSensor = read_DR_Sensor - DRSensor;
    SIDE_EM_OFF;
	if(DLSensor < 0)
		DLSensor = 0;
	if(DRSensor < 0)
		DRSensor = 0;
	
	readVolMeter();
	
	LFSensor = LFSensor*reflectionRate/1000;
	RFSensor = RFSensor*reflectionRate/1000;
	DLSensor = DLSensor*reflectionRate/1000;
	DRSensor = DRSensor*reflectionRate/1000;
	
	// delay_us(80);
	// elapseMicros(500,curt);
}



/*read voltage meter*/
void readVolMeter(void)
{          //3240 = 7.85V
	volMeter = read_Vol_Meter;//raw value
	voltage = volMeter*809/3248;//actual voltage value  ex) 8.2V = 8200
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim14 )
  {
    readSensor();
  }
}



bool irBlink() {
	static uint32_t t3 = 76;
	if (LFSensor < t3 && RFSensor < t3) {
			return true;
		}
	return false;
}

bool rightIrBlink(){
	static uint32_t t2 = 32;
	if (DRSensor < t2) {
			return true;
		}
	return false;
}

bool leftIrBlink(){
	static uint32_t t1 = 32;
	if (DLSensor < t1) {
			return true;
		}
	return false;
}

void getSensorReadings() {
	static uint32_t t1 = 24;
	static uint32_t t2 = 32;
	static uint32_t t3 = 76;

	if (DLSensor > t1 && DRSensor > t2 && DRSensor < t3 && RFSensor < t3) {
		F = true;
		R = false;
		L = false;
	} else if (DLSensor > t1 && DRSensor < t2 && DRSensor > t3) {
		F = false;
		R = true;
		L = false;
	} else if (DLSensor < t1 && DRSensor > t2 && RFSensor > t3) {
		F = false;
		R = false;
		L = true;
	} else if (DLSensor > t1 && DRSensor < t2 && DRSensor < t3 && RFSensor < t3) {
		F = true;
		R = true;
		L = false;
	} else if (DLSensor < t1 && DRSensor > t2 && DRSensor < t3 && RFSensor < t3) {
		F = true;
		R = false;
		L = true;
	} else if (DLSensor < t1 && DRSensor < t2 && DRSensor > t3 && RFSensor > t3) {
		F = false;
		R = true;
		L = true;
	} else if (DLSensor < t1 && DRSensor < t2 && LFSensor < t3 && RFSensor < t3) {
		F = true;
		R = true;
		L = true;
	} else if (DLSensor > t1 && DRSensor > t2 && DRSensor > t3 && RFSensor > t3) {
		F = false;
		R = false;
		L = false;
	}
}
