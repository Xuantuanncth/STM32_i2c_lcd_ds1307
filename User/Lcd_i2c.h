#include "i2c_Hardware.h"

/* Define command lcd*/
#define lcdI2cAddress 0x27
#define	CURSOR_HOME		  0x80
#define CURSOR_SECOND     0xc0

extern void delay_ms(uint32_t u32_Time);

void _lcd_I2C_Init(void);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_send_string (char *str);
void lcd_i2c_gotoxy(uint8_t row, uint8_t col);
void lcd_send_buff(uint8_t buff[]);
