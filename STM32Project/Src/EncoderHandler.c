#include <EncoderHandler.h>


volatile SpdTracker FWspeed = {0};


void initEncoder() {

	FWspeed.lastCnt = LL_TIM_GetAutoReload(TIM_ENC) / 2;	//start counting from the middle of possible values

	FWspeed.ts = 1.0/50.0;		//to calculate speed
	LL_TIM_EnableIT_UPDATE(TIM_SERVO);  //for velocity calculation

	LL_TIM_SetCounter(TIM_ENC, FWspeed.lastCnt);
	LL_TIM_ClearFlag_UPDATE(TIM_ENC);
	LL_TIM_EnableIT_UPDATE(TIM_ENC);
	LL_TIM_EnableCounter(TIM_ENC);


}
