#include "orientation.h"
#include "MPU6050.h"

#include <math.h>

#define DEG_TO_RAD (57.2957795131)

//calculates roll and pitch values
//uses a complementary filter the combine both accelerometer and gyro data
void calcOrientation(Orientation* o){

	const float sampleT = 1.0/1000;

	/*//Normalize accelerometer vector

	//magnitude = sqrt( ax^2 + ay^2 + az^2)
	float magnitude = sqrt(
			powf(o->mpu.acc[0], 2) +
			powf(o->mpu.acc[1], 2) +
			powf(o->mpu.acc[2], 2));

	//calculate the integral of the gyroscope

	for(int i = 0; i < 3; ++i) {
		o->gIntegrated[i] += o->mpu.g[i]*sampleT;
	}

	//calculate the roll and pitch using, by combining both data
	o->roll = asinf(o->mpu.acc[1]/magnitude) + o->gIntegrated[1]*DEG_TO_RAD;
	o->pitch = asinf(0.0 - o->mpu.acc[0]/magnitude) + o->gIntegrated[0] * DEG_TO_RAD;
*/}
