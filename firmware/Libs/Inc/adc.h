#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <typedefs.h>
#include "main.h"

uint16_t readADC(adc_channels channel, uint8_t timeout);

// readADC (CHANNEL TO READ, TIMEOUT FOR CONVERSION)
#define read_Vol_Meter     readADC(BAT_VOL,1)
#define read_LF_Sensor     readADC(LF_RECEIVER,1)
#define read_RF_Sensor     readADC(RF_RECEIVER,1)
#define	read_DL_Sensor	   readADC(DL_RECEIVER,1)
#define read_DR_Sensor     readADC(DR_RECEIVER,1)


#endif /* INC_ADC_H_ */
