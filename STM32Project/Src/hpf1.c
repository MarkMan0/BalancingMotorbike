#include "hpf1.h"



float makeReadingHPF1(HPF1* hpf, float data){

	hpf->lastY = hpf->b0*data + hpf->b1*hpf->lastU + hpf->a1*hpf->lastY;
	hpf->lastU = data;

	return hpf->lastY;
}
