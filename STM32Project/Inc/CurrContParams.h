#ifndef _CURR_CONT_PARAMS_H
#define _CURR_CONT_PARAMS_H		1

#include "stdint.h"

typedef struct _CurrContParams {
	float kp, ki, lastI;
	float ts;
	float setVal;
	uint16_t adcBuff[2];

} CurrContParams;

extern volatile CurrContParams CCParams;	//global instance

#endif
