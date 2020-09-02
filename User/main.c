#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "i2c_Hardware.h"
#include "Lcd_i2c.h"
#include "Ds1307.h"


#define button1 GPIO_Pin_7
#define button2 GPIO_Pin_6
#define button3 GPIO_Pin_5
#define led1 GPIO_Pin_12
#define led2 GPIO_Pin_13
#define led3 GPIO_Pin_14

GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_InitStructure;
USART_InitTypeDef USART_InitStructure;

void _initGPIO(void);
void _initUART(void);
void _initTimer(void);


void delay_ms(uint32_t u32_Time);
void uart_send_string(char *str);
uint8_t Keypad_Read(void);
uint8_t GetKey(void);
void blink_led(void);



char date[20];
uint8_t date_t, day_t, month_t, year_t;
uint8_t hour_t, min_t, sec_t;
uint8_t address = 0;

void _initGPIO() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_13 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void _initUART(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Config TX PB10 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Config RX PB11 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
}

void _initTimer() {
	TIM_DeInit(TIM2);
	/* Enable timer 2*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 0xffff;
	TIM_InitStructure.TIM_Prescaler = 72-1;
	
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(uint32_t u32_Time) {
	while(u32_Time > 0) {
		TIM_SetCounter(TIM2, 0);
		while(TIM_GetCounter(TIM2) < 1000) {};
		u32_Time--;
	}
}

void uart_send_string(char *str) {
	while(*str) {
		USART_SendData(USART2,(*str++));
		delay_ms(10);
	}
}

uint8_t Keypad_Read(void)
{
	uint8_t Ret = 0;
	static uint8_t LastVal = 1;
	uint8_t Val_bt1 = 1, Val_bt2 = 1, Val_bt3 = 1;
	
	Val_bt1 = GPIO_ReadInputDataBit(GPIOB,button1);
	Val_bt2 = GPIO_ReadInputDataBit(GPIOB,button2);
	Val_bt3 = GPIO_ReadInputDataBit(GPIOB,button3);
	if(Val_bt1 != LastVal)
	{
		if(Val_bt1 == 0)
		{
			Ret = 1;
		}
		LastVal = Val_bt1;
	}
	if(Val_bt2 != LastVal)
	{
		if(Val_bt2 == 0)
		{
			Ret = 2;
		}
		LastVal = Val_bt2;
	}
	if(Val_bt3 != LastVal)
	{
		if(Val_bt3 == 0)
		{
			Ret = 3;
		}
		LastVal = Val_bt3;
	}
	return Ret;
}

uint8_t GetKey(void) {
	uint8_t key = 0;
	if(GPIO_ReadInputDataBit(GPIOB,button1) == 0) {
		key = 1;
		while(GPIO_ReadInputDataBit(GPIOB,button1) == 0);
	}
	if(GPIO_ReadInputDataBit(GPIOB,button2) == 0) {
		key = 2;
		while(GPIO_ReadInputDataBit(GPIOB,button2) == 0);
	}
	if(GPIO_ReadInputDataBit(GPIOB,button3) == 0) {
		key = 3;
		while(GPIO_ReadInputDataBit(GPIOB,button3) == 0);
	}
	return key;

}

void Display_LCD() {

}

int main(void) {
	uint8_t sec_t = 0, min_t = 0, hour_t = 0,day_t = 0, date_t = 0,mon_t = 0,year_t = 0;
	//uint16_t year = 0;
	uint8_t timeNow[8];
	_initTimer();
	_initGPIO();
	_initUART();
	_initI2C2();
	uart_send_string("Begin");
	_lcd_I2C_Init();
	lcd_send_string("Hello");

	uart_send_string("Set date\n");

	uart_send_string("Set Time \n");
	while(1) {
		year_t = ds1307_getYear();
		mon_t = ds1307_getMonth();
		date_t = ds1307_getDate();
		day_t = ds1307_getDay();
		hour_t = ds1307_getHour();
		min_t =  ds1307_getMinute();
		sec_t =  ds1307_getSecond();
		
		sprintf(timeNow,"%.2d:%.2d:%.2d \n",hour_t,min_t,sec_t);
		lcd_i2c_gotoxy(1,3);
		lcd_send_buff(timeNow);
	}
}
