// #include "L3GD20.h"
#include <stdint.h>
#include "main.h"

#define AVERAGE_WINDOW_SIZE ((uint32_t)10u)
#define CALIBRATION_BUFFER_LENGTH ((uint32_t)2000u)
#define GYRO_SENSITIVITY ((float)0.1361)
#define GYRO_NOISE_THRESHOLD ((float) 0.95)



static L3GD20_DataReadyFlagType dataReadyFlag = L3GD20_DATA_READY;
static L3GD20_caliStateType currentcalistate = 	L3GD20_collect_calibration_samples;


static L3GD20_StateType currentState = L3GD20_fisrt;

static float angleRate_z = 0;
static int32_t offset_z = 0;
static float Noise_Z = 0;
float Angle_Z = 0;
static float LastAngleRate_Z = 0;
static int32_t TempNoise_Z = 0;

volatile static uint32_t caliCounter = 0;

static int16_t calibrationBuffer_Z[CALIBRATION_BUFFER_LENGTH];

static uint8_t spiTxBuf[2];
static uint8_t spiRxBuf[7];

uint32_t previousTime = 0;
float timeDifference;
uint32_t currentTime = 0;
int ss;

volatile int16_t Raw_z = 0;

void L3GD20_Init(void)
{	LED9_ON;LED10_ON;LED11_ON;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	spiTxBuf[0] = 0x0F; // who i am register address
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
	HAL_SPI_Receive(&hspi1, &spiRxBuf[1], 1, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x20;
	spiTxBuf[1] = 0xff;
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x21;
	spiTxBuf[1] = 0x00;
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x22;
	spiTxBuf[1] = 0x00;
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x23;
	spiTxBuf[1] = 0x20;
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x24;
	spiTxBuf[1] = 0x10;
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	Raw_z = 0;


	int16_t averageWindow_Z[AVERAGE_WINDOW_SIZE] = {0};

	uint32_t windowPosition = 0;
	int32_t tempSum_Z = 0;

	while (1)
	{
		switch (currentState)
		{
		case (L3GD20_fisrt):
			if (dataReadyFlag == L3GD20_DATA_READY)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				spiTxBuf[0] = 0x2c | 0x80;
				HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
				HAL_SPI_Receive(&hspi1, &spiRxBuf[5], 1, 50);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				spiTxBuf[0] = 0x2d | 0x80;
				HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
				HAL_SPI_Receive(&hspi1, &spiRxBuf[6], 1, 50);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

				currentState = L3GD20_second;
				dataReadyFlag = L3GD20_DATA_NOT_READY;
			}
			else
			{
			}
			break;

		case (L3GD20_second):
			Raw_z = (spiRxBuf[6] << 8) | spiRxBuf[5];

			if (currentcalistate == L3GD20_calibrated)
			{
				break;
			}
			else
			{
				switch (currentcalistate)
				{
				//---------------------------------------------------------------------------------------------------------
				case (L3GD20_collect_calibration_samples):
					calibrationBuffer_Z[caliCounter] = Raw_z;
					caliCounter++;

					if (caliCounter >= CALIBRATION_BUFFER_LENGTH)
					{
						caliCounter = 0;

						currentcalistate = L3GD20_process_calibration_samples;
					}
					else
					{
					}
					break;
					//----------------------------------------------------------------------------------------------------------
				case (L3GD20_process_calibration_samples):
					for (uint32_t idx = 0; idx < CALIBRATION_BUFFER_LENGTH;
						 idx++)
					{
						tempSum_Z = tempSum_Z - averageWindow_Z[windowPosition] + calibrationBuffer_Z[idx];

						averageWindow_Z[windowPosition] = calibrationBuffer_Z[idx];

						offset_z = tempSum_Z / (int32_t)AVERAGE_WINDOW_SIZE;

						windowPosition++;

						if (windowPosition >= AVERAGE_WINDOW_SIZE)
						{
							windowPosition = 0;
						}
						else
						{
						}
					}
					for (uint32_t idx = 0; idx < CALIBRATION_BUFFER_LENGTH; idx++)
						if (((int32_t)calibrationBuffer_Z[idx] - offset_z) > TempNoise_Z)
							TempNoise_Z = (int32_t)calibrationBuffer_Z[idx] - offset_z;
						else if (((int32_t)calibrationBuffer_Z[idx] - offset_z) < -TempNoise_Z)
							TempNoise_Z = -((int32_t)calibrationBuffer_Z[idx] - offset_z);

					Noise_Z = (float)TempNoise_Z * GYRO_SENSITIVITY;

					currentcalistate = L3GD20_calibrated;
					break;

				case (L3GD20_calibrated):
					break;

				default:
					currentcalistate = L3GD20_collect_calibration_samples;
					break;
				}
			}
			currentState = L3GD20_fisrt;
			dataReadyFlag = L3GD20_DATA_READY;

		default:
			currentState = L3GD20_fisrt;
		}
		if (currentcalistate == L3GD20_calibrated)
		{
			break;
		}

		HAL_Delay(1);
	}
	LED9_OFF;LED10_OFF;LED11_OFF;
}

void L3GD20_loop(void)
{
	Noise_Z = (Noise_Z>GYRO_NOISE_THRESHOLD)? GYRO_NOISE_THRESHOLD:Noise_Z;
	Raw_z = 0;

	if (dataReadyFlag == L3GD20_DATA_READY)
	{

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		spiTxBuf[0] = 0x2c | 0x80;
		HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
		HAL_SPI_Receive(&hspi1, &spiRxBuf[5], 1, 50);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		spiTxBuf[0] = 0x2d | 0x80;
		HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
		HAL_SPI_Receive(&hspi1, &spiRxBuf[6], 1, 50);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

		dataReadyFlag = L3GD20_DATA_NOT_READY;
	}
	else
	{

		Raw_z = (spiRxBuf[6] << 8) | spiRxBuf[5];
		angleRate_z = (float)(Raw_z - (offset_z)) * GYRO_SENSITIVITY;

		timeDifference = 0.001;

		if ((angleRate_z > Noise_Z) || (angleRate_z < -Noise_Z))
		{ 
			Angle_Z += ((angleRate_z + LastAngleRate_Z) * timeDifference) / (2.0f);
			LastAngleRate_Z = angleRate_z;
		}
		else;
		dataReadyFlag = L3GD20_DATA_READY;
	}
}
