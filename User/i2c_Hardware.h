#include "stm32f10x.h"

#define transmit 0x10
#define receive 0x11

void _initI2C2(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_transmit(uint8_t data);
uint8_t i2c_receive(void);
void i2c_sendAddress(uint8_t address, uint8_t mode);
void i2c_write_byte(uint8_t address, uint8_t data);
void i2c_write_byte_with_reg(uint8_t address, uint8_t reg, uint8_t data);
uint8_t i2c_read_byte(uint8_t address);
uint8_t i2c_read_byte_with_reg(uint8_t address, uint8_t reg);


