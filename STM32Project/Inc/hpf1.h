#ifndef _HPF1_H
#define _HPF1_H	1


//High pass filter in the form of
//
//G = (b0 + b1*z^-1)/(1 + a1*z^-1)

typedef struct _HPF1 {

	float lastY, lastU;
	float b0, b1, a1;

} HPF1;

float makeReadingHPF1(HPF1* lpf, float data);


#endif
