#ifndef _MOVEMENT_CONTROLLER_H
#define _MOVEMENT_CONTROLLER_H 1

#include "stdint.h"

//struct contains the helper and status variables for the servo and the rear motor

typedef struct _MovementControl {

	uint16_t servoPW;
	uint16_t motorPW;
	uint8_t dir;

} MovementControl;


#endif
