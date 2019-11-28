
#ifndef _LPF1_H
#define _LPF1_H	1


//first order low pass filter
//in for b1*z^-1/(1 - a1*z^-1)
typedef struct _LPF1 {

	float lastY, lastU;
	const float b1, a1;

} LPF1;

float makeReadingLPF1(LPF1* lpf, float data);

#endif
