/*
 MAIN FILE CONTAINING ALL OUR CODES
 TEAM: SINDiB
 AUTHOR: BIYON
*/

#include "cppmain.h"
uint16_t i ;
uint16_t pos_l, pos_r;
void cppmain(void){
    
    // INITIALIZATION OF HARDWARES
    motorInit();
    encoderInit();
    i=0;

    while(1){
        // goLong(500);
    	i++;
        pos_l = l_position;
        pos_r = r_position;
    }
}


