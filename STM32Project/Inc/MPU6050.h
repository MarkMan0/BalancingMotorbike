#ifndef _MPU6050_H
#define _MPU6050_H 1

#include "lpf1.h"
#include "hpf1.h"

typedef struct _MPU6050 {

	float acc[3];
	float g[3];

	LPF1 lpf[3];
	HPF1 hpf[3];

} MPU6050;


//this function manages the reading from the I2C device
void readData(MPU6050* mpu);
void MPU6050init(MPU6050* mpu);


#endif
