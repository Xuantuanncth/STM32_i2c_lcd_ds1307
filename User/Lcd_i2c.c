#include "Lcd_i2c.h"

void lcd_send_cmd(uint8_t cmd) {
	uint8_t data_low, data_up, i;
	uint8_t data[4];
	data_up = cmd&0xf0;
	data_low = (cmd << 4)&0xf0;
	data[0] = data_up|0x0c;
	data[1] = data_up|0x08;
	data[2] = data_low|0x0c;
	data[3] = data_low|0x08;
	for(i = 0; i < 4; i++) {
		i2c_write_byte(lcdI2cAddress,data[i]);
	}
}

void lcd_send_data(uint8_t data) {
	uint8_t data_u, data_l,i;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	for(i = 0; i< 4; i++) {
		i2c_write_byte(lcdI2cAddress,data_t[i]);
	}
}

void _lcd_I2C_Init(){
	lcd_send_cmd(0x33);  /* set 4-bits interface */
	delay_ms(10);
	lcd_send_cmd (0x32);
	delay_ms(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	delay_ms(50);
	lcd_send_cmd (0x01); /* clear display */
	delay_ms(50);
	lcd_send_cmd (0x06); /* set entry mode */
	delay_ms(50);
	lcd_send_cmd (0x0c); /* set display to on */
	delay_ms(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	delay_ms(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_send_buff(uint8_t buff[]) {
	uint8_t i =0, length = 0;
	length = strlen(buff);
	for(i = 0; i< length; i++) {
		lcd_send_data(buff[i]);
	}
}

void lcd_i2c_gotoxy(uint8_t row, uint8_t col) {
	uint16_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if(row > 2) {
		row = 2-1;
	}
	lcd_send_cmd(0x80 | (col + row_offsets[row]));
}
