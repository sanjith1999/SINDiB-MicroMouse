#include "melody.h"

const uint32_t winTone[] = {
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

const uint32_t winDuration[] = {
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

const uint32_t tone1[] = {
		  NOTE_F5
};

const uint32_t tone1Duration[] = {
		  5
};

const uint32_t tone2[] = {
		  NOTE_C5, 0,NOTE_C5, 0, NOTE_C5
};

const uint32_t tone2Duration[] = {
		  4, 2, 4, 2, 4
};

const uint32_t tone3[] = {
		  NOTE_C2, 0, NOTE_C2
};

const uint32_t tone3Duration[] = {
		  4, 2, 4
};

const uint32_t tone4[] = {
		  NOTE_A4
};

const uint32_t tone4Duration[] = {
		  4
};




const u32* melody[] ={winTone,tone1, tone2, tone3, tone4};
const u32* noteDurations[] = {winDuration, tone1Duration, tone2Duration, tone3Duration, tone4Duration };

const u32 melodySizes[] ={sizeof(winTone)/sizeof(uint32_t),sizeof(tone1)/sizeof(uint32_t), sizeof(tone2)/sizeof(uint32_t), sizeof(tone3)/sizeof(uint32_t),
						sizeof(tone4)/sizeof(uint32_t)};

