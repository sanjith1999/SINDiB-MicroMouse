#ifndef PARAMETERS__H_
#define PARAMETERS__H_

// ENCODER.h
#define LINEAR_SENSITIVITY 66.7

///////////////////////////// MOTOR.H //////////////////////////////////////////
#define SPEED_THRESHOLD_ 0.7

//////////////////////////// PID.H //////////////////////////////////////////////
// STRAIGHT MOVEMENT PARAMETERS
#define STKp_ 1.0
#define STKd_ .6
#define STKi_ .08
#define RTKp_ 1.0
#define RTKd_ .6
#define RTKi_ .08

// PID ERROR REDUCTION FACTOR
#define PID_RED_ST_ 30
#define PID_RED_RT_ 20


/////////////////////////////////// L3GD20.h /////////////////////////////////////////
#define GYRO_SENSITIVITY ((float)0.1361)
#define GYRO_NOISE_THRESHOLD ((float) 0.95)




#endif /* PARAMETERS__H_ */
