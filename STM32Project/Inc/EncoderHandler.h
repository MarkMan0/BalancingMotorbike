#ifndef _FW_SPD_TRACKER_H
#define _FW_SPD_TRACKER_H 	1

#include "main.h"

#define RAD_PER_PULSE  (0.09817477042)

typedef struct _SpdTracker {

	float currSpd;
	uint32_t lastCnt;
	float ts;
	uint8_t overflowFlag;

} SpdTracker;

extern volatile SpdTracker FWspeed;


void initEncoder();

static inline void calcEncoderSpd() {
	uint32_t curr = LL_TIM_GetCounter(TIM_ENC);
	int32_t diff = 0;
	if(FWspeed.overflowFlag) {
		if(curr < FWspeed.lastCnt) {
			//overflow
			diff = ((uint32_t)(FWspeed.lastCnt - curr));
		} else {
			diff = -1*((uint32_t)(FWspeed.lastCnt - curr));
		}
		FWspeed.overflowFlag = 0;
	}
	else {
		diff = curr - FWspeed.lastCnt;
	}

	FWspeed.currSpd = diff / FWspeed.ts * RAD_PER_PULSE;	//in rad/s
	FWspeed.lastCnt = curr;

}

#endif
