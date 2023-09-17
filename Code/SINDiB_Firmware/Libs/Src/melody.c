#include "melody.h"


const uint32_t marioMelody[] = {
		  NOTE_E7, NOTE_E7, 0, NOTE_E7,
		  0, NOTE_C7, NOTE_E7, 0,
		  NOTE_G7, 0, 0,  0,
		  NOTE_G6, 0, 0, 0,

		  NOTE_C7, 0, 0, NOTE_G6,
		  0, 0, NOTE_E6, 0,
		  0, NOTE_A6, 0, NOTE_B6,
		  0, NOTE_AS6, NOTE_A6, 0,

		  NOTE_G6, NOTE_E7, NOTE_G7,
		  NOTE_A7, 0, NOTE_F7, NOTE_G7,
		  0, NOTE_E7, 0, NOTE_C7,
		  NOTE_D7, NOTE_B6, 0, 0,

		  NOTE_C7, 0, 0, NOTE_G6,
		  0, 0, NOTE_E6, 0,
		  0, NOTE_A6, 0, NOTE_B6,
		  0, NOTE_AS6, NOTE_A6, 0,

		  NOTE_G6, NOTE_E7, NOTE_G7,
		  NOTE_A7, 0, NOTE_F7, NOTE_G7,
		  0, NOTE_E7, 0, NOTE_C7,
		  NOTE_D7, NOTE_B6, 0, 0
};

const uint32_t secondMelody[] = {
		  NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
		  NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,
		  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
		  NOTE_C4, NOTE_D4,0,

		  NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
		  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,      //29               //8
		  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
		  NOTE_C4, NOTE_D4,0,

		  NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
		  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
		  NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
		  NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58

		  NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
		  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
		  NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
		  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,

		  NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
		  NOTE_C4, NOTE_D4, 0,
		  NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
		  NOTE_C4, NOTE_D4
};

const uint32_t marioDuration[] = {
		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,

		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,

		  9, 9, 9,
		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,

		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,

		  9, 9, 9,
		  12, 12, 12, 12,
		  12, 12, 12, 12,
		  12, 12, 12, 12,
};

const uint32_t secondDuration[] = {
  8,4,8,4,
  4,4,4,12,
  4,4,4,4,4,4,
  4,16,4,

  8,4,8,4,
  4,2,1,1,2,1,1,12,
  4,4,4,4,4,4,
  4,16,4,

  4,4,4,4,4,4,
  4,4,4,12,
  4,4,4,4,4,4,
  4,4,4,12,

  4,4,4,4,4,4,
  2,1,1,2,1,1,4,8,4,
  2,6,4,2,6,4,
  2,1,1,16,4,

  4,8,4,4,4,
  4,16,4,
  4,8,4,4,4,
  4,20,
};

const u32* melody[] ={marioMelody, secondMelody};
const u32* noteDurations[] = {marioDuration, secondDuration};
const u16 melodySlowfactor[] ={15, 30};

const u32 melodySizes[] ={sizeof(marioMelody)/sizeof(uint32_t),
						sizeof(secondDuration)/sizeof(uint32_t)};

