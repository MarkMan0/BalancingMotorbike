#ifndef _ORIENTATION_H
#define _ORIENTATION_H 1

#include "MPU6050.h"

//calculates the orientation of the bike from accelerometer and gyro data

typedef struct _Orientation {

	float roll, pitch, yaw;
	volatile MPU6050 *mpu;

	const float filtParam;
	const float ts;
	const float levelState;
} Orientation;

//calculate all 6 axes
void calcOrientation(Orientation* o);

//calculate roll only, using y axis accelerometer and gyroscope data
void calcRoll(Orientation* o);


extern volatile Orientation orientation;

#endif
