#include "BalanceContParams.h"


volatile BalanceContParams BCParams = {
		0.0, 0.0, //kp, ki
		0.0, //last I
		1.0/2000, 	//time step
		-5, 5,		//output min, max
		2 };		//deadzone
