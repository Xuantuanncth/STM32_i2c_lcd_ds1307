#include "stm32f10x.h"
#include "i2c_Hardware.h"

/* Define command DS1307*/
#define ds1307Address 0x68
#define ds1307_second 0x00
#define ds1307_minute 0x01
#define ds1307_hour   0x02
#define ds1307_day 		0x03
#define ds1307_date		0x04
#define ds1307_month	0x05
#define ds1307_year		0x06


// DS1307 day of week
#define DS1307_SUNDAY				1
#define DS1307_MONDAY				2
#define DS1307_TUESDAY			3
#define DS1307_WEDNESDAY		4
#define DS1307_THRUSDAY			5
#define DS1307_FRIDAY				6
#define DS1307_SATURDAY			7

#define DS1307_HOUR_MODE		6
#define DS1307_AM_PM				5

// DS1307 hour mode
#define DS1307_HOUR_12			1
#define DS1307_HOUR_24			0
#define DS1307_AM						0
#define DS1307_PM						1

/*Function ds1307*/
uint8_t ds1307_getSecond(void);
uint8_t ds1307_getMinute(void);
uint8_t ds1307_getHour(void);
uint8_t ds1307_getDate(void);
uint8_t ds1307_getDay(void);
uint8_t ds1307_getMonth(void);
uint8_t ds1307_getYear(void);

void ds1307_init(void);

void ds1307_setSecond(uint8_t sec);
void ds1307_setMinute(uint8_t min);
void ds1307_setHour(uint8_t hour);
void ds1307_setDay(uint8_t day);
void ds1307_setMonth(uint8_t mon);
void ds1307_setYear(uint8_t year);

void ds1307_setTime(uint8_t hour, uint8_t min, uint8_t sec);
void ds1307_setCalendar(uint8_t day, uint8_t date, uint8_t mon, uint8_t year);

uint8_t bcd2bin(uint8_t bcd);
uint8_t bin2bcd(uint8_t bin) ;

