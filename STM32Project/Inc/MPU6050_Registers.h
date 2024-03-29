#ifndef _MPU6050_REGISTERS_H
#define _MPU6050_REGISTERS_H 1


//register addresses
#define MPU_6050_REG_SELF_TEST_X			(uint8_t)(0x0D)
#define MPU_6050_REG_SELF_TEST_Y			(uint8_t)(0x0E)
#define MPU_6050_REG_SELF_TEST_Z			(uint8_t)(0x0F)
#define MPU_6050_REG_SELF_TEST_A			(uint8_t)(0x10)
#define MPU_6050_REG_SMPLRT_DIV				(uint8_t)(0x19)
#define MPU_6050_REG_CONFIG					(uint8_t)(0x1A)
#define MPU_6050_REG_GYRO_CONFIG			(uint8_t)(0x1B)
#define MPU_6050_REG_ACCEL_CONFIG			(uint8_t)(0x1C)
#define MPU_6050_REG_FIFO_EN				(uint8_t)(0x23)
#define MPU_6050_REG_I2C_MST_CTRL			(uint8_t)(0x24)
#define MPU_6050_REG_I2C_SLV0_ADDR			(uint8_t)(0x25)
#define MPU_6050_REG_I2C_SLV0_REG			(uint8_t)(0x26)
#define MPU_6050_REG_I2C_SLV0_CTRL			(uint8_t)(0x27)
#define MPU_6050_REG_I2C_SLV1_ADDR			(uint8_t)(0x28)
#define MPU_6050_REG_I2C_SLV1_REG			(uint8_t)(0x29)
#define MPU_6050_REG_I2C_SLV1_CTRL			(uint8_t)(0x2A)
#define MPU_6050_REG_I2C_SLV2_ADDR			(uint8_t)(0x2B)
#define MPU_6050_REG_I2C_SLV2_REG			(uint8_t)(0x2C)
#define MPU_6050_REG_I2C_SLV2_CTRL			(uint8_t)(0x2D)
#define MPU_6050_REG_I2C_SLV3_ADDR			(uint8_t)(0x2E)
#define MPU_6050_REG_I2C_SLV3_REG			(uint8_t)(0x2F)
#define MPU_6050_REG_I2C_SLV3_CTRL			(uint8_t)(0x30)
#define MPU_6050_REG_I2C_SLV4_ADDR			(uint8_t)(0x31)
#define MPU_6050_REG_I2C_SLV4_REG			(uint8_t)(0x32)
#define MPU_6050_REG_I2C_SLV4_DO			(uint8_t)(0x33)
#define MPU_6050_REG_I2C_SLV4_CTRL			(uint8_t)(0x34)
#define MPU_6050_REG_I2C_SLV4_DI			(uint8_t)(0x35)
#define MPU_6050_REG_I2C_MST_STATUS			(uint8_t)(0x36)
#define MPU_6050_REG_INT_PIN_CFG			(uint8_t)(0x37)
#define MPU_6050_REG_INT_ENABLE				(uint8_t)(0x38)
#define MPU_6050_REG_INT_STATUS				(uint8_t)(0x3A)
#define MPU_6050_REG_ACCEL_XOUT_H			(uint8_t)(0x3B)
#define MPU_6050_REG_ACCEL_XOUT_L			(uint8_t)(0x3C)
#define MPU_6050_REG_ACCEL_YOUT_H			(uint8_t)(0x3D)
#define MPU_6050_REG_ACCEL_YOUT_L			(uint8_t)(0x3E)
#define MPU_6050_REG_ACCEL_ZOUT_H			(uint8_t)(0x3F)
#define MPU_6050_REG_ACCEL_ZOUT_L			(uint8_t)(0x40)
#define MPU_6050_REG_TEMP_OUT_H				(uint8_t)(0x41)
#define MPU_6050_REG_TEMP_OUT_L				(uint8_t)(0x42)
#define MPU_6050_REG_GYRO_XOUT_H			(uint8_t)(0x43)
#define MPU_6050_REG_GYRO_XOUT_L			(uint8_t)(0x44)
#define MPU_6050_REG_GYRO_YOUT_H			(uint8_t)(0x45)
#define MPU_6050_REG_GYRO_YOUT_L			(uint8_t)(0x46)
#define MPU_6050_REG_GYRO_ZOUT_H			(uint8_t)(0x47)
#define MPU_6050_REG_GYRO_ZOUT_L			(uint8_t)(0x48)
#define MPU_6050_REG_EXT_SENS_DATA_00		(uint8_t)(0x49)
#define MPU_6050_REG_EXT_SENS_DATA_01		(uint8_t)(0x4A)
#define MPU_6050_REG_EXT_SENS_DATA_02		(uint8_t)(0x4B)
#define MPU_6050_REG_EXT_SENS_DATA_03		(uint8_t)(0x4C)
#define MPU_6050_REG_EXT_SENS_DATA_04		(uint8_t)(0x4D)
#define MPU_6050_REG_EXT_SENS_DATA_05		(uint8_t)(0x4E)
#define MPU_6050_REG_EXT_SENS_DATA_06		(uint8_t)(0x4F)
#define MPU_6050_REG_EXT_SENS_DATA_07		(uint8_t)(0x50)
#define MPU_6050_REG_EXT_SENS_DATA_08		(uint8_t)(0x51)
#define MPU_6050_REG_EXT_SENS_DATA_09		(uint8_t)(0x52)
#define MPU_6050_REG_EXT_SENS_DATA_10		(uint8_t)(0x53)
#define MPU_6050_REG_EXT_SENS_DATA_11		(uint8_t)(0x54)
#define MPU_6050_REG_EXT_SENS_DATA_12		(uint8_t)(0x55)
#define MPU_6050_REG_EXT_SENS_DATA_13		(uint8_t)(0x56)
#define MPU_6050_REG_EXT_SENS_DATA_14		(uint8_t)(0x57)
#define MPU_6050_REG_EXT_SENS_DATA_15		(uint8_t)(0x58)
#define MPU_6050_REG_EXT_SENS_DATA_16		(uint8_t)(0x59)
#define MPU_6050_REG_EXT_SENS_DATA_17		(uint8_t)(0x5A)
#define MPU_6050_REG_EXT_SENS_DATA_18		(uint8_t)(0x5B)
#define MPU_6050_REG_EXT_SENS_DATA_19		(uint8_t)(0x5C)
#define MPU_6050_REG_EXT_SENS_DATA_20		(uint8_t)(0x5D)
#define MPU_6050_REG_EXT_SENS_DATA_21		(uint8_t)(0x5E)
#define MPU_6050_REG_EXT_SENS_DATA_22		(uint8_t)(0x5F)
#define MPU_6050_REG_EXT_SENS_DATA_23		(uint8_t)(0x60)
#define MPU_6050_REG_I2C_SLV0_DO			(uint8_t)(0x63)
#define MPU_6050_REG_I2C_SLV1_DO			(uint8_t)(0x64)
#define MPU_6050_REG_I2C_SLV2_DO			(uint8_t)(0x65)
#define MPU_6050_REG_I2C_SLV3_DO			(uint8_t)(0x66)
#define MPU_6050_REG_I2C_MST_DELAY_CTRL		(uint8_t)(0x67)
#define MPU_6050_REG_SIGNAL_PATH_RESET		(uint8_t)(0x68)
#define MPU_6050_REG_USER_CTRL				(uint8_t)(0x6A)
#define MPU_6050_REG_PWR_MGMT_1				(uint8_t)(0x6B)
#define MPU_6050_REG_PWR_MGMT_2				(uint8_t)(0x6C)
#define MPU_6050_REG_FIFO_COUNTH			(uint8_t)(0x72)
#define MPU_6050_REG_FIFO_COUNTL			(uint8_t)(0x73)
#define MPU_6050_REG_FIFO_R_W				(uint8_t)(0x74)
#define MPU_6050_REG_WHO_AM_I				(uint8_t)(0x75)



//config register modes
#define MPU_6050_CONFIG_FSYNC_DISABLED      (uint8_t)(0x00 << 3)
#define MPU_6050_CONFIG_FSYNC_TEMPOUT       (uint8_t)(0x01 << 3)
#define MPU_6050_CONFIG_FSYNC_GYRO_X        (uint8_t)(0x02 << 3)
#define MPU_6050_CONFIG_FSYNC_GYRO_Y        (uint8_t)(0x03 << 3)
#define MPU_6050_CONFIG_FSYNC_GYRO_Z        (uint8_t)(0x04 << 3)
#define MPU_6050_CONFIG_FSYNC_ACCEL_X       (uint8_t)(0x05 << 3)
#define MPU_6050_CONFIG_FSYNC_ACCEL_Y       (uint8_t)(0x06 << 3)
#define MPU_6050_CONFIG_FSYNC_ACCEL_Z       (uint8_t)(0x07 << 3)

#define MPU_6050_CONFIG_LPF_0               (uint8_t)(0x00)
#define MPU_6050_CONFIG_LPF_1               (uint8_t)(0x01)
#define MPU_6050_CONFIG_LPF_2               (uint8_t)(0x02)
#define MPU_6050_CONFIG_LPF_3               (uint8_t)(0x03)
#define MPU_6050_CONFIG_LPF_4               (uint8_t)(0x04)
#define MPU_6050_CONFIG_LPF_5               (uint8_t)(0x05)
#define MPU_6050_CONFIG_LPF_6               (uint8_t)(0x06)



//gyro config register
#define MPU_6050_GYRO_CNFG_250              (uint8_t)(0x00 << 3)
#define MPU_6050_GYRO_CNFG_500              (uint8_t)(0x01 << 3)
#define MPU_6050_GYRO_CNFG_1000             (uint8_t)(0x02 << 3)
#define MPU_6050_GYRO_CNFG_2000             (uint8_t)(0x03 << 3)
#define MPU_6050_GYRO_CNFG_X_STEST          (uint8_t)(0x01 << 7)
#define MPU_6050_GYRO_CNFG_Y_STEST          (uint8_t)(0x01 << 6)
#define MPU_6050_GYRO_CNFG_Z_STEST          (uint8_t)(0x01 << 5)


//accelerometer config register
#define MPU_6050_ACCEL_CNFG_2               (uint8_t)(0x00 << 3)
#define MPU_6050_ACCEL_CNFG_4               (uint8_t)(0x01 << 3)
#define MPU_6050_ACCEL_CNFG_8               (uint8_t)(0x02 << 3)
#define MPU_6050_ACCEL_CNFG_16              (uint8_t)(0x03 << 3)
#define MPU_6050_ACCEL_CNFG_X_STEST         (uint8_t)(0x01 << 7)
#define MPU_6050_ACCEL_CNFG_Y_STEST         (uint8_t)(0x01 << 6)
#define MPU_6050_ACCEL_CNFG_Z_STEST         (uint8_t)(0x01 << 5)

//INT pin config register
#define MPU_6050_INT_CFG_LEVEL_H            (uint8_t)(0x00 << 7)
#define MPU_6050_INT_CFG_LEVEL_L            (uint8_t)(0x01 << 7)
#define MPU_6050_INT_CFG_PP                 (uint8_t)(0x00 << 6)
#define MPU_6050_INT_CFG_OD                 (uint8_t)(0x01 << 6)
#define MPU_6050_INT_CFG_PULSE              (uint8_t)(0x00 << 5)
#define MPU_6050_INT_CFG_LATCH              (uint8_t)(0x01 << 5)


//INT enable register
#define MPU_6050_INT_EN_FIFO                (uint8_t)(0x01 << 4)
#define MPU_6050_INT_EN_I2C                 (uint8_t)(0x01 << 3)
#define MPU_6050_INT_EN_DR                  (uint8_t)(0x01)


//power management
#define MPU_6050_PWR_MAN_1_CLK_INT          (uint8_t)(0x00)
#define MPU_6050_PWR_MAN_1_CLK_X_GYRO       (uint8_t)(0x01)
#define MPU_6050_PWR_MAN_1_CLK_Y_GYRO       (uint8_t)(0x01)
#define MPU_6050_PWR_MAN_1_CLK_Z_GYRO       (uint8_t)(0x01)

#define MPU_6050_PWR_MAN_2_WAKE_125HZ       (uint8_t)(0x00 << 6)
#define MPU_6050_PWR_MAN_2_WAKE_5HZ         (uint8_t)(0x01 << 6)
#define MPU_6050_PWR_MAN_2_WAKE_20HZ        (uint8_t)(0x02 << 6)
#define MPU_6050_PWR_MAN_2_WAKE_40HZ        (uint8_t)(0x03 << 6)

#define MPU_6050_PWR_MAN_2_SB_XA            (uint8_t)(0x01 << 5)
#define MPU_6050_PWR_MAN_2_SB_YA            (uint8_t)(0x01 << 4)
#define MPU_6050_PWR_MAN_2_SB_ZA            (uint8_t)(0x01 << 3)
#define MPU_6050_PWR_MAN_2_SB_XG            (uint8_t)(0x01 << 2)
#define MPU_6050_PWR_MAN_2_SB_YG            (uint8_t)(0x01 << 1)
#define MPU_6050_PWR_MAN_2_SB_ZG            (uint8_t)(0x01 << 0)

#define MPU6050_ADDRESS           				(uint8_t)(0xD0)


#endif
