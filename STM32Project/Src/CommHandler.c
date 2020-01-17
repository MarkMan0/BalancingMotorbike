#include "CommHandler.h"
#include "BalanceController.h"

static inline void updateServoPW() {
	LL_TIM_OC_SetCompareCH1(TIM_SERVO, MC.servoPW);
}

static inline void updateMotorPWM() {
	if(MC.dir == DIR_FORWARD) {
		//set CH1 to output PWM signal and CH2 to output 0
		LL_TIM_OC_SetCompareCH2(TIM_REAR_PWM, 0);
		LL_TIM_OC_SetCompareCH1(TIM_REAR_PWM, MC.motorPW);
	}
	else {
		//set CH1 to zero and CH2 to PWM
		LL_TIM_OC_SetCompareCH1(TIM_REAR_PWM, 0);
		LL_TIM_OC_SetCompareCH2(TIM_REAR_PWM, MC.motorPW);
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

	return atoi((const char *)cmd);
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

	return atoff((const char *)cmd);
}


static volatile uint8_t startFlag;
void receiveCharCallback(uint8_t c) {
	static uint8_t buffer[UART_RX_BUFLEN];
	static uint8_t ind = 0;
	if(c == 'a') {
		startFlag = 1;	//indicate start
	}
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

void waitUser() {
	startFlag = 0;
	while(!startFlag) {
	  //blink led
	  LL_GPIO_TogglePin(LED_PIN_GPIO_Port, LED_PIN_Pin);
	  LL_mDelay(100);
	}

	LL_GPIO_ResetOutputPin(LED_PIN_GPIO_Port, LED_PIN_Pin);

}

static uint8_t isValid(float val) {
	return (!isnanf(val) && !isinff(val));
}

void handleCommand(uint8_t *cmd) {

	switch(cmd[0]) {
	case 'P':
	case 'p': {
		//turn left
		int16_t pos = getIntFromCmd(cmd);
		MC.servoPW = map(pos, -50, 50, SERVO_PW_MIN, SERVO_PW_MAX);
		//MC.servoPW = CONSTRAIN(MC.servoPW, SERVO_PW_MIN, SERVO_PW_MAX);

		updateServoPW();
		break;
	}

	case 'Q':
	case 'q': {
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

	case 'M':
	case 'm': {
		//current controller Kp
		float val = getFloatFromCmd(cmd);
		if(isValid(val)) {
			CCParams.kp = val;
		}
		break;
	}

	case 'N':
	case 'n': {
		//current controller Ki param
		float val = getFloatFromCmd(cmd);
		if(isValid(val)) {
			CCParams.ki = val;
		}
		break;
	}

	case 'B':
	case 'b': {
		//setpoint for current controller
		float val = getFloatFromCmd(cmd);
		if(isValid(val)) {
			CCParams.setVal = val;
		}
		break;
	}

	case 'V':
	case 'v': {
		//pause current control loop
		updateFlywheelPWM(0);
		LL_TIM_DisableCounter(TIM_CC_LOOP);
		break;
	}

	case 'C':
	case 'c': {
		//restart current control loop
		LL_TIM_SetCounter(TIM_CC_LOOP, 0);
		LL_TIM_EnableCounter(TIM_CC_LOOP);
		break;
	}

	case 'X':
	case 'x': {
		//reset integrator of current control loop
		CCParams.lastI = 0.0;
		break;
	}

	case 'L':
	case 'l': {
		//set Kp for balance controller
		float val = getFloatFromCmd(cmd);
		if(isValid(val)) {
			BCParams.kp = val;
		}
		break;
	}
	case 'K':
	case 'k': {
		//set Kp for balance controller
		float val = getFloatFromCmd(cmd);
		if(isValid(val)) {
			BCParams.ki = val;
		}
		break;
	}
	case 'J':
	case 'j': {
		//set Kp for balance controller
		float val = getFloatFromCmd(cmd);
		if(isValid(val)) {
			BCParams.kd = val;
		}
		break;
	}

	}


}
