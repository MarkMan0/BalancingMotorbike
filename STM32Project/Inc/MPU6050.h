#ifndef _MPU6050_H
#define _MPU6050_H 1

#include "lpf1.h"
#include "hpf1.h"

typedef struct _MPU6050 {

	float accBuff[3];
	float gBuff[3];

} MPU6050;


//this function manages the reading from the I2C device
void readData(MPU6050* mpu);
void MPU6050init(MPU6050* mpu);


#endif
