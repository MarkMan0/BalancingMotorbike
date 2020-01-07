#include "MPU6050.h"
#include "i2c.h"
#include <stdlib.h>
#include <string.h>

#include "MPU6050_Registers.h"

//reads all 6 data via I2C
void readData(MPU6050* mpu) {
	i2c_read3_int16(MPU6050_ADDRESS, MPU_6050_REG_ACCEL_XOUT_H,(uint8_t*) mpu->accBuff);

	i2c_read3_int16(MPU6050_ADDRESS, MPU_6050_REG_GYRO_XOUT_H, (uint8_t*) mpu->gBuff);
}

//reads the y accelerometer and gyroscope data
void readForRoll(MPU6050* mpu) {
	i2c_read_int16(MPU6050_ADDRESS, MPU_6050_REG_ACCEL_YOUT_H, (uint8_t*)(mpu->accBuff+1));
	i2c_read_int16(MPU6050_ADDRESS, MPU_6050_REG_GYRO_XOUT_H, (uint8_t*)(mpu->gBuff));
}


//sets the init condition in the MPU, via I2C
//sets up gains and internal filters
void MPU6050init(MPU6050* mpu) {

	//set the default scale values
	mpu->accScale = 1.0/16384.0;
	mpu->gScale = 1.0/131.0;

	i2c_write(MPU6050_ADDRESS, MPU_6050_REG_PWR_MGMT_1, 0x00);	//reset MPU
}
