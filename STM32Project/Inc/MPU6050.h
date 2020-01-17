#ifndef _MPU6050_H
#define _MPU6050_H 1

#include <stdint.h>


//struct to monitor the internal state of the MPU6050
typedef struct _MPU6050 {

	int16_t accBuff[3];
	int16_t gBuff[3];

	int16_t gCorrection[3];
	int16_t accCorrection[3];

	float accScale;
	float gScale;
	uint8_t readFlag;
} MPU6050;


void MPU6050readData(MPU6050* mpu);	//read all 6 axis
void MPU6050readForRoll(MPU6050* mpu);	//read Y axis only
void MPU6050init(MPU6050* mpu);	//call on startup
void MPU6050CalcErr(MPU6050* mpu);	//get gyro error

#endif
