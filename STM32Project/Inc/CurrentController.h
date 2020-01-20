#ifndef _CURR_CONT_PARAMS_H
#define _CURR_CONT_PARAMS_H		1

//if disable, open loop control is used, the setval changes the motor pwm

//#define CURRENT_CONTROL_CLOSEDLOOP

#include "stdint.h"
#include "main.h"
#include "EncoderHandler.h"

#define ADC_TO_VOLTS		(3.3/4095)

#define FLYWHEELPWM_MAX		(699)
#define FLYWHEELPWM_NEG		(-699)

#define CURRENT_SENSOR_OFFSET	(5.0/2.0)		// Zero current value
#define CURRENT_SENSOR_K		(1.0/0.185)		//Volt / Amps

typedef struct _CurrContParams {
	float kp, ki, lastI;
	float correction;
	float ts;
	float setVal;
	float current;
	float offset;
	float min, max;
	uint16_t adcBuff[2];

} CurrContParams;

extern volatile CurrContParams CCParams;	//global instance


static inline void readCurrent() {
	CCParams.current = CURRENT_SENSOR_K*(CCParams.adcBuff[0]*ADC_TO_VOLTS) - CCParams.offset;
}


static inline void updateFlywheelPWM(float pw) {	//pw is between -1 and 1
	pw = pw*FLYWHEELPWM_MAX;
	pw = CONSTRAIN(pw, FLYWHEELPWM_NEG, FLYWHEELPWM_MAX);

	if(pw >= 0) {
		//TIM1->CH1 ON, TIM1->CH4 OFF
		LL_TIM_OC_SetCompareCH4(TIM_FLYWHELL_PWM, 0);
		LL_TIM_OC_SetCompareCH1(TIM_FLYWHELL_PWM, (uint32_t) pw);
	}
	else {
		LL_TIM_OC_SetCompareCH1(TIM_FLYWHELL_PWM, 0);
		LL_TIM_OC_SetCompareCH4(TIM_FLYWHELL_PWM, (uint32_t) (-1*pw));
	}
}

static inline void currContLoop() {
	readCurrent();

#if defined(CURRENT_CONTROL_CLOSEDLOOP)
	float e = CCParams.setVal - CCParams.current;
	CCParams.lastI += CCParams.ki * e * CCParams.ts;	//perform integration
	CCParams.lastI = CONSTRAIN(CCParams.lastI, -1, 1);	//clamp integral
		updateFlywheelPWM((CCParams.kp * e + CCParams.lastI) + FWspeed.currSpd * CCParams.correction);		//update PWM
#else
	updateFlywheelPWM(CCParams.setVal + CCParams.correction*FWspeed.currSpd);

#endif
}


void initADC();
void initDMA_ADC(uint32_t toAddr, uint32_t sz);
void initTIM_FLYWHEEL();
void initCurrCont();
void calcCurrentSensorOffset();



#endif
