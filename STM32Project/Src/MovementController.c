#include "MovementController.h"



#define CONSTRAIN(VAR, MIN, MAX) ( VAR < MIN ? MIN : (VAR > MAX ? MAX : VAR))

MovementControl MC = {0};	//global variable initialization



void MC_handleCommand(MovementControl *MC, uint8_t* cmd) {

	if(cmd[0] == 'a') {
		//turn left
		MC->servoPW += SERVO_PW_STEP;
		MC->servoPW = CONSTRAIN(MC->servoPW, SERVO_PW_MIN, SERVO_PW_MAX);
	}
	else if(cmd[0] == 'd') {
		//turn right
		MC->servoPW -= SERVO_PW_STEP;
		MC->servoPW = CONSTRAIN(MC->servoPW, SERVO_PW_MIN, SERVO_PW_MAX);
	}
	else if(cmd[0] == 'w') {
		//move forward with desired speed
	}
	else if(cmd[0] == 's') {
		//reverse with desired speed
	}
}
