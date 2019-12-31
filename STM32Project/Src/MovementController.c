#include "MovementController.h"
#include "main.h"
#include "stdlib.h"

#define CONSTRAIN(VAR, MIN, MAX) ( VAR < MIN ? MIN : (VAR > MAX ? MAX : VAR))

MovementControl MC = {0};	//global variable initialization

void updateServoPW(MovementControl *MC) {
	LL_TIM_OC_SetCompareCH1(TIM2, MC->servoPW);
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

void MC_handleCommand(MovementControl *MC, uint8_t* cmd) {

	if(cmd[0] == 'a') {
		//turn left
		MC->servoPW += SERVO_PW_STEP;
		MC->servoPW = CONSTRAIN(MC->servoPW, SERVO_PW_MIN, SERVO_PW_MAX);
		updateServoPW(MC);
	}
	else if(cmd[0] == 'd') {
		//turn right
		MC->servoPW -= SERVO_PW_STEP;
		MC->servoPW = CONSTRAIN(MC->servoPW, SERVO_PW_MIN, SERVO_PW_MAX);
		updateServoPW(MC);
	}
	else if(cmd[0] == 'w' || cmd[0] == 's') {
		//move forward/backward with desired speed
		int16_t spd = getIntFromCmd(cmd);
		MC->motorPW = (uint16_t)(spd/100.0 * MOTOR_PW_MAX);
		MC->motorPW = CONSTRAIN(MC->motorPW, MOTOR_PW_MIN, MOTOR_PW_MAX);

		if(cmd[0] == 'w') {
			MC->dir = DIR_FORWARD;
		}
		else {
			MC->dir = DIR_REVERSE;
		}
		updateMotorPWM(MC);
	}
}
