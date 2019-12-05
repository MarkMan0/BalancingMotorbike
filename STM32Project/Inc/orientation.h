#ifndef _ORIENTATION_H
#define _ORIENTATION_H 1

#include "MPU6050.h"

//calculates the orientation of the bike from accelerometer and gyro data

typedef struct _Orientation {

	//helper
	float gIntegrated[3];

	float roll, pitch;
	MPU6050 *mpu;
} Orientation;


void calcOrientation(Orientation* o);


#endif
