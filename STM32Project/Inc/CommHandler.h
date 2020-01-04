#ifndef _COMM_HANDLER_H
#define _COMM_HANDLER_H		1

#include <stdint.h>
#include "MovementController.h"
#include "CurrContParams.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>

#define UART_RX_BUFLEN 	20

static inline void updateServoPW() {
	LL_TIM_OC_SetCompareCH1(TIM16, MC.servoPW);
}

static inline void updateMotorPWM() {
	if(MC.dir == DIR_FORWARD) {
		//set CH1 to output PWM signal and CH2 to output 0
		LL_TIM_OC_SetCompareCH2(TIM3, 0);
		LL_TIM_OC_SetCompareCH1(TIM3, MC.motorPW);
	}
	else {
		//set CH1 to zero and CH2 to PWM
		LL_TIM_OC_SetCompareCH1(TIM3, 0);
		LL_TIM_OC_SetCompareCH2(TIM3, MC.motorPW);
	}
}

static inline int16_t getIntFromCmd(uint8_t* cmd) {
	++cmd;	//skip first char, which is a letter
	uint16_t i = 0;
	while(cmd[i] != '\0') {
		if(cmd[i] == '\n' || cmd[i] == '\r') {
			cmd[i] = '\0';	//replace trailing newline char, if exists
			break;
		}
		++i;
	}

	return atoi(cmd);
}

static inline float getFloatFromCmd(uint8_t* cmd ){
	++cmd;	//skip first char, which is a letter
	uint16_t i = 0;
	while(cmd[i] != '\0') {
		if(cmd[i] == '\n' || cmd[i] == '\r') {
			cmd[i] = '\0';	//replace trailing newline char, if exists
			break;
		}
		++i;
	}

	return atoff(cmd);
}

static inline int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


static inline void handleCommand(uint8_t *cmd) {

	switch(cmd[0]) {
	case 'p': {
		//turn left
		int16_t pos = getIntFromCmd(cmd);
		MC.servoPW = map(pos, -50, 50, SERVO_PW_MIN, SERVO_PW_MAX);
		//MC.servoPW = CONSTRAIN(MC.servoPW, SERVO_PW_MIN, SERVO_PW_MAX);

		updateServoPW();
		break;
	}
	case 's': {
		//move forward/backward with desired speed
		int16_t spd = getIntFromCmd(cmd);
		if(spd >= 0) {
			MC.dir = DIR_FORWARD;
		} else {
			MC.dir = DIR_REVERSE;
		}
		spd = abs(spd);
		MC.motorPW = (uint16_t)(spd/100.0 * MOTOR_PW_MAX);
		MC.motorPW = CONSTRAIN(MC.motorPW, MOTOR_PW_MIN, MOTOR_PW_MAX);

		updateMotorPWM();
		break;
	}

	case 'm': {
		//current controller Kp
		float val = getFloatFromCmd(cmd);
		if(!isnanf(val) && !isinff(val)) {
			CCParams.kp = val;
		}
		break;
	}

	case 'n': {
		//current controller Ki param
		float val = getFloatFromCmd(cmd);
		if(!isnanf(val) && !isinff(val)) {
			CCParams.ki = val;
		}
		break;
	}

	case 'b': {
		//setpoint for current controller
		float val = getFloatFromCmd(cmd);
		if(!isnanf(val) && !isinff(val)) {
			CCParams.setVal = val;
		}
		break;
	}

	}


}


static inline void receiveCharCallback(uint8_t c) {
	static uint8_t buffer[UART_RX_BUFLEN];
	static uint8_t ind = 0;
	if(ind < UART_RX_BUFLEN) {
		buffer[ind++] = c;
	} else {
		ind = 0;
	}
	if(c == '\n' || c == '\r'  || c == '\0') {
		//end of command
		handleCommand(buffer);
		ind = 0;
	}
	return;
}

#endif
