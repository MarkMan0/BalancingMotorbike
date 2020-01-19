#include <BalanceController.h>


volatile BalanceContParams BCParams = { 0 };

void initBalanceController() {
	BCParams.kp = -8;
	BCParams.ki = 0;
	BCParams.kd = 0;
	BCParams.ts = 1.0/1000.0;
	BCParams.outMin = -2.0;
	BCParams.outMax = 2.0;
	BCParams.deadzone = 0.0;

	LL_TIM_EnableIT_UPDATE(TIM_BALANCE_LOOP);
	LL_TIM_EnableCounter(TIM_BALANCE_LOOP);
}
