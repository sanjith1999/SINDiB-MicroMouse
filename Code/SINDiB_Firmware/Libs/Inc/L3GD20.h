//#pragma once
//
//////////////////StringUtilities.h
//#define BASE_10  10
//
//char* IntegerToString(int value, char *result, int base);
//
///////////////UART.h
//void UartInit();
//void SendString(char* string);
//
/////////////////Gyro.h
//void GyroInit();
//short DisplayAxisValues();


#ifndef __L3GD20_H
#define __L3GD20_H

#ifdef __cplusplus
 extern "C" {
#endif




	 void L3GD20_Init(void);

	 void L3GD20_loop(void);

























	 #ifdef __cplusplus
}
#endif

#endif

