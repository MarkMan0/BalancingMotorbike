#ifndef _MPU6050_H
#define _MPU6050_H 1

#include "lpf1.h"
#include "hpf1.h"
#include <stdint.h>

typedef struct _MPU6050 {

	int16_t accBuff[3];
	int16_t gBuff[3];

	float accScale;
	float gScale;

} MPU6050;


//this function manages the reading from the I2C device
void readData(MPU6050* mpu);
void MPU6050init(MPU6050* mpu);


#endif
