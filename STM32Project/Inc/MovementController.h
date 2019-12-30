#ifndef _MOVEMENT_CONTROLLER_H
#define _MOVEMENT_CONTROLLER_H 1

#include "stdint.h"

#define SERVO_PW_MAX	(100)
#define SERVO_PW_MIN	(50)
#define SERVO_PW_STEP	(2)

#define DIR_FORWARD 	(0)
#define DIR_REVERSE 	(1)
#define MOTOR_PW_MIN 	(0)
#define MOTOR_PW_MAX 	(100)


//struct contains the helper and status variables for the servo and the rear motor

typedef struct _MovementControl {

	uint16_t servoPW;
	uint16_t motorPW;
	uint8_t dir;

} MovementControl;

void MC_handleCommand(MovementControl *MC, uint8_t* cmd);

extern MovementControl MC;

#endif
