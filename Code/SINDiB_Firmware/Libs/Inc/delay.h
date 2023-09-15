#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "stdbool.h" //for bool
#include "typedefs.h"
#include "main.h"

// void Systick_Configuration(void);//initialize systick
void delay_ms(u32 nTime);
void delay_us(u32 nTime);
u32 micros(void);
u32 millis(void);
void elapseMicros(u32 targetTime, u32 oldt);
void elapseMillis(u32 targetTime, u32 oldt);

extern volatile u32 Millis;
extern volatile u32 Micros;

#define useExternalOSC 0     //true=1/false=0
#define systemFrequency 168   //MHz


#endif /* INC_DELAY_H_ */
