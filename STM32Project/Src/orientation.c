#include "orientation.h"
#include "MPU6050.h"

#include <math.h>

#define DEG_TO_RAD (57.2957795131)

//calculates roll and pitch values
//uses a complementary filter the combine both accelerometer and gyro data
void calcOrientation(Orientation* o){

	const float sampleT = 1.0/1000;
	const float coef = 0.95;
	//Normalize accelerometer vector
	float acc[] = {o->mpu.accBuff[0]*o->mpu.accScale,
			 o->mpu.accBuff[1]*o->mpu.accScale,
			 o->mpu.accBuff[2]*o->mpu.accScale },
			g[] = { o->mpu.gBuff[0]*o->mpu.gScale,
			 o->mpu.gBuff[1]*o->mpu.gScale,
			 o->mpu.gBuff[2]*o->mpu.gScale};
	//magnitude = sqrt( ax^2 + ay^2 + az^2)
	float magnitude = sqrt(acc[0]*acc[0] + acc[1]*acc[1] + acc[2]*acc[2]);
	//calculate the integral of the gyroscope


	o->roll = coef*(g[1]*DEG_TO_RAD*sampleT + o->roll) + (1.0-coef)*asinf(acc[1]/magnitude);
	o->pitch = coef*(g[0]*DEG_TO_RAD*sampleT + o->pitch) + (1.0-coef)*asinf(0.0 - acc[0]/magnitude);

}
