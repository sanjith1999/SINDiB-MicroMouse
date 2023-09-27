#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

/*
SCREEN SIZE => 128x32

     128  --> x
------------
|          | 32  y
------------

FONT SIZES
----------
SMALL    		// 6x8
MEDIUM		// 7x10
LARGE		// 11x18
HUGE			// 16x24
*/


#include <stdio.h>
#include <string.h>
#include "typedefs.h"
#include "read_sensors.h"

#include "ssd1306.h"

// THIS VARIABLE DECIDES WHAT IS ON SCREEN
extern DISP_State disp_state;

// INITIALIZATION OF THE DISPLAY 
void displayInit(void);

// CLEARNING SCREEN
void clearScreen();

// WRITING STRING ON SCREEN
void writeString(char *str, FONT_Size font_size);

// PUTTING A STRING ON SPECIFIED LOCATION
void putString(char *str, int x, int y, FONT_Size font_size);

// PUTTING A CHARACTOR ON SPECIFIED LOCATION
void putChar(char chr, int x, int y, FONT_Size font_size);

// PUTTING A INT ON SPECIFIED LOCATION
void putInt(int INT, int x, int y, FONT_Size font_size);

// PUTTING A FLOAT ON SPECIFIED LOCATION
void putFloat(float FLOAT, int x, int y, FONT_Size font_size);

// DISPLAY UPDATE -- CONTAINS ALL THE NECESSARY SCREEN DETAILS
void displayUpdate(void);


#endif /* INC_DISPLAY_H_ */
