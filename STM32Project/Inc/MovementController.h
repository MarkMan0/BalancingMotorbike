#ifndef _MOVEMENT_CONTROLLER_H
#define _MOVEMENT_CONTROLLER_H 1

#include "stdint.h"

#define SERVO_PW_MAX	(126)
#define SERVO_PW_MIN	(32)
#define SERVO_CENTER    ((SERVO_PW_MAX + SERVO_PW_MIN)/2)
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

void initServo();
void initRearMotor();

extern volatile MovementControl MC;

#endif
