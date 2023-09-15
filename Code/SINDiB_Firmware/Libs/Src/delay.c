#include "delay.h"

/* define global variables, declarations are in stm32f4xx_it.c */
volatile u32 Micros;
volatile u32 Millis;


// void Systick_Configuration(void)
// {  
// 	SystemInit();
// 	SystemCoreClockUpdate();
	
// 	//systemFrequency = SystemCoreClock / 1000000;
// 	if (SysTick_Config (SystemCoreClock / 1000)) //1ms per interrupt
// 		while (1); 

// 	//set systick interrupt priority
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//4 bits for preemp priority 0 bit for sub priority
// 	NVIC_SetPriority(SysTick_IRQn, 0);
	  
// 	Millis = 0;//reset Millis
// }

u32 micros(void)
{
	Micros = Millis*1000 + 1000 - SysTick->VAL/systemFrequency;//=Millis*1000+(SystemCoreClock/1000-SysTick->VAL)/168;
	return Micros; 
}

u32 millis(void)
{
	return Millis;
}

void delay_ms(u32 nTime)
{
	u32 curTime = Millis;
	while((nTime-(Millis-curTime)) > 0);
}

void delay_us(u32 nTime)
{
	u32 curTime = micros();
	while((nTime-(micros()-curTime)) > 0);
}  

void elapseMicros(u32 targetTime, u32 oldt)
{
	while((micros()-oldt)<targetTime);
}


void elapseMillis(u32 targetTime, u32 oldt)
{
	while((millis()-oldt)<targetTime);
}


