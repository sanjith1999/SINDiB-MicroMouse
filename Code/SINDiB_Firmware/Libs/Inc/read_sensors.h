#ifndef INC_READ_SENSORS_H_
#define INC_READ_SENSORS_H_


#include "main.h"
#include "led.h"
#include "typedefs.h"
#include "adc.h"

extern int reflectionRate;

extern int32_t volMeter;
extern int32_t voltage;
extern int32_t LFSensor;
extern int32_t RFSensor;
extern int32_t DLSensor;
extern int32_t DRSensor;

extern bool L;
extern bool R;
extern bool F;


void readSensor(void);
void readVolMeter(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
bool irBlink();
bool rightIrBlink();
bool leftIrBlink();
void getSensorReadings();

#endif /* INC_READ_SENSORS_H_ */
