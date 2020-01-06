#ifndef _CURR_CONT_PARAMS_H
#define _CURR_CONT_PARAMS_H		1

//if disable, open loop control is used, the setval changes the motor pwm

//#define CURRENT_CONTROL_CLOSEDLOOP
#ifdef CURRENT_CONTROL_CLOSEDLOOP
	//A correction factor is also applied to the pulse width, from the current speed
	//K is roughly the motor constant  K = voltage[V]/speed[rad/s]
	//#define CURRENT_CONTROL_CORRECTION_FACTOR	(5.5)
#endif

#include "stdint.h"
#include "main.h"

#define FLYWHEELPWM_MAX		(699)
#define FLYWHEELPWM_NEG		(-699)

#define CURRENT_SENSOR_OFFSET	(1.15)		// Zero current value
#define CURRENT_SENSOR_K		(0.185)		//Volt / Amps

typedef struct _CurrContParams {
	float kp, ki, lastI;
	float ts;
	float setVal;
	float current;
	uint16_t adcBuff[2];

} CurrContParams;

extern volatile CurrContParams CCParams;	//global instance


static inline void readCurrent() {
	CCParams.current = CURRENT_SENSOR_K*(CCParams.adcBuff[0]*13513.5 - CURRENT_SENSOR_OFFSET); // 4095*3.3 = 13513.5  <-- adc scale factor @12 bit resolution
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
	#if defined(CURRENT_CONTROL_CORRECTION_FACTOR)
		updateFlywheelPWM((CCParams.kp * e + CCParams.lastI)*CURRENT_CONTROL_CORRECTION_FACTOR);		//update PWM
	#else
		updateFlywheelPWM(CCParams.kp * e + CCParams.lastI);
	#endif
#else
	updateFlywheelPWM(CCParams.setVal);

#endif
}


void initADC();
void init_ADC_DMA(uint32_t toAddr, uint32_t sz);
void initTIM_FLYWHEEL();
void initTIM_CurrCont();


#endif
