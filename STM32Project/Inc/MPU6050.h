#ifndef _MPU6050_H
#define _MPU6050_H 1

#include "lpf1.h"
#include "hpf1.h"
#include <stdint.h>


//struct to monitor the internal state of the MPU6050
typedef struct _MPU6050 {

	int16_t accBuff[3];
	int16_t gBuff[3];

	float accScale;
	float gScale;

} MPU6050;


void readData(MPU6050* mpu);	//read all 6 axis
void readForRoll(MPU6050* mpu);	//read Y axis only
void MPU6050init(MPU6050* mpu);	//call on startup


#endif
