#ifndef _BALANCE_CONT_PARAMS_H
#define _BALANCE_CONT_PARAMS_H	1


typedef struct _BalanceContParams {
	float ki, kp;
	float lastI;
	const float ts;
	const float outMin, outMax;
	const float deadzone;
} BalanceContParams;

extern volatile BalanceContParams BCParams;
#endif
