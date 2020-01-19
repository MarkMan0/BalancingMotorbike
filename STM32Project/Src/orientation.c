#include "orientation.h"
#include "MPU6050.h"

#include <math.h>

//calculates roll and pitch values
//uses a complementary filter the combine both accelerometer and gyro data
void calcOrientation(Orientation* o){

	//Calculate actual accelerometer and gyroscope data
	float acc[] = {o->mpu->accBuff[0]*o->mpu->accScale,
			 o->mpu->accBuff[1]*o->mpu->accScale,
			 o->mpu->accBuff[2]*o->mpu->accScale },
			g[] = { o->mpu->gBuff[0]*o->mpu->gScale,
			 o->mpu->gBuff[1]*o->mpu->gScale,
			 o->mpu->gBuff[2]*o->mpu->gScale};

	float roll = atan2f(acc[1], acc[2]);
	o->roll = o->filtParam*(g[0]*o->ts + o->roll) + (1.0-o->filtParam)*asinf(roll);
	if(isnanf(o->roll)) o->roll = 0.0;

	float pitch = atan2((-acc[0]) , sqrt(acc[1]*acc[1] + acc[2]*acc[2]));
	o->pitch = o->filtParam*(g[1]*o->ts + o->pitch) + (1.0-o->filtParam)*pitch;
	if(isnanf(o->pitch)) o->pitch = 0.0;

	o->yaw = g[2]*o->ts + o->yaw;
	if(isnanf(o->yaw)) o->yaw = 0.0;
}

void calcRoll(Orientation* o) {


	float accY = o->mpu->accBuff[1]*o->mpu->accScale,
			accZ = o->mpu->accBuff[2]*o->mpu->accScale,
			g = o->mpu->gBuff[0]*o->mpu->gScale;

	float roll = atan2f(accY, accZ);
	o->roll = o->filtParam*(g*o->ts + o->roll) + (1.0-o->filtParam)*roll;
	if(isnanf(o->roll)) o->roll = 0.0;
}




volatile Orientation orientation = { 0, 0, 0, 0,
		0.75,	//filter
		1.0/1000.0,	//sample time
		-0.05		//level state
};
