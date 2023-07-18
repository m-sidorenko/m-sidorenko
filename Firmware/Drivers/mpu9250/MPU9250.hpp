#ifndef __MPU9250_HPP
#define __MPU9250_HPP

#include "stm32f4xx_hal.h"	// set HAL version for your chip

//--------------------------------------------
//    REGISTERS MAP, ADDRESSES AND MACROS

#define		MPU9250_ADDR		0xD0

#define		WHO_AM_I_REG		0x75
#define		PWR_MGM_1_REG		0x6B
#define		PWR_MGM_2_REG		0x6C
#define		SMPLRT_DIV_REG		0x19
#define		EXT_SENS_DATA_00	0x49
#define 	I2C_SLV0_ADDR		0x25
#define 	I2C_SLV0_REG		0x26
#define		I2C_SLV0_DO			0x63
#define		I2C_SLV0_CTRL 		0x27
#define		I2C_SLV0_EN			0x80
#define 	USER_CTRL 			0x6A
#define  	I2C_MST_EN 			0x20
#define 	I2C_MST_CLK 		0x0D
#define 	I2C_MST_CTRL 		0x24

		// gyroscope registers
#define 	GYRO_CONFIG_REG		0x1B
#define 	GYRO_XOUT_H_REG		0x43
#define 	GYRO_XOUT_L_REG		0x44
#define 	GYRO_YOUT_H_REG		0x45
#define 	GYRO_YOUT_L_REG		0x46
#define 	GYRO_ZOUT_H_REG		0x47
#define 	GYRO_ZOUT_L_REG		0x48

		// accelerometer registers
#define 	ACCEL_CONFIG_REG_1	0x1C
#define 	ACCEL_CONFIG_REG_2	0x1D
#define 	ACCEL_XOUT_H_REG	0x3B
#define 	ACCEL_XOUT_L_REG	0x3C
#define 	ACCEL_YOUT_H_REG	0x3D
#define 	ACCEL_YOUT_L_REG	0x3E
#define 	ACCEL_ZOUT_H_REG	0x3F
#define 	ACCEL_ZOUT_L_REG	0x40

		// magnetometer registers 
		// and macros
#define 	AK8963_I2C_ADDR		0x0C
#define 	AK8963_HXL			0x03
#define 	AK8963_CNTL1		0x0A
#define 	AK8963_PWR_DOWN		0x00
#define 	AK8963_CNT_MEAS1	0x12
#define 	AK8963_CNT_MEAS2	0x16
#define 	AK8963_FUSE_ROM		0x0F
#define 	AK8963_CNTL2		0x0B
#define 	AK8963_RESET		0x01
#define 	AK8963_ASA			0x10
#define 	AK8963_WHO_AM_I		0x00


/*----------------------------------------------------------------------------
                            CLASS FOR MPU9250
*---------------------------------------------------------------------------*/

class mpu9250
{

public:

	uint8_t init(I2C_HandleTypeDef* hi2c);

	void read_accel(float* accel_data);
	void read_gyro(float* gyro_data);

private:
	I2C_HandleTypeDef* mpu_hi2c;
	uint16_t mpu_data_rate;
	uint16_t mpu_gyro_cfg;
	uint16_t mpu_accel_cfg;
	
};

#endif /* __MPU9250_HPP */

// ************************** END OF FILE **************************
