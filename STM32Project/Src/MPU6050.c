#include "MPU6050.h"
#include "i2c.h"
#include <stdlib.h>
#include <string.h>
#include "lpf1.h"

void readData(MPU6050* mpu) {
	static uint8_t buff[6];

	memset(buff, 0, 6);
	i2c_read_n(MPU6050_ADDRESS, MPU_6050_REG_ACCEL_XOUT_H, buff, 6);

	for(int i = 0, j = 0; i < 6; i += 2, ++j) {
		int16_t a = buff[i], b = buff[i+1];
		int16_t c = ((a << 8) | b );
		mpu->acc[j] = makeReadingLPF1(&(mpu->lpf[j]), 1.0*c/ 16384.0 );
	}

}
void MPU6050init(MPU6050* mpu) {

	/* TODO:
	 * Initialize the MPU, set up the sampling rate
	 */
	//turn off hpf and lpf (gain=1)

	for(uint8_t i = 0; i < 3; ++i) {
		mpu->hpf[i].b1 = 1;
		mpu->lpf[i].b1 = 1;
	}

	i2c_write(MPU6050_ADDRESS, MPU_6050_REG_PWR_MGMT_1, 0x00);	//reset MPU
}
