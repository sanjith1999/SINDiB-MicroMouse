#ifndef INC_READ_SENSORS_H_
#define INC_READ_SENSORS_H_


#include "main.h"
#include "led.h"
#include "typedefs.h"
#include "adc.h"
#include "motor.h"
#include "buzzer.h"
#include "parameters_.h"
#include "display.h"

#define ADC_REF_VOL 3.322

extern int reflectionRate;

extern float voltage;
extern int32_t LFSensor;
extern int32_t RFSensor;
extern int32_t DLSensor;
extern int32_t DRSensor;

extern bool L;
extern bool R;
extern bool F;

extern float averageL;
extern float averageR;
extern float averageFL;
extern float averageFR;


void readSensor(void);
void readVolMeter(void);

bool irBlink();
bool rightIrBlink();
bool leftIrBlink();
void getSensorReadings();
void stop_it_all(void);
void calculateAndSaveAverages();

#endif /* INC_READ_SENSORS_H_ */
