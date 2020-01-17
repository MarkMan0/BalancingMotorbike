#include "MPU6050.h"
#include "i2c.h"
#include <stdlib.h>
#include <string.h>

#include "MPU6050_Registers.h"

//reads all 6 data via I2C
void MPU6050readData(MPU6050* mpu) {
	i2c_read3_int16(MPU6050_ADDRESS, MPU_6050_REG_ACCEL_XOUT_H,(uint8_t*) mpu->accBuff);
	i2c_read3_int16(MPU6050_ADDRESS, MPU_6050_REG_GYRO_XOUT_H, (uint8_t*) mpu->gBuff);

	//apply offsets
	for(int8_t i = 0; i < 3; ++i) {
		mpu->accBuff[i] -= mpu->accCorrection[i];
		mpu->gBuff[i] -= mpu->gCorrection[i];
	}
}

//reads the y accelerometer and gyroscope data
void MPU6050readForRoll(MPU6050* mpu) {
	i2c_read_int16(MPU6050_ADDRESS, MPU_6050_REG_ACCEL_YOUT_H, (uint8_t*)(mpu->accBuff+1));
	mpu->accBuff[1] -= mpu->accCorrection[1];
	i2c_read_int16(MPU6050_ADDRESS, MPU_6050_REG_GYRO_XOUT_H, (uint8_t*)(mpu->gBuff));
	mpu->gBuff[0] -= mpu->gCorrection[0];
}


//sets the init condition in the MPU, via I2C
//sets up gains and internal filters
void MPU6050init(MPU6050* mpu) {

	//set the default scale values
	mpu->accScale = 1.0/16384.0;
	mpu->gScale = 1.0/131.0;

	i2c_write(MPU6050_ADDRESS, MPU_6050_REG_PWR_MGMT_1, 0x00);	//reset MPU
	i2c_write(MPU6050_ADDRESS, MPU_6050_REG_CONFIG, 0x02);		//enable filter
}


void MPU6050CalcErr(MPU6050* mpu) {
	//the robot should be still
	//the expected value for all gyro readings is 0
	//do N number of readings, the average will be the offset for each axis

	const int16_t accExpected[] = {0, 0, 0};	//TODO: find values, at least for y

	for(int8_t i = 0; i < 3; ++i) {
		mpu->gCorrection[i] = 0;
		mpu->accCorrection[i] = 0;
	}

	const int16_t N = 500;
	int32_t sum[6];
	for(int8_t i = 0; i < 6; ++i) {
		sum[i] = 0;
	}
	for(int16_t i = 0; i < N; ++i) {
		MPU6050readData(mpu);
		for(int8_t i =0; i < 3; ++i) {
			sum[i] += mpu->accBuff[i] - accExpected[i];
		}
		for(int8_t i = 3; i < 6; ++i) {
			sum[i] += mpu->gBuff[i-3];
		}
		LL_mDelay(2); //gyro refresh rate is 1Khz. This to make sure that always reading new data
	}

	for(int8_t i = 0; i < 3; ++i) {
		//mpu->accCorrection[i] = (int16_t) (1.0*sum[i] / N);
		mpu->gCorrection[i] = (int16_t) (1.0*sum[i+3] / N);
	}

}

