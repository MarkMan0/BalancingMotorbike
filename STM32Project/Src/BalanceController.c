#include <BalanceController.h>


volatile BalanceContParams BCParams = {
		15, 0.0, 0.0, //kp, ki
		0.0, //last I
		0.0, //last Error
		1.0/2000, 	//time step
		-5, 5,		//output min, max
		0.005 };		//deadzone
