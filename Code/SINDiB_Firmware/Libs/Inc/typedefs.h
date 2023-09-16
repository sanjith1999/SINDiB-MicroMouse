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

#endif /* INC_TYPEDEFS_H_ */
