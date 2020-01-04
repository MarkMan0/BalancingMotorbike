#include "MovementController.h"
#include "main.h"
#include "stdlib.h"
#include "CurrContParams.h"
#include "math.h"


volatile MovementControl MC = {0};	//global variable initialization

void updateServoPW(MovementControl *MC) {
	LL_TIM_OC_SetCompareCH1(TIM16, MC->servoPW);
}

void updateMotorPWM(MovementControl *MC) {
	if(MC->dir == DIR_FORWARD) {
		//set CH1 to output PWM signal and CH2 to output 0
		LL_TIM_OC_SetCompareCH2(TIM3, 0);
		LL_TIM_OC_SetCompareCH1(TIM3, MC->motorPW);
	}
	else {
		//set CH1 to zero and CH2 to PWM
		LL_TIM_OC_SetCompareCH1(TIM3, 0);
		LL_TIM_OC_SetCompareCH2(TIM3, MC->motorPW);
	}
}

int16_t getIntFromCmd(uint8_t* cmd) {
	++cmd;	//skip first char, which is a letter
	size_t i = 0;
	while(cmd[i] != '\0') {
		if(cmd[i] == '\n' || cmd[i] == '\r') {
			cmd[i] = '\0';	//replace trailing newline char, if exists
			break;
		}
		++i;
	}

	return atoi(cmd);
}

float getFloatFromCmd(uint8_t* cmd ){
	++cmd;	//skip first char, which is a letter
	size_t i = 0;
	while(cmd[i] != '\0') {
		if(cmd[i] == '\n' || cmd[i] == '\r') {
			cmd[i] = '\0';	//replace trailing newline char, if exists
			break;
		}
		++i;
	}

	return atoff(cmd);
}

int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void MC_handleCommand(MovementControl *MC, uint8_t* cmd) {

	if(cmd[0] == 'p') {
		//turn left
		int16_t pos = getIntFromCmd(cmd);
		MC->servoPW = map(pos, -50, 50, SERVO_PW_MIN, SERVO_PW_MAX);
		MC->servoPW = CONSTRAIN(MC->servoPW, SERVO_PW_MIN, SERVO_PW_MAX);

		updateServoPW(MC);
	}
	else if(cmd[0] == 's') {
		//move forward/backward with desired speed
		int16_t spd = getIntFromCmd(cmd);
		if(spd >= 0) {
			MC->dir = DIR_FORWARD;
		} else {
			MC->dir = DIR_REVERSE;
		}
		spd = abs(spd);
		MC->motorPW = (uint16_t)(spd/100.0 * MOTOR_PW_MAX);
		MC->motorPW = CONSTRAIN(MC->motorPW, MOTOR_PW_MIN, MOTOR_PW_MAX);

		updateMotorPWM(MC);
	}
	else if(cmd[0] == 'm') {
		//current controller Kp
		float val = getFloatFromCmd(cmd);
		if(!isnanf(val) && !isinff(val)) {
			CCParams.kp = val;
		}
	}
	else if(cmd[0] == 'n') {
		//current controller Ki param
		float val = getFloatFromCmd(cmd);
		if(!isnanf(val) && !isinff(val)) {
			CCParams.ki = val;
		}
	}
	else if(cmd[0] == 'b') {
		//setpoint for current controller
		float val = getFloatFromCmd(cmd);
		if(!isnanf(val) && !isinff(val)) {
			CCParams.setVal = val;
		}
	}
}


void initServo() {
	LL_TIM_OC_SetCompareCH1(TIM16, SERVO_CENTER);
	LL_TIM_CC_EnableChannel(TIM16, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableAllOutputs(TIM16);
	LL_TIM_EnableCounter(TIM16);
}

void initRearMotor() {
	  LL_TIM_OC_SetCompareCH1(TIM3, 0);
	  LL_TIM_OC_SetCompareCH2(TIM3, 0);
	  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
	  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH2);
	  LL_TIM_EnableCounter(TIM3);
}


