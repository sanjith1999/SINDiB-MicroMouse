#include "L3GD20.h"

const float timeDifference = 2e-3;
const float NOISE_THRESHOLD = NOISE_THRESHOLD_;
const float GYRO_SENSITIVITY = GYRO_SENSITIVITY_;

u8 gyro_identity;
float angle_z = 0;
float last_angle_rate = 0, angle_rate=0;

float offset;
float noise;

static u8 spiTxBuf[2];
static u8 spiRxBuf[2];


void gyroInit(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	spiTxBuf[0] = 0x0F | 0x80; // WHO_AM_I
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
	HAL_SPI_Receive(&hspi1, &gyro_identity, 1, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x20; // CTRL1:           DR1 DR0 BW1 BW0 PD Zen Xen Yen
	spiTxBuf[1] = 0xfc; // 800Hz, BW-100Hz   1   1   1   1   1  1   0   0
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x21; // CTRL2:            EXTRen LVLen HPM1 HMP0 HPCF3 HPCF2 HPCF1 HPCF0
	spiTxBuf[1] = 0x03; //  2Hz                0      0    0    0      0    1     0    1
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x23; // CTRL4:             BDU      BLE    FS1    FS0     IMPen   ST2  ST1   SIM
	spiTxBuf[1] = 0x30; // 2000dps     	       0        0    	1      1       0       0    0     0
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(20);
	spiTxBuf[0] = 0x24; // CTRL5:              BOOT FIFO_EN   StopOnFTH    HPen   IG_Sel1    IG_Sel2   Out_Sel1   Out_Sel0
	spiTxBuf[1] = 0x00; //                      0      0         0           0       0         0          0        0
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(20);
}

int gyroUpdate(void)
{
	LED8_ON;
	angle_rate = (float)(readGyro() - offset) * GYRO_SENSITIVITY;
	angle_rate = (fabs(angle_rate) < noise && fabs(angle_rate)<NOISE_THRESHOLD) ? 0 : angle_rate;
	angle_z += ((angle_rate + last_angle_rate) * timeDifference) / (2.0f);
	last_angle_rate = angle_rate;
	LED8_OFF;
	return 0;
}

int16_t readGyro(void)
{
	u16 raw_z = 0;

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	spiTxBuf[0] = 0x2c | 0x80; // 0x2c ~ L8 bits OUT_Z(2's complement form),  0x2c | 0x80 ~ READ OPERATION
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
	HAL_SPI_Receive(&hspi1, &spiRxBuf[0], 1, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	spiTxBuf[0] = 0x2d | 0x80;
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50); // 0x2c ~ U8 bits OUT_Z(2's complement form),  0x80 ~ READ OPERATION
	HAL_SPI_Receive(&hspi1, &spiRxBuf[1], 1, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

	raw_z = (spiRxBuf[1] << 8) | spiRxBuf[0];
	return (int16_t)raw_z;
}

void gyroCalibration(void)
{
	LED9_ON, LED10_ON, LED11_ON;
	int16_t calibration_buffer[BUFFER_LENGTH];
	int32_t calibration_sum = 0;

	for (u32 idx = 0; idx < BUFFER_LENGTH; idx++)
	{
		calibration_buffer[idx] = readGyro();
		HAL_Delay(2);
		calibration_sum += calibration_buffer[idx];
	}

	offset = (float)calibration_sum / BUFFER_LENGTH;

	for (u32 idx = 0; idx < BUFFER_LENGTH; idx++)
		noise += pow(calibration_buffer[idx] - offset, 2);
	noise = pow(noise, .5) / 2 * GYRO_SENSITIVITY;

	LED9_OFF, LED10_OFF, LED11_OFF;

	return;
}