#ifndef PARAMETERS__H_
#define PARAMETERS__H_

#define REFLECTION_RATE_ 1000
#define LOW_BAT_TH_ 7.4

// ENCODER.h
#define LINEAR_SENSITIVITY 66.7

///////////////////////////// MOTOR.H //////////////////////////////////////////
#define SPEED_THRESHOLD_ 0.7

//////////////////////////// PID.H //////////////////////////////////////////////
// STRAIGHT MOVEMENT PARAMETERS
#define S1Kp_ 1.0
#define S1Kd_ .6
#define S2Kp_ 1.0
#define S2Kd_ .6

// PID ERROR REDUCTION FACTOR
#define AC_RED_S1_ 30
#define AC_RED_S2_ 20


/////////////////////////////////// L3GD20.h /////////////////////////////////////////
#define GYRO_SENSITIVITY_ 0.071
#define NOISE_THRESHOLD_ 1.5

//////////////////////////////////// DISPLAY.h ////////////////////////////////////////
#define FPS 1  // MIN_ALLOWED --> .5

/////////////////////////////////Buzzer.h /////////////////////////////////
#define BUZZ_LOUDNESS_ .03


#endif /* PARAMETERS__H_ */
