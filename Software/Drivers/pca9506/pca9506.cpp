#define __PCA9506_C__

#include "pca9506.h"
#include "stm32g0xx_hal_i2c.h"

/*----------------------------------------------------------------------------
*                            PCA INITIALIZATION
*---------------------------------------------------------------------------*/
byte pca9506::init(uint8_t pca_addr, I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  pca_hi2c = hi2c;
  
  if ( pca_addr == 0 ) 
  {
    pca_address = PCA_ADDR_0;
    
    // -------------------- GPIO init --------------------
    GPIO_InitStruct.Pin = GPIO_PIN_PCA1_RST;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(GPIO_PORT_PCA1_RST, &GPIO_InitStruct);
    SET_GPIO(GPIO_PORT_PCA1_RST, GPIO_PIN_PCA1_RST);
    
    GPIO_InitStruct.Pin = GPIO_PIN_PCA1_OE;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(GPIO_PORT_PCA1_OE, &GPIO_InitStruct);
    CLR_GPIO(GPIO_PORT_PCA1_OE, GPIO_PIN_PCA1_OE);
    
    return 1;
  }
  else if ( pca_addr == 1 ) 
  {
    pca_address = PCA_ADDR_1;
    
    // -------------------- GPIO init --------------------
    GPIO_InitStruct.Pin = GPIO_PIN_PCA2_RST;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(GPIO_PORT_PCA2_RST, &GPIO_InitStruct);
    SET_GPIO(GPIO_PORT_PCA2_RST, GPIO_PIN_PCA2_RST);
    
    GPIO_InitStruct.Pin = GPIO_PIN_PCA2_OE;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(GPIO_PORT_PCA2_OE, &GPIO_InitStruct);
    CLR_GPIO(GPIO_PORT_PCA2_OE, GPIO_PIN_PCA2_OE);
    
    return 1;
  }
  else if ( pca_addr == 2 ) 
  {
    pca_address = PCA_ADDR_2;
    
    // -------------------- GPIO init --------------------
    GPIO_InitStruct.Pin = GPIO_PIN_PCA3_RST;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(GPIO_PORT_PCA3_RST, &GPIO_InitStruct);
    SET_GPIO(GPIO_PORT_PCA3_RST, GPIO_PIN_PCA3_RST);
    
    GPIO_InitStruct.Pin = GPIO_PIN_PCA3_OE;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(GPIO_PORT_PCA3_OE, &GPIO_InitStruct);
    CLR_GPIO(GPIO_PORT_PCA3_OE, GPIO_PIN_PCA3_OE);
    
    return 1;
  }    
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                         PCA CONFIGURATION
*---------------------------------------------------------------------------*/
byte pca9506::config(uint8_t* ports_config)
{
  uint8_t data[6] = {PCA_CMD_WR_CFG, 0,0,0,0,0};
 
  for (byte i = 0; i < 5; i++)
  {
    data[i+1] = ports_config[i];
    pca_ports_cfg[i] = ports_config[i]; // new current config of port
  }
  
  if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 6, 150) == HAL_OK )
    return 1;
  else 
    return 0;
}


/*----------------------------------------------------------------------------
*                            WRITE ALL PCA PORTS
*---------------------------------------------------------------------------*/
byte pca9506::write_all_ports(uint8_t* pca_ports_state)
{
  uint8_t data[6] = {PCA_CMD_WR_PORTS, 0,0,0,0,0};
  
  for (byte i = 0; i < 5; i++)
  {
    data[i+1] = pca_ports_state[i];
    pca_ports_st[i] = pca_ports_state[i]; // new current state of ports
  }
  
  if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 6, 150) == HAL_OK )
    return 1;
  else
    return 0;
}


/*----------------------------------------------------------------------------
*                           WRITE ONE PCA PORT
*---------------------------------------------------------------------------*/
byte pca9506::write_port(uint8_t port_number, uint8_t port_state)
{
  uint8_t data[2] = {0,};
  
  if ( port_number >= 0 && port_number < 5 )
  {  
    data[0] = PCA_CMD_WR_PORT + port_number;
    data[1] = port_state;
    pca_ports_st[port_number] = port_state; // new current state of port
      
    if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 2, 50) == HAL_OK )
      return 1;
    else
      return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                           WRITE ONE PCA PIN
*---------------------------------------------------------------------------*/
byte pca9506::write_pin(uint8_t port_number, uint8_t pin_number, uint8_t pin_state)
{
  uint8_t data[2] = {0,};
  
  if ( (port_number >= 0 && port_number < 5) && (pin_number >= 0 && pin_number < 8) )
  {  
    data[0] = PCA_CMD_WR_PORT + port_number; 
    
    if ( pin_state )  
      data[1] = pca_ports_st[port_number] | (1 << pin_number);
    else
      data[1] = pca_ports_st[port_number] ^ (1 << pin_number);
    
    pca_ports_st[port_number] = data[1]; // new current state of port
    
    if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 2, 50) == HAL_OK )
      return 1;
    else
      return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                               READ ALL PCA PORTS
*---------------------------------------------------------------------------*/
byte pca9506::read_all_ports(uint8_t* data)
{ 
  if ( HAL_I2C_Mem_Read(pca_hi2c, pca_address, PCA_CMD_RD_PORTS, I2C_MEMADD_SIZE_8BIT, data, 5, 150) == HAL_OK )
  {
    for (byte i = 0; i < 5; i++)
      pca_ports_st[i] = data[i]; // new current state of ports
      
    return 1;
  }
  else
    return 0;
}


/*----------------------------------------------------------------------------
*                                READ ONE PCA PORT
*---------------------------------------------------------------------------*/
byte pca9506::read_port(uint8_t port_number)
{ 
  uint8_t command = 0;
  uint8_t port = 0;
  
  if ( port_number >= 0 && port_number < 5 )
  {
    command = PCA_CMD_RD_PORT + port_number;
    
    if ( HAL_I2C_Mem_Read(pca_hi2c, pca_address, command, I2C_MEMADD_SIZE_8BIT, &port, 1, 150) == HAL_OK )
    {
      pca_ports_st[port_number] = port; // new current state of port
      return port;
    }   
    else
      return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                                READ ONE PCA PIN
*---------------------------------------------------------------------------*/
byte pca9506::read_pin(uint8_t port_number, uint8_t pin_number)
{ 
  uint8_t port = 0;
  
  if ( (port_number >= 0 && port_number < 5) && (pin_number >= 0 && pin_number < 8) )
  {
    port = read_port(port_number);
    
    if ( port & 1<<pin_number )
       return 1;
    else 
       return 0;
  }
  else return 0; // INPUT MISTAKE
}

// *********************************** E N D **********************************

