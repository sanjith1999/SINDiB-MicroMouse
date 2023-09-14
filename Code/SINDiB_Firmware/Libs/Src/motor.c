#include "motor.h"
#include "cppmain.h"
#include "L3GD20.h"

int max_limit = 65534;
float base_speed_l = 0.2;
float base_speed_r = 0.2;
const float StKp = 1.0;
const float StKi = 0.00;
const float StKd = 0.00;

int l_start, r_start;
int l_dist, r_dist;
int error, lastErr;
int I;
int cnt = 0;
float correction = 0;
float run_speed_l;
float run_speed_r;

// INITIALIZATIONS
void motorInit(void) {
	// Start PWM for TIM4 channels (you may need to adjust this based on your application)
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);  // LPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);  // LPWMB
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);  // RPWMA
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);  // RPWMB
	setWheels(0, 0);
}

// LEFT WHEEL PLANNER
void setLeftWheel(float l_speed) {
	uint16_t l_pwma, l_pwmb;
	l_pwma = (l_speed >= 0) ? l_speed * max_limit : 0;
	l_pwmb = (l_speed < 0) ? (-l_speed) * max_limit : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, l_pwma);  // LPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, l_pwmb);  // LPWMB
}

void setRightWheel(float r_speed) {
	uint16_t r_pwma, r_pwmb;

	r_pwma = (r_speed >= 0) ? r_speed * max_limit : 0;
	r_pwmb = (r_speed < 0) ? (-r_speed) * max_limit : 0;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, r_pwma);  // RPWMA
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, r_pwmb);  // RPWMB
}

void setWheels(float l_speed, float r_speed) {
	setLeftWheel(l_speed);
	setRightWheel(r_speed);
}

bool straightCounts(int count) {
	uint16_t l_temp, r_temp;
	bool l_away = true, r_away = true;

	l_temp = l_position;
	r_temp = r_position;

	while (l_away || r_away) {
		if (l_position - l_temp < count)
			setLeftWheel(base_speed_l);
		else {
			setLeftWheel(0);
			l_away = false;
		}
		if (r_position - r_temp < count)
			setRightWheel(base_speed_r);
		else {
			setRightWheel(0);
			r_away = false;
		}
	}
	return true;
}

void goLong(int count) {
	for (int i = 0; i < count / 100; i++)
		straightCounts(100);
}

void straightCountsPID(int count) {

	l_start = l_position;
	r_start = r_position;

	while (1) {
		if (l_position >= l_start) {
			l_dist = l_position - l_start;
		} else {
			l_dist = max_limit + l_position - l_start;
		}
		if (r_position <= r_start) {
			r_dist = r_start - r_position;
		} else {
			r_dist = max_limit + r_start - r_position;
		}

		pos_l = l_position;
		pos_r = r_position;

		error = l_dist - r_dist;
		I = I + error;

		correction =
				(float) (error * StKp + I * StKi + (error - lastErr) * StKd)
						/ 50.0;
		lastErr = error;

		if (l_dist < count && r_dist < count) {
			setLeftWheel(base_speed_l - correction);
			setRightWheel(base_speed_r + correction);
//			setLeftWheel(base_speed_l);
//			setRightWheel(base_speed_r);
		} else {
			setLeftWheel(0);
			setRightWheel(0);
			break;
		}

	}
//	return true;
}

void turnLeft(int count) {

	uint16_t rmp = 1000;
	l_start = l_position;
	r_start = r_position;

	cnt = 0;
	run_speed_l = 0;
	run_speed_r = 0;

	while (1) {

		if (l_position <= l_start) {
			l_dist = l_start - l_position;
		} else {
			l_dist = max_limit + l_start - l_position;
		}
		if (r_position <= r_start) {
			r_dist = r_start - r_position;
		} else {
			r_dist = max_limit + r_start - r_position;
		}

		error = l_dist - r_dist;
		I = I + error;

		correction =
				(float) (error * StKp + I * StKi + (error - lastErr) * StKd)
						/ 50.0;
		lastErr = error;

		if (l_dist < count && r_dist < count) {

			if (cnt < rmp) {
				run_speed_l += base_speed_l / (float) rmp;
				run_speed_r += base_speed_r / (float) rmp;
				cnt += 1;
			} else {
				run_speed_l = base_speed_l;
				run_speed_r = base_speed_r;
			}

			setLeftWheel(-run_speed_l + correction);
			setRightWheel(run_speed_r + correction);

		} else {
			if (cnt > 0) {
				run_speed_l -= base_speed_l / (float) rmp;
				run_speed_r -= base_speed_r / (float) rmp;
				cnt -= 1;

				setLeftWheel(-run_speed_l + correction);
				setRightWheel(run_speed_r + correction);
			} else {
				setLeftWheel(0);
				setRightWheel(0);
				break;
			}
		}
	}
}

void turnRight(int count) {

	uint16_t rmp = 1000;
	l_start = l_position;
	r_start = r_position;

	cnt = 0;
	run_speed_l = 0;
	run_speed_r = 0;

	while (1) {

		if (l_position >= l_start) {
			l_dist = l_position - l_start;
		} else {
			l_dist = max_limit + l_position - l_start;
		}
		if (r_position <= r_start) {
			r_dist = r_position - r_start;
		} else {
			r_dist = max_limit + r_position - r_start;
		}

		error = l_dist - r_dist;
		I = I + error;

		correction =
				(float) (error * StKp + I * StKi + (error - lastErr) * StKd)
						/ 50.0;
		lastErr = error;

		if (l_dist < count && r_dist < count) {

			if (cnt < rmp) {
				run_speed_l += base_speed_l / (float) rmp;
				run_speed_r += base_speed_r / (float) rmp;
				cnt += 1;
			} else {
				run_speed_l = base_speed_l;
				run_speed_r = base_speed_r;
			}

			setLeftWheel(run_speed_l - correction);
			setRightWheel(-run_speed_r - correction);

		} else {
			if (cnt > 0) {
				run_speed_l -= base_speed_l / (float) rmp;
				run_speed_r -= base_speed_r / (float) rmp;
				cnt -= 1;

				setLeftWheel(run_speed_l - correction);
				setRightWheel(-run_speed_r - correction);
			} else {
				setLeftWheel(0);
				setRightWheel(0);
				break;
			}
		}
	}
}

void turnLeftGyro(float angle) {

	while (1) {

		error = Angle_Z - angle;
		I = I + error;

		correction =
				(float) (error * StKp + I * StKi + (error - lastErr) * StKd)
						/ 50.0;
		lastErr = error;

		setLeftWheel(-correction);
		setRightWheel(correction);

	}

}
