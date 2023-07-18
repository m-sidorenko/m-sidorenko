#define __MPU9250_CPP__

#include "MPU9250.hpp"

/*----------------------------------------------------------------------------
*						  MPU9250 initialization
*---------------------------------------------------------------------------*/
uint8_t mpu9250::init(I2C_HandleTypeDef* hi2c)
{
	this->mpu_hi2c = hi2c;
	
    uint8_t data = 0;
    
    // Check WHO_AM_I register, the default state is 113
    HAL_I2C_Mem_Read(hi2c, MPU9250_ADDR, WHO_AM_I_REG, 1, &data, 1, 50);
	
    if (data == 113) 
	{

		// Wake the module up
		data = 0;
		HAL_I2C_Mem_Write(hi2c, MPU9250_ADDR, PWR_MGM_1_REG, 1, &data, 1, 50);

		data = 0;
		HAL_I2C_Mem_Write(hi2c, MPU9250_ADDR, PWR_MGM_2_REG, 1, &data, 1, 50);

		// Set data rate of 1KHz
		data = 0x07;
		HAL_I2C_Mem_Write(hi2c, MPU9250_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 50);

		// Configure gyroscope to 250deg/s and accelerometer to +-2g
		data = 0x18;
		HAL_I2C_Mem_Write(hi2c, MPU9250_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 50);
		HAL_I2C_Mem_Write(hi2c, MPU9250_ADDR, ACCEL_CONFIG_REG_1, 1, &data, 1, 50);

		// Enable low pass filter
		data = 0x08;
		HAL_I2C_Mem_Write(hi2c, MPU9250_ADDR, ACCEL_CONFIG_REG_2, 1, &data, 1, 50);

		return 1; // return 1, if all is OK
    } 
	else  
		return 0; 
}


/*----------------------------------------------------------------------------
*						Read data from accelerometer
*---------------------------------------------------------------------------*/
void mpu9250::read_accel(float* accel_data)
{
  uint8_t raw_sensor_data[6] = {0};
  int16_t accel_x_raw = 0, accel_y_raw = 0, accel_z_raw = 0;
  
  
  HAL_I2C_Mem_Read(this->mpu_hi2c, MPU9250_ADDR, ACCEL_XOUT_H_REG, 1, raw_sensor_data, 6, 1000);
  
  accel_x_raw = (int16_t)((raw_sensor_data[0] << 8) | raw_sensor_data[1]);
  accel_y_raw = (int16_t)((raw_sensor_data[2] << 8) | raw_sensor_data[3]);
  accel_z_raw = (int16_t)((raw_sensor_data[4] << 8) | raw_sensor_data[5]);
  
  accel_data[0] = (float)accel_x_raw / 2047.1; // x
  accel_data[1] = (float)accel_y_raw / 2047.1; // y
  accel_data[2] = (float)accel_z_raw / 2047.1; // z
}


/*----------------------------------------------------------------------------
*						Read data from gyroscope
*---------------------------------------------------------------------------*/
void mpu9250::read_gyro(float* gyro_data)
{
  uint8_t raw_sensor_data[6] = {0};
  uint16_t gyro_x_raw = 0, gyro_y_raw = 0, gyro_z_raw = 0;
  
  
  HAL_I2C_Mem_Read(this->mpu_hi2c, MPU9250_ADDR, GYRO_XOUT_H_REG, 1, raw_sensor_data, 6, 1000);
  
  gyro_x_raw = (int16_t)((raw_sensor_data[0] << 8) | raw_sensor_data[1]);
  gyro_y_raw = (int16_t)((raw_sensor_data[2] << 8) | raw_sensor_data[3]);
  gyro_z_raw = (int16_t)((raw_sensor_data[4] << 8) | raw_sensor_data[5]);
  
  gyro_data[0] = (float)gyro_x_raw / 250.0; // x
  gyro_data[1] = (float)gyro_y_raw / 250.0; // y
  gyro_data[2] = (float)gyro_z_raw / 250.0; // z
}



// ************************** END OF FILE **************************
