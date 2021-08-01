#ifndef __PCA9506_HPP__
#define __PCA9506_HPP__

#include <stm32f4xx_hal.h> 		// set HAL version for your chip

#define			I2C_DELAY				50

//--------------------------------------------
//          	I2C ADDRESS

#define         PCA_ADDR_0              0x20 << 1
#define         PCA_ADDR_1              0x21 << 1
#define         PCA_ADDR_2              0x22 << 1
#define         PCA_ADDR_3              0x23 << 1
#define         PCA_ADDR_4              0x24 << 1
#define         PCA_ADDR_5              0x25 << 1
#define         PCA_ADDR_6              0x26 << 1
#define         PCA_ADDR_7              0x27 << 1
#define         PCA_ADDR_8              0x28 << 1

//--------------------------------------------
//              REGISTERS MAP 

        // input port registers
#define         PCA_REG_IP              0x00
#define         PCA_REG_IP0             0x00
#define         PCA_REG_IP1             0x01
#define         PCA_REG_IP2             0x02
#define         PCA_REG_IP3             0x03
#define         PCA_REG_IP4             0x04

        // output port registers
#define         PCA_REG_OP              0x08
#define         PCA_REG_OP0             0x08
#define         PCA_REG_OP1             0x09
#define         PCA_REG_OP2             0x0A
#define         PCA_REG_OP3             0x0B
#define         PCA_REG_OP4             0x0C

    // input\output configuration registers
#define         PCA_REG_IOC             0x18
#define         PCA_REG_IOC0            0x18
#define         PCA_REG_IOC1            0x19
#define         PCA_REG_IOC2            0x1A
#define         PCA_REG_IOC3            0x1B
#define         PCA_REG_IOC4            0x1C


//--------------------------------------------
//               COMANDS

                 // config
#define         PCA_CMD_WR_CFG          PCA_REG_IOC ^ 0x80

                 // write
#define         PCA_CMD_WR_PORTS        PCA_REG_OP  ^ 0x80 
#define         PCA_CMD_WR_PORT         PCA_REG_OP

                 // read
#define         PCA_CMD_RD_PORTS        PCA_REG_IP  ^ 0x80
#define         PCA_CMD_RD_PORT         PCA_REG_IP


/*----------------------------------------------------------------------------
                            CLASS FOR PCA9506
*---------------------------------------------------------------------------*/

class pca9506{

public:

  /* init and config */
  void gpio_init(GPIO_TypeDef* OE_PORT, uint16_t OE_PIN, GPIO_TypeDef* RST_PORT, uint16_t RST_PIN);
  void init(uint16_t pca_addr, I2C_HandleTypeDef* hi2c);
  uint8_t config(uint8_t* ports_config);
  
  /* write operations */
  uint8_t write_all_ports(uint8_t* ports_state);
  uint8_t write_port(uint8_t port_number, uint8_t port_state);
  uint8_t write_pin(uint8_t port_number, uint8_t pin_number, uint8_t pin_state);
  
  /* read operations */
  uint8_t read_all_ports(uint8_t* data);
  uint8_t read_port(uint8_t port_number);
  uint8_t read_pin(uint8_t port_number, uint8_t pin_number);
  
  /* get information */
  uint16_t get_address();
  uint8_t* get_config();

private:
  I2C_HandleTypeDef* pca_hi2c;		// i2c handle
  uint16_t pca_address;				// chip address on I2C bus
  uint8_t  pca_ports_st[5]; 		// ports state
  uint8_t  pca_ports_cfg[5];		// ports configuration

};

#endif
// *********************************** E N D **********************************
