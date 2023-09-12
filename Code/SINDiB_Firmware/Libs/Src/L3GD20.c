

//#include "RegisterAddresses.h"
//#include "main.h"
//
//////////////////StringUtilities.h
//#define BASE_10  10
//
///////////////////////////////UART.c
//#define MAX_BUFFER_SIZE 2000
//unsigned char dmaBuffer[MAX_BUFFER_SIZE];
//
//volatile int uartBusy = 0;
//
//
//
///////////////////StringUtilities.c
//
//// The following function came from
//// https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
//char* IntegerToString(int value, char *result, int base)
//{
//    // check that the base if valid
//    if (base < 2 || base > 36) { *result = '\0'; return result; }
//
//    char* ptr = result, *ptr1 = result, tmp_char;
//    int tmp_value;
//
//    do {
//        tmp_value = value;
//        value /= base;
//        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
//    } while ( value );
//
//    // Apply negative sign
//    if (tmp_value < 0) *ptr++ = '-';
//    *ptr-- = '\0';
//    while (ptr1 < ptr) {
//        tmp_char = *ptr;
//        *ptr--= *ptr1;
//        *ptr1++ = tmp_char;
//    }
//    return result;
//}
//
///////////////////////////////////
//
//
//
//void WaitForSPI1RXReady()
//{
//	// See page 605 of the datasheet for info on the SPI status register
//	// If Bit0 == 0 then SPI RX is empty
//	// If Bit7 == 1 then SPI is busy
//	while((ACCESS(SPI1_SR) & 1) == 0 || (ACCESS(SPI1_SR) & (1 << 7)) == 1) { }
//}
//
//void WaitForSPI1TXReady()
//{
//	// See page 605 of the datasheet for info on the SPI status register
//	// If Bit1 == 0 then SPI TX buffer is not empty
//	// If Bit7 == 1 then SPI is busy
//	while((ACCESS(SPI1_SR) & (1 << 1)) == 0 || (ACCESS(SPI1_SR) & (1 << 7)) == 1) { }
//}
//
//// See page 25 of the L3GD20 datasheet for details on how we send commands to, and make
//// queries of, the gyro.  If you look at figure 14 of UM1842 on page 33 you'll see how
//// the L3GD20 pins are connected to the STM32F411:
////    CS  --> PE3   // Chip Select
////    SPC --> PA5   // Clock
////    SDI --> PA7   // Data In
////    SDO --> PA6   // Data Out
//// As shown on page 25 of the L3GD20 communication with the gyro takes the following steps:
//// 1) The chip select must go from high to low to indicate we're doing a read or write.
//// 2) The first byte we send is the register of the gyro (combined with 0x80 if we're going
////    to do a read operation).
//// 3) Do a read from SDO
//// 4) Write the next byte
//// 5) Read a result
//// 6) Set CS back to high
//
//unsigned char ReadFromGyro(unsigned char gyroRegister)
//{
//	ACCESS(GPIOE_BSRR) |= (1 << 19);
//	WaitForSPI1TXReady();
//	ACCESS(SPI1_DR) = (gyroRegister | 0x80); // 0x80 indicates we're doing a read
//	WaitForSPI1RXReady();
//	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
//	WaitForSPI1TXReady();
//	ACCESS(SPI1_DR) = 0xFF;
//	WaitForSPI1RXReady();
//	volatile unsigned char readValue = (unsigned char)ACCESS(SPI1_DR);
//	ACCESS(GPIOE_BSRR) |= (1 << 3);
//
//	return readValue;
//}
//
//void WriteToGyro(unsigned char gyroRegister, unsigned char value)
//{
//	ACCESS(GPIOE_BSRR) |= (1 << 19);
//	WaitForSPI1TXReady();
//	ACCESS(SPI1_DR) = gyroRegister;
//	WaitForSPI1RXReady();
//	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
//	WaitForSPI1TXReady();
//	ACCESS(SPI1_DR) = value;
//	WaitForSPI1RXReady();
//	ACCESS(SPI1_DR);  // Don't care what valley the device put into the data register
//	ACCESS(GPIOE_BSRR) |= (1 << 3);
//}
//
//void GyroInit()
//{
//	SendString("Initializing Gyro Device\r\n");
//
//	// Give a clock to port A as pins PA5-thru-PA7 are connected to the gyro (pg 20 of UM1842) and
//	// page 116 of RM0383 for the RCC AHB register info.
//	ACCESS(RCC_AHB1ENR) |= 1;
//
//	// Give a clock to port E as pin PE3 is connected to the chip select of the gyro (pg 20 of
//	// UM1842) and page 116 of RM0383 for the RCC AHB register info.
//	ACCESS(RCC_AHB1ENR) |= (1 << 3);
//
//	// See pg 20 of the ST UM1842 document.  We'll be using SPI1 to communicate with the gyro.
//	// See pg 149 of RM0383.  It shows SPI1 to be alternate function 5.
//	// See pg 156 of RM0383 for documentation on the GPIO mode register.  It shows how to set
//	// pins to alternate mode.  We do this for pins PA5, PA6, PA7.
//	ACCESS(GPIOA_MODER) |= ((1 << 11) | (1 << 13) | (1 << 15));
//	ACCESS(GPIOE_MODER) |= (1 << 6);
//
//	// See pg 149 of ST RM0383 document.  SPI1 is AF5.  And pg 160 of the same document shows
//	// alternate function for pin 5 = bits 20-23, pin 6 = bits 24-27, pin 7 = bits 28-31.
//	// We set these to 5.
//	ACCESS(GPIOA_AFRL) |= ((5 << 20) | (5 << 24) | (5 << 28));
//
//	// Set the pins to fast speed.  See pg 157 for more info on the register.  Pin 5 corresponds to
//	// bits 10/11, 6=12/13, and 7=14,15.  And for port E pin 3 corresponds to bits 6/7.
//	ACCESS(GPIOA_OSPEEDR) |= ((2 << 10) | (2 << 12) | (2 << 14));
//	ACCESS(GPIOE_OSPEEDR) |= (2 << 6);
//
//	// Enable clock for SPI1
//	ACCESS(RCC_APB2ENR) |= (1 << 12);
//
//	// See page 602 for details of configuring SPI1 Control Register
//	// Set Bit 0: The second clock transition is the first data capture edge
//	// Set Bit 1: CK to 1 when idle
//	// Set Bit 2: The STM32 is the master, the gyro is the slave
//	// Set Bits 3-5 to 010 for a baud rate of fPCLK/8
//	// Set Bits 8-9: Software slave management enabled, Internal slave select to 1
//	ACCESS(SPI1_CR1) |= (1 | (1 << 1) | (1 << 2) | (2 << 3) | (1 << 8) | (1 << 9));
//
//	// Set Bit 6: Enable SPI.  See page 603.
//	ACCESS(SPI1_CR1) |= (1 << 6);
//
//	// Set the CS high on the gyro as setting it low indicates communication.  See
//	// 25 of the L3GD20 datasheet and page 159 of RM0383 for more info on BSRR.
//	ACCESS(GPIOE_BSRR) |= (1 << 3);
//
//	// See page 31 of the L3GD20 datasheet.  If communication to the gyro is properly
//	// setup, reading from register 0x0F will give us b11010100 (0xD4).
//	if(ReadFromGyro(0x0F) != 0xD7)
//	{
//		ad =ReadFromGyro(0x0F);
//		SendString("Initializing Gyro Device Failed\r\n");
//	}
//	else{
//		ad=2;
//	}
//
//	// See page 31 of the L3GD20 datasheet.  Writing 0x0F to register 0x20 will power up
//	// the gyro and enables the X, Y, Z axes.
//	WriteToGyro(0x20, 0x0F);
//
//	SendString("Initializing of Gyro Device Successful\r\n");
//}
//
//short GetAxisValue(unsigned char lowRegister, unsigned char highRegister)
//{
//	// See page 9 of L3GD20.  It shows the mechanical characteristics of the gyro.  Note
//	// that we leave the sensitivity as is (i.e. 0) so that it's 250 dps.  So, we read
//	// the value from the gyro and convert it to a +/- 360 degree value.
//	float scaler = 8.75 * 0.001;
//	short temp = (ReadFromGyro(lowRegister) | (ReadFromGyro(highRegister) << 8));
//	return (short)((float)temp * scaler);
//}
//
//void DisplayAxisValue(char* label, short value)
//{
//	// Print the label
//	SendString(label);
//	SendString(":");
//
//	// Convert the number to string
//	char valueAsString[8];
//	IntegerToString(value, valueAsString, BASE_10);
//
//	// Right justify display the string
//	short strlen = 0;
//	while(valueAsString[strlen])
//	{
//		strlen++;
//	}
//
//	while(strlen < 4)
//	{
//		SendString(" ");
//		++strlen;
//	}
//
//	SendString(valueAsString);
//}
//
//short DisplayAxisValues()
//{
//	// See page 36 of the L3GD20 datasheet.  It shows the hi/lo addresses of each of
//	// the axes.
//	short x = GetAxisValue(0x28, 0x29);
//	DisplayAxisValue("X", x);
//	SendString("  ");
//	short y = GetAxisValue(0x2A, 0x2B);
//	DisplayAxisValue("Y", y);
//	SendString("  ");
//	short z = GetAxisValue(0x2C, 0x2D);
//	DisplayAxisValue("Z", z);
//
//	// Reset the terminal cursor to the beginning of the line
//	SendString("\r");
//	return x;
//}
//
///////////////////////////////////////////////////////////////////////////UART.c
//
//
//void DMA1_Stream6_IRQHandler(void)
//{
//	// See pg 187.  Bit 21 is the "Stream 6 transfer complete interrupt flag".  This bit
//	// will be set when the DMA transfer is complete.
//	if((ACCESS(DMA1_HISR) & (1 << 21)) != 0)
//	{
//		// See pg 188.  Here we clear the transfer complete interrupt.
//		ACCESS(DMA1_HIFCR) |= (1 << 21);
//
//		// See pg 552.  Here we specify that we want an interrupt generated once the
//		// USART transmission is complete.
//		ACCESS(USART2_CR1) |= (1 << 6);
//	}
//}
//
//void USART2_IRQHandler(void)
//{
//	// See pg 549.  Bit 6 of the status register will be set when the UART
//	// transmission has completed.
//	if((ACCESS(USART2_SR) & (1 << 6)) != 0)
//	{
//		// Clear the interrupt. (...So that it doesn't continually trigger)
//		ACCESS(USART2_CR1) &= ~(1 << 6);
//
//		// Clear the busy flag to allow the next transmission.
//		uartBusy = 0;
//	}
//}
//
//void UartGpioInit()
//{
//	// Give a clock to port A as we'll be using one of its pins for transfer of data.
//	ACCESS(RCC_AHB1ENR) |= 1;
//
//	// See pg 19 of the ST UM1842 document.  We'll be using USART2.  USART2 TX occurs on
//	// PA2 and USART2 RX occurs on PA3 so we set this pin to alternate mode.
//	ACCESS(GPIOA_MODER) |= ((1 << 5) | (1 << 7));
//
//	// See pg 149 of ST RM0383 document.  USART2 is AF7.  And pg 160 of the same document
//	// shows alternate function for pins 2 and 3 are set using alternate function low register
//	// bits 8-thru-11.
//	ACCESS(GPIOA_AFRL) |= ((7 << 8) | (7 << 12));
//
//	// Set PA2 and PA3 to high speed
//	ACCESS(GPIOA_OSPEEDR) |= ((3 << 4) | (3 << 6));
//}
//
//void UartDmaInit()
//{
//	// Enable a clock for DMA1
//	ACCESS(RCC_AHB1ENR) |= (1 << 21);
//
//	// See pg 189 for details of the DMA stream configuration register
//	// Setting bit 6 specifies memory-to-peripheral communication.
//	// Setting bit 10 specifies to increment the memory pointer after each data transfer.  This
//	// allows the DMA device to progressively step through the dmaBuffer array.
//	// Setting bit 27 specifies to use channel 4 of stream 6.
//	ACCESS(DMA1_S6CR) |= ((1 << 6) | (1 << 10) | (1 << 27));
//
//	// Enable interrupt for DMA1_Stream6
//	ACCESS(NVIC_ISER0) |= (1 << 17);
//}
//
//void UartInit()
//{
//	UartGpioInit();
//
//	UartDmaInit();
//
//	// Give a clock USART2.  See pg 117.
//	ACCESS(RCC_APB1ENR) |= (1 << 17);
//
//	// Here we set the baud rate.  This is explained on 519 of ST RM0383.  The peripheral
//	// clock is 16 MHz by default.  So, the calculation for the USARTDIV is:
//	// DesiredBaudRate = 16MHz / 16*USARTDIV
//	// Note that the fractional part of USARTDIV is represented with only 4 bits.  So
//	// if we use 9600 this will result in a small error of 0.02% (see pg 522).  Therefore
//	// the baud rate is actually 9,598.  Again, see pg 522.
//	ACCESS(USART2_BRR) |= 0x683;
//
//	// Enable USART2 for transmitting data.
//	ACCESS(USART2_CR1) |= ((1 << 3) | (1 << 13));
//
//	// See pg 200 of RM0383 ("STM32F411xC/E Reference Manual") for the interrupt
//	// vector table.  You'll see TIM3 is interrupt 29.
//	// See pg 209 of PM0214 ("STM32F4 Series Programming Manual") for info on "ISER"
//	// which is one of the "interrupt set-enable registers".  We enable interrupt
//	// number 29.
//	ACCESS(NVIC_ISER1) |= (1 << (38 - 32));
//}
//
//void SendString(char* string)
//{
//	// Here we block until the previous transfer completes.
//	while(uartBusy == 1);
//	uartBusy = 1;
//
//	// Copy the string into the DMA buffer and also calculate its length.
//	int lengthOfString = 0;
//	while(lengthOfString < MAX_BUFFER_SIZE && string[lengthOfString])
//	{
//		dmaBuffer[lengthOfString] = string[lengthOfString];
//		++lengthOfString;
//		printf(dmaBuffer[lengthOfString]);
//	}
//
//	// See pg 192.  This register holds the number of data items to transfer.
//	ACCESS(DMA1_S6NDTR) = lengthOfString;
//
//	// See pg 193.  This register holds the peripheral data register.  Since we're
//	// using USART2 we set it to its data register.
//	ACCESS(DMA1_S6PAR) = USART2_DR;
//
//	// See pg 193.  This register holds the memory address of the data we want to transfer.
//	ACCESS(DMA1_S6M0AR) = (unsigned int)dmaBuffer;
//
//	// Enable interrupt to occur upon completion of transfer
//	ACCESS(DMA1_S6CR) |= (1 << 4);
//
//	// Enable the stream
//	ACCESS(DMA1_S6CR) |= 1;
//
//	// Clear the transfer complete flag in the UART SR
//	ACCESS(USART2_SR) &= ~(1 << 6);
//
//	// Enable DMA transmission
//	ACCESS(USART2_CR3) |= (1 << 7);
//}



//#include "L3GD20.h"
#include <stdint.h>
#include "main.h"

#define AVERAGE_WINDOW_SIZE                  ((uint32_t) 10u)
#define CALIBRATION_BUFFER_LENGTH            ((uint32_t) 2000u)
#define L3GD20_SENSITIVITY    ((float)0.07)


typedef enum
{
	L3GD20_DATA_NOT_READY,
	L3GD20_DATA_READY,
}L3GD20_DataReadyFlagType;

static L3GD20_DataReadyFlagType dataReadyFlag=L3GD20_DATA_READY;

typedef enum
{
	L3GD20_collect_calibration_samples,
	L3GD20_process_calibration_samples,
	L3GD20_calibrated,
}L3GD20_caliStateType;

static L3GD20_caliStateType currentcalistate=L3GD20_collect_calibration_samples;



typedef enum
{
	L3GD20_fisrt,
	L3GD20_second,
	L3GD20_finaly
}L3GD20_StateType;
static L3GD20_StateType currentState=L3GD20_fisrt;


static float angleRate_x=0;
static float angleRate_y=0;
static float angleRate_z=0;

static int32_t offset_x=0;
static int32_t offset_y=0;
static int32_t offset_z=0;

static float Noise_X = 0;
static float Noise_Y = 0;
static float Noise_Z = 0;

static float Angle_X = 0;
static float Angle_Y = 0;
static float Angle_Z = 0;

static float LastAngleRate_X = 0;
static float LastAngleRate_Y = 0;
static float LastAngleRate_Z = 0;

static int32_t TempNoise_X = 0;
static int32_t TempNoise_Y = 0;
static int32_t TempNoise_Z = 0;






volatile static uint32_t caliCounter = 0;


static int16_t calibrationBuffer_X[CALIBRATION_BUFFER_LENGTH];
static int16_t calibrationBuffer_Y[CALIBRATION_BUFFER_LENGTH];
static int16_t calibrationBuffer_Z[CALIBRATION_BUFFER_LENGTH];

static uint8_t spiTxBuf[2];
static uint8_t spiRxBuf[7];

uint32_t previousTime = 0;
float timeDifference = 0;
uint32_t currentTime = 0;
int ss;


void L3GD20_Init(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
	spiTxBuf[0]=0x0F;//who i am register address
	HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
	HAL_SPI_Receive(&hspi1,&spiRxBuf[1],1,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(20);



	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0]=0x20;
	spiTxBuf[1]=0xff;
	HAL_SPI_Transmit(&hspi1,spiTxBuf,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0]=0x21;
	spiTxBuf[1]=0x00;
	HAL_SPI_Transmit(&hspi1,spiTxBuf,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0]=0x22;
	spiTxBuf[1]=0x00;
	HAL_SPI_Transmit(&hspi1,spiTxBuf,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0]=0x23;
	spiTxBuf[1]=0x20;
	HAL_SPI_Transmit(&hspi1,spiTxBuf,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0]=0x24;
	spiTxBuf[1]=0x10;
	HAL_SPI_Transmit(&hspi1,spiTxBuf,2,50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(20);

}

void L3GD20_loop(void)
{
		volatile int16_t Raw_x=0;
		volatile int16_t Raw_y=0;
		volatile int16_t Raw_z=0;



		int16_t averageWindow_X[AVERAGE_WINDOW_SIZE] = {0};
		int16_t averageWindow_Y[AVERAGE_WINDOW_SIZE] = {0};
		int16_t averageWindow_Z[AVERAGE_WINDOW_SIZE] = {0};

		uint32_t windowPosition = 0;
		int32_t tempSum_X = 0;
		int32_t tempSum_Y = 0;
		int32_t tempSum_Z = 0;

		currentTime = __HAL_TIM_GET_COUNTER(&htim2);

		if(currentTime>=previousTime)
		{
			timeDifference = (currentTime - previousTime)*1.0/HAL_RCC_GetHCLKFreq();
		}
		else
		{
			timeDifference = (4294967295 + currentTime - previousTime)*1.0/ HAL_RCC_GetHCLKFreq();
		}
		previousTime = currentTime;

		switch(currentState)
		{
			//---------------------------------------------------------------------------
			//data
			case(L3GD20_fisrt):
				if(dataReadyFlag==L3GD20_DATA_READY)
				{
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
						spiTxBuf[0]=0x28|0x80;
						HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
						HAL_SPI_Receive(&hspi1,&spiRxBuf[1],1,50);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
						spiTxBuf[0]=0x29|0x80;
						HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
						HAL_SPI_Receive(&hspi1,&spiRxBuf[2],1,50);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
						spiTxBuf[0]=0x2a|0x80;
						HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
						HAL_SPI_Receive(&hspi1,&spiRxBuf[3],1,50);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
						spiTxBuf[0]=0x2b|0x80;
						HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
						HAL_SPI_Receive(&hspi1,&spiRxBuf[4],1,50);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
						spiTxBuf[0]=0x2c|0x80;
						HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
						HAL_SPI_Receive(&hspi1,&spiRxBuf[5],1,50);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
						spiTxBuf[0]=0x2d|0x80;
						HAL_SPI_Transmit(&hspi1,spiTxBuf,1,50);
						HAL_SPI_Receive(&hspi1,&spiRxBuf[6],1,50);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);

						currentState=L3GD20_second;
						dataReadyFlag=L3GD20_DATA_NOT_READY;
				}
				else
				{
				}

				break;
						//-----------------------------------------------------------------------------------
						//varibla
			case(L3GD20_second):
				Raw_x=(spiRxBuf[2]<<8)|spiRxBuf[1];
				Raw_y=(spiRxBuf[4]<<8)|spiRxBuf[3];
				Raw_z=(spiRxBuf[6]<<8)|spiRxBuf[5];

			if(currentcalistate==L3GD20_calibrated)
			{
				HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
				angleRate_x=(float) (Raw_x - (offset_x))*L3GD20_SENSITIVITY;
				angleRate_y=(float) (Raw_y - (offset_y))*L3GD20_SENSITIVITY;
				angleRate_z=(float) (Raw_z - (offset_z))*L3GD20_SENSITIVITY;


//				timeDifference = 0.001;


				if((angleRate_x>Noise_X)||(angleRate_x<-Noise_X))
				{
					Angle_X+=((angleRate_x+LastAngleRate_X)*timeDifference)/(2.0f);
					LastAngleRate_X=angleRate_x;
				}
				else
				{
				}
				if((angleRate_y>Noise_Y)||(angleRate_y<-Noise_Y))
				{
					Angle_Y+=((angleRate_y+LastAngleRate_Y)*timeDifference)/(2.0f);
					LastAngleRate_Y=angleRate_y;
				}
				else
				{
				}
				if((angleRate_z>Noise_Z)||(angleRate_z<-Noise_Z))
				{//57.29577951308232
					Angle_Z+=((angleRate_z+LastAngleRate_Z)*timeDifference)/(2.0f);
					LastAngleRate_Z=angleRate_z;
				}
				else
				{
				}
			}
			else
			{
				switch(currentcalistate)
				{
					//---------------------------------------------------------------------------------------------------------
					case(L3GD20_collect_calibration_samples):
						calibrationBuffer_X[caliCounter]=Raw_x;
						calibrationBuffer_Y[caliCounter]=Raw_y;
						calibrationBuffer_Z[caliCounter]=Raw_z;
						caliCounter++;

						if(caliCounter>=CALIBRATION_BUFFER_LENGTH)
						{
							caliCounter=0;

							currentcalistate=L3GD20_process_calibration_samples;
						}
						else
						{
						}
						break;
					//----------------------------------------------------------------------------------------------------------
					case(L3GD20_process_calibration_samples):
						for(uint32_t idx=0; idx<CALIBRATION_BUFFER_LENGTH;idx++)
							{
								tempSum_X=tempSum_X-averageWindow_X[windowPosition]+calibrationBuffer_X[idx];
								tempSum_Y=tempSum_Y-averageWindow_Y[windowPosition]+calibrationBuffer_Y[idx];
								tempSum_Z=tempSum_Z-averageWindow_Z[windowPosition]+calibrationBuffer_Z[idx];

								averageWindow_X[windowPosition]=calibrationBuffer_X[idx];
								averageWindow_Y[windowPosition]=calibrationBuffer_Y[idx];
								averageWindow_Z[windowPosition]=calibrationBuffer_Z[idx];

								offset_x=tempSum_X/(int32_t)AVERAGE_WINDOW_SIZE;
								offset_y=tempSum_Y/(int32_t)AVERAGE_WINDOW_SIZE;
								offset_z=tempSum_Z/(int32_t)AVERAGE_WINDOW_SIZE;

								windowPosition++;

								if(windowPosition>=AVERAGE_WINDOW_SIZE)
								{
									windowPosition=0;
								}
								else
								{
								}

							}
							for(uint32_t idx=0;idx<CALIBRATION_BUFFER_LENGTH;idx++)
							{
								if(((int32_t)calibrationBuffer_X[idx]-offset_x)>TempNoise_X)
								{
									TempNoise_X=(int32_t)calibrationBuffer_X[idx]-offset_x;
								}
								else if(((int32_t)calibrationBuffer_X[idx]-offset_x)<-TempNoise_X)
								{
									TempNoise_X=-((int32_t)calibrationBuffer_X[idx]-offset_x);
								}

								if(((int32_t)calibrationBuffer_Y[idx]-offset_y)>TempNoise_Y)
								{
									TempNoise_Y=(int32_t)calibrationBuffer_Y[idx]-offset_y;
								}
								else if(((int32_t)calibrationBuffer_Y[idx]-offset_y)<-TempNoise_Y)
								{
									TempNoise_Y=-((int32_t)calibrationBuffer_Y[idx]-offset_y);
								}

								if(((int32_t)calibrationBuffer_Z[idx]-offset_z)>TempNoise_Z)
								{
									TempNoise_Z=(int32_t)calibrationBuffer_Z[idx]-offset_z;
								}
								else if(((int32_t)calibrationBuffer_Z[idx]-offset_z)<-TempNoise_Z)
								{
									TempNoise_Z=-((int32_t)calibrationBuffer_Z[idx]-offset_z);
								}
							}

							Noise_X=(float)TempNoise_X*L3GD20_SENSITIVITY;
							Noise_Y=(float)TempNoise_Y*L3GD20_SENSITIVITY;
							Noise_Z=(float)TempNoise_Z*L3GD20_SENSITIVITY;

							currentcalistate=L3GD20_calibrated;
							break;

					case(L3GD20_calibrated):
						break;

					default:
						break;
				}

			}
			currentState=L3GD20_fisrt;
			dataReadyFlag=L3GD20_DATA_READY;
			break;

					default:
						break;

		}
}

