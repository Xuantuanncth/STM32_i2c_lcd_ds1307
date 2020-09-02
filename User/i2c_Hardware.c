#include "i2c_Hardware.h"

void _initI2C2(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	/* Enable GPIOB	 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	
	I2C_Init(I2C2,&I2C_InitStructure);
	I2C_Cmd(I2C2,ENABLE);
}

void i2c_start(void) {
		I2C_GenerateSTART(I2C2,ENABLE);
		while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
}

void i2c_stop(void) {
	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

void i2c_sendAddress(uint8_t address, uint8_t mode) {
	uint8_t address_t = address << 1;
	if(mode == transmit) {
		I2C_Send7bitAddress(I2C2,address_t,I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	if(mode == receive) {
		I2C_Send7bitAddress(I2C2,address_t,I2C_Direction_Receiver);
		while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

void i2c_transmit(uint8_t data) {
		I2C_SendData(I2C2,data);
		while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

uint8_t i2c_receive(void) {
	uint8_t data;
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data = I2C_ReceiveData(I2C2);
	return data;
}

void i2c_write_byte(uint8_t address, uint8_t data) {
	i2c_start();
	i2c_sendAddress(address, transmit);
	i2c_transmit(data);
	i2c_stop();
}

/*
 * Wirte byte with register 
 */
void i2c_write_byte_with_reg(uint8_t address, uint8_t reg, uint8_t data) {	
	i2c_start();
	i2c_sendAddress(address, transmit);
	i2c_transmit(reg);
	i2c_transmit(data);
	i2c_stop();
}

uint8_t i2c_read_byte(uint8_t address) {
	uint8_t data;
	i2c_start();
	i2c_sendAddress(address,receive);
	data = i2c_receive();
	i2c_stop();
	return data;
}

/**
 * Read byte with register
 */

uint8_t i2c_read_byte_with_reg(uint8_t address, uint8_t reg) {
	uint8_t data;
	i2c_start();
	i2c_sendAddress(address, transmit);
	i2c_transmit(reg);
	i2c_stop();
	i2c_start();
	i2c_sendAddress(address, receive);
	data = i2c_receive();
	i2c_stop();
	return data;
}
