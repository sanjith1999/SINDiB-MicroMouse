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


// L3GD20.h
typedef enum
{
	L3GD20_collect_calibration_samples,
	L3GD20_process_calibration_samples,
	L3GD20_calibrated,
} L3GD20_caliStateType;

// L3GD20.h
typedef enum
{
	L3GD20_DATA_NOT_READY,
	L3GD20_DATA_READY,
} L3GD20_DataReadyFlagType;

// L3GD20.h
typedef enum
{
	L3GD20_fisrt,
	L3GD20_second,
	L3GD20_finaly
} L3GD20_StateType;

#endif /* INC_TYPEDEFS_H_ */
