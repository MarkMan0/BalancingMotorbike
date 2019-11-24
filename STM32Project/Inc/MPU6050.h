#ifndef _MPU6050_H
#define _MPU6050_H 1


typedef struct _MPU6050 {

	float acc[3];
	float g[3];

} MPU6050;


//this function manages the reading from the I2C device
void readData(MPU6050* mpu);
void MPU6050init(MPU6050* mpu);


#endif
