#include "FWSpdTracker.h"


volatile SpdTracker FWspeed = {0};


void initTracker() {

	FWspeed.lastCnt = LL_TIM_GetAutoReload(TIM_ENC) / 2;
	FWspeed.ts = 1.0/50.0;	//updated in balance ISR

	LL_TIM_SetCounter(TIM_ENC, FWspeed.lastCnt);
	LL_TIM_ClearFlag_UPDATE(TIM_ENC);
	LL_TIM_EnableIT_UPDATE(TIM_ENC);
	LL_TIM_EnableCounter(TIM_ENC);


}
