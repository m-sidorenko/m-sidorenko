#define __PCA9506_CPP__

#include <pca9506.hpp>

/*----------------------------------------------------------------------------
*                     PCA RST AND OE PINS INITIALIZATION
*---------------------------------------------------------------------------*/
void pca9506::gpio_init(GPIO_TypeDef* OE_PORT,  uint16_t OE_PIN,
						GPIO_TypeDef* RST_PORT, uint16_t RST_PIN)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	// -------------------- OE PIN INIT --------------------
    GPIO_InitStruct.Pin = OE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(OE_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(OE_PORT, OE_PIN, GPIO_PIN_SET);
    
	// -------------------- RST PIN INIT --------------------
    GPIO_InitStruct.Pin = RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  
    HAL_GPIO_Init(RST_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(RST_PORT, RST_PIN, GPIO_PIN_RESET);
	
}

/*----------------------------------------------------------------------------
*                            PCA INITIALIZATION
*---------------------------------------------------------------------------*/
void pca9506::init(uint16_t pca_addr, I2C_HandleTypeDef* hi2c)
{
  this->pca_hi2c = hi2c;

  this->pca_address = pca_addr;
}


/*----------------------------------------------------------------------------
*                         	 PCA CONFIGURATION
*---------------------------------------------------------------------------*/
uint8_t pca9506::config(uint8_t* ports_config)
{
  uint8_t data[6] = {PCA_CMD_WR_CFG, 0,0,0,0,0};

  for (uint8_t i = 0; i < 5; i++)
  {
    data[i+1] = ports_config[i];
    this->pca_ports_cfg[i] = ports_config[i]; // new current configuration of port
  }
  
  if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 6, I2C_DELAY*3) == HAL_OK )
    return 1;
  else 
    return 0;
}


/*----------------------------------------------------------------------------
*                            WRITE ALL PCA PORTS
*---------------------------------------------------------------------------*/
uint8_t pca9506::write_all_ports(uint8_t* pca_ports_state)
{
  uint8_t data[6] = {PCA_CMD_WR_PORTS, 0,0,0,0,0};
  
  for (uint8_t i = 0; i < 5; i++)
  {
    data[i+1] = pca_ports_state[i];
    this->pca_ports_st[i] = pca_ports_state[i]; // new current state of ports
  }
  
  if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 6, I2C_DELAY*3) == HAL_OK )
    return 1;
  else
    return 0;
}


/*----------------------------------------------------------------------------
*                           WRITE ONE PCA PORT
*---------------------------------------------------------------------------*/
uint8_t pca9506::write_port(uint8_t port_number, uint8_t port_state)
{
  uint8_t data[2] = {0,};
  
  if ( port_number < 5 )
  {  
    data[0] = PCA_CMD_WR_PORT + port_number;
    data[1] = port_state;

    this->pca_ports_st[port_number] = port_state; // new current state of port
      
    if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 2, I2C_DELAY) == HAL_OK )
      return 1;
    else
      return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                           WRITE ONE PCA PIN
*---------------------------------------------------------------------------*/
uint8_t pca9506::write_pin(uint8_t port_number, uint8_t pin_number, uint8_t pin_state)
{
  uint8_t data[2] = {0,};
  
  if ( port_number < 5 && pin_number < 8 )
  {  
    data[0] = PCA_CMD_WR_PORT + port_number; 
    
    if ( pin_state )  
      data[1] = pca_ports_st[port_number] | (1 << pin_number);
    else
      data[1] = pca_ports_st[port_number] ^ (1 << pin_number);
    
    this->pca_ports_st[port_number] = data[1]; // new current state of port
    
    if ( HAL_I2C_Master_Transmit(pca_hi2c, pca_address, data, 2, I2C_DELAY) == HAL_OK )
      return 1;
    else
      return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                            READ ALL PCA PORTS
*---------------------------------------------------------------------------*/
uint8_t pca9506::read_all_ports(uint8_t* data)
{ 
  if ( HAL_I2C_Mem_Read(pca_hi2c, pca_address, PCA_CMD_RD_PORTS, I2C_MEMADD_SIZE_8BIT, data, 5, I2C_DELAY*3) == HAL_OK )
  {
    for (uint8_t i = 0; i < 5; i++)
      this->pca_ports_st[i] = data[i]; // new current state of ports
      
    return 1;
  }
  else
    return 0;
}


/*----------------------------------------------------------------------------
*                           READ ONE PCA PORT
*---------------------------------------------------------------------------*/
uint8_t pca9506::read_port(uint8_t port_number)
{ 
  uint8_t command = 0;
  uint8_t port_state = 0;
  
  if ( port_number < 5 )
  {
    command = PCA_CMD_RD_PORT + port_number;
    
    if ( HAL_I2C_Mem_Read(pca_hi2c, pca_address, command, I2C_MEMADD_SIZE_8BIT, &port_state, 1, I2C_DELAY*3) == HAL_OK )
    {
      this->pca_ports_st[port_number] = port_state; 	// new current state of port
      return port_state;
    }   
    else
      return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                          READ ONE PCA PIN
*---------------------------------------------------------------------------*/
uint8_t pca9506::read_pin(uint8_t port_number, uint8_t pin_number)
{ 
  uint8_t port_state = 0;
  
  if ( port_number < 5 && (pin_number >= 0 && pin_number < 8) )
  {
	port_state = read_port(port_number);
    
    if ( port_state & 1<<pin_number )
       return 1;
    else 
       return 0;
  }
  else return 0; // INPUT MISTAKE
}


/*----------------------------------------------------------------------------
*                            GET CHIP ADDRESS
*---------------------------------------------------------------------------*/
uint16_t pca9506::get_address()
{
	return this->pca_address;
}


/*----------------------------------------------------------------------------
*                       GET CURRENT PORTS CONFIGURATION
*---------------------------------------------------------------------------*/
uint8_t* pca9506::get_config()
{
	return this->pca_ports_cfg;
}
// *********************************** E N D **********************************

