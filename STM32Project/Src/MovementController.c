#include <CurrentController.h>
#include "MovementController.h"
#include "main.h"
#include "stdlib.h"
#include "math.h"


volatile MovementControl MC = {0};	//global variable initialization





void initServo() {
	LL_TIM_EnableIT_UPDATE(TIM_SERVO);
	LL_TIM_OC_SetCompareCH1(TIM_SERVO, SERVO_CENTER);
	LL_TIM_CC_EnableChannel(TIM_SERVO, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableAllOutputs(TIM_SERVO);
	LL_TIM_EnableCounter(TIM_SERVO);
}

void initRearMotor() {
	  LL_TIM_OC_SetCompareCH1(TIM_REAR_PWM, 0);
	  LL_TIM_OC_SetCompareCH2(TIM_REAR_PWM, 0);
	  LL_TIM_CC_EnableChannel(TIM_REAR_PWM, LL_TIM_CHANNEL_CH1);
	  LL_TIM_CC_EnableChannel(TIM_REAR_PWM, LL_TIM_CHANNEL_CH2);
	  LL_TIM_EnableCounter(TIM_REAR_PWM);
}


