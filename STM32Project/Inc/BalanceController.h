#ifndef _BALANCE_CONT_PARAMS_H
#define _BALANCE_CONT_PARAMS_H	1

#include "main.h"
#include "orientation.h"
#include "CurrentController.h"

typedef struct _BalanceContParams {
	float ki, kp, kd;
	float lastI;
	float lastE;
	const float ts;
	const float outMin, outMax;
	const float deadzone;
} BalanceContParams;


extern volatile BalanceContParams BCParams;


static inline void balanceContLoop() {
	calcRoll((Orientation*) &orientation);
	orientation.mpu->readFlag = 1;	//get new reading
	float e = -orientation.roll;

	if(e < BCParams.deadzone && e > -BCParams.deadzone)
		e = 0.0;

	BCParams.lastI += BCParams.ki * BCParams.ts * e;

	float sp = BCParams.kp*e + BCParams.lastI + BCParams.kd/BCParams.ts * (e - BCParams.lastE);
	BCParams.lastE = e;
	CCParams.setVal = CONSTRAIN(sp, BCParams.outMin, BCParams.outMax);

}


#endif
