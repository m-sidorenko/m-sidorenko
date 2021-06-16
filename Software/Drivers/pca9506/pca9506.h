#ifndef __PCA9506_H__
#define __PCA9506_H__

#include "types.h"
#include "cpu.h"
#include "gpio.h"

/*
        stm_check_v1 I2C addresses:

        DD4 (OUT 24 V)  ---> PCA_ADDR_0
        DD5 (OUT 220 V) ---> PCA_ADDR_1
        DD6 (INPUT) ---> PCA_ADDR_2
*/

//--------------------------------------------
//             ADDRESS on I2C bus

#define         PCA_ADDR_0              0x20 << 1
#define         PCA_ADDR_1              0x21 << 1
#define         PCA_ADDR_2              0x22 << 1


//--------------------------------------------
//              PCA PINS
 
#define         GPIO_PIN_PCA1_RST       GPIO_PIN_13
#define         GPIO_PORT_PCA1_RST      GPIOC
#define         GPIO_PIN_PCA1_OE        GPIO_PIN_12
#define         GPIO_PORT_PCA1_OE       GPIOC

#define         GPIO_PIN_PCA2_RST       GPIO_PIN_0
#define         GPIO_PORT_PCA2_RST      GPIOD
#define         GPIO_PIN_PCA2_OE        GPIO_PIN_2
#define         GPIO_PORT_PCA2_OE       GPIOD

#define         GPIO_PIN_PCA3_RST       GPIO_PIN_3
#define         GPIO_PORT_PCA3_RST      GPIOC
#define         GPIO_PIN_PCA3_OE        GPIO_PIN_2
#define         GPIO_PORT_PCA3_OE       GPIOC


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

                  //config
#define         PCA_CMD_WR_CFG          PCA_REG_IOC ^ 0x80
                  //read
#define         PCA_CMD_WR_PORTS        PCA_REG_OP  ^ 0x80 
#define         PCA_CMD_WR_PORT         PCA_REG_OP
                  //write
#define         PCA_CMD_RD_PORTS        PCA_REG_IP  ^ 0x80
#define         PCA_CMD_RD_PORT         PCA_REG_IP
      
#define         PCA_SET_PIN             1
#define         PCA_CLR_PIN             0
/*----------------------------------------------------------------------------

                            CLASS FOR PCA9506

*---------------------------------------------------------------------------*/
class pca9506{
  
public:
  byte init(uint8_t pca_addr, I2C_HandleTypeDef* hi2c);
  byte config(uint8_t* ports_config);
  
  /* write operations*/
  byte write_all_ports(uint8_t* ports_state);
  byte write_port(uint8_t port_number, uint8_t port_state);
  byte write_pin(uint8_t port_number, uint8_t pin_number, uint8_t pin_state);
  
  /* read operations */
  byte read_all_ports(uint8_t* data);
  byte read_port(uint8_t port_number);
  byte read_pin(uint8_t port_number, uint8_t pin_number);
  
private:
  I2C_HandleTypeDef* pca_hi2c;
  uint8_t pca_address;
  uint8_t pca_ports_cfg[5] = {0,};
  uint8_t pca_ports_st[5] = {0,};
};  




#endif
// *********************************** E N D **********************************