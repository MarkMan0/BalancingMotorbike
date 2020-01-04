#ifndef _CURR_CONT_PARAMS_H
#define _CURR_CONT_PARAMS_H		1

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
	uint16_t adcBuff[2];

} CurrContParams;

extern volatile CurrContParams CCParams;	//global instance


static inline void updateFlywheelPWM(float pw) {	//pw is between -1 and 1
	pw = pw*FLYWHEELPWM_MAX;
	pw = CONSTRAIN(pw, FLYWHEELPWM_NEG, FLYWHEELPWM_MAX);

	if(pw >= 0) {
		//TIM1->CH1 ON, TIM1->CH4 OFF
		LL_TIM_OC_SetCompareCH4(TIM1, 0);
		LL_TIM_OC_SetCompareCH1(TIM1, (uint32_t) pw);
	}
	else {
		LL_TIM_OC_SetCompareCH1(TIM1, 0);
		LL_TIM_OC_SetCompareCH4(TIM1, (uint32_t) (-1*pw));
	}
}

static inline void currContLoop() {
	float e = CCParams.setVal - CURRENT_SENSOR_K*(CCParams.adcBuff[0]*13513.5 - CURRENT_SENSOR_OFFSET);	// 4095*3.3 = 13513.5  <-- adc scale factor @12 bit resolution
	CCParams.lastI += CCParams.ki * e * CCParams.ts;	//perform integration
	CCParams.lastI = CONSTRAIN(CCParams.lastI, -1, 1);	//clamp integral

	updateFlywheelPWM((CCParams.kp * e + CCParams.lastI));		//update PWM
}


#endif