#ifndef __MPU9250_H
#define __MPU9250_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "stdio.h"

/******** Registers, addresses and macros ********/
#define		MPU9050_ADDR		0xD0

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
//------ gyroscope registers ------
#define 	GYRO_CONFIG_REG		0x1B
#define 	GYRO_XOUT_H_REG		0x43
#define 	GYRO_XOUT_L_REG		0x44
#define 	GYRO_YOUT_H_REG		0x45
#define 	GYRO_YOUT_L_REG		0x46
#define 	GYRO_ZOUT_H_REG		0x47
#define 	GYRO_ZOUT_L_REG		0x48

//---- accelerometer registers ----
#define 	ACCEL_CONFIG_REG_1	0x1C
#define 	ACCEL_CONFIG_REG_2	0x1D
#define 	ACCEL_XOUT_H_REG	0x3B
#define 	ACCEL_XOUT_L_REG	0x3C
#define 	ACCEL_YOUT_H_REG	0x3D
#define 	ACCEL_YOUT_L_REG	0x3E
#define 	ACCEL_ZOUT_H_REG	0x3F
#define 	ACCEL_ZOUT_L_REG	0x40

//---- magnetometer registers and macros----
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
/*****************************************/

#ifdef __cplusplus
extern "C" {
#endif

uint8_t mpu9250_init(void);
void mpu9250_read_accel(float* accel_data);
void mpu9250_read_gyro(float* gyro_data);
void mpu9250_read_magn(uint16_t* magn_data);
void mpu9250_read_all_sensors(uint8_t* accel_data, uint8_t* gyro_data);

void ak8963_write(uint8_t sub_addr, uint8_t data);
void ak8963_read(uint8_t sub_addr, uint8_t size, uint8_t* buff);

#ifdef __cplusplus
}
#endif

#endif /* __MPU9250_H */

// ************************** END OF FILE **************************
