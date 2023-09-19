#ifndef INC_TYPEDEFS_H_
#define INC_TYPEDEFS_H_

#include <stdint.h>

#define u32_max 4294967295

#define u32 uint32_t
#define u16 uint16_t
#define u8  uint8_t

typedef enum adc_channels
{
    LF_RECEIVER = 0,
    RF_RECEIVER,
    DR_RECEIVER,
	DL_RECEIVER,
	BAT_VOL
}adc_channels;


////////////////////////////// L3GD20.h //////////////////////////////////////////
typedef enum
{
	L3GD20_collect_calibration_samples,
	L3GD20_process_calibration_samples,
	L3GD20_calibrated,
} L3GD20_caliStateType;

typedef enum
{
	L3GD20_DATA_NOT_READY,
	L3GD20_DATA_READY,
} L3GD20_DataReadyFlagType;

typedef enum
{
	L3GD20_fisrt,
	L3GD20_second,
	L3GD20_finaly
} L3GD20_StateType;

///////////////////////////////////// BUZZER.h //////////////////////////////////////
typedef enum 
{
	WIN_TONE=0,
	TONE1,
	TONE2,
	TONE3,
	TONE4
} BUZZ_Tones;


///////////////////////////////////// DISPLAY.h //////////////////////////////////////
typedef enum
{
	SMALL=0,  		// 6x8
	MEDIUM,			// 7x10
	LARGE,			// 11x18
	HUGE			// 16x24
} FONT_Size;


typedef enum
{
	INIT = 0,
	DEFAULT,
	GYRO_CALIB,
	SENSOR_READ,
	LOW_BAT,
	SUCESS_MSG,
	SPEED_ADJ
} DISP_State;



//////////////////////////////////////////motor.h//////////////////////////////////////////////
typedef enum
{
	IDLE,
	MOVE_STRAIGHT,
	TAKE_TURN,
	ALIGN

}PID_State;

#endif /* INC_TYPEDEFS_H_ */
