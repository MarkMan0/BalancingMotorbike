#include <BalanceController.h>


volatile BalanceContParams BCParams = {
		-8, 0.0, 0.0, //kp, ki, kd
		0.0, //last I
		0.0, //last Error
		1.0/1000, 	//time step
		-1, 1,		//output min, max
		0.00 };		//deadzone
