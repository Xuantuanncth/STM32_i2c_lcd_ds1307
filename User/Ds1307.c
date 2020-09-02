#include "Ds1307.h"

void ds1307_init(void) {	
	_initI2C2();
}	

uint8_t ds1307_getSecond(void) {
	uint8_t sec = 0;
	sec = i2c_read_byte_with_reg(ds1307Address,ds1307_second);
	return bcd2bin(sec);
}

uint8_t ds1307_getMinute(void){
		uint8_t min = 0;
		min = i2c_read_byte_with_reg(ds1307Address,ds1307_minute);
		return bcd2bin(min);
}

uint8_t ds1307_getHour(void){
		uint8_t hour = 0;
		hour = i2c_read_byte_with_reg(ds1307Address,ds1307_hour);
		return bcd2bin(hour & 0x3f);
}

uint8_t ds1307_getDay(void){
		uint8_t day = 0;
		day = i2c_read_byte_with_reg(ds1307Address,ds1307_day);
		return bcd2bin(day);
}

uint8_t ds1307_getDate(void){
		uint8_t date = 0;
		date = i2c_read_byte_with_reg(ds1307Address,ds1307_date);
		return bcd2bin(date);
}

uint8_t ds1307_getMonth(void){
		uint8_t mon = 0;
		mon = i2c_read_byte_with_reg(ds1307Address,ds1307_month);
		return bcd2bin(mon);
}

uint8_t ds1307_getYear(void){
		uint8_t year = 0;
		year = i2c_read_byte_with_reg(ds1307Address,ds1307_year);
		return bcd2bin(year);
}

void ds1307_setSecond(uint8_t sec) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_second,bin2bcd(sec));
}
void ds1307_setMinute(uint8_t min) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_minute,bin2bcd(min));
}
void ds1307_setHour(uint8_t hour) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_hour,bin2bcd(hour));
}
void ds1307_setDay(uint8_t day) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_day,bin2bcd(day));
}
void ds1307_setDate(uint8_t date) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_date,bin2bcd(date));
}
void ds1307_setMonth(uint8_t mon) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_month,bin2bcd(mon));
}
void ds1307_setYear(uint8_t year) {
	i2c_write_byte_with_reg(ds1307Address,ds1307_year,bin2bcd(year));
}

void ds1307_setTime(uint8_t hour, uint8_t min, uint8_t sec) {
	ds1307_setHour(hour);
	ds1307_setMinute(min);
	ds1307_setSecond(sec);
}

void ds1307_setCalendar(uint8_t day, uint8_t date, uint8_t mon, uint8_t year) {
	ds1307_setDay(day);
	ds1307_setDate(date);
	ds1307_setMonth(mon);
	ds1307_setYear(year);
}

uint8_t bcd2bin(uint8_t bcd) {
	uint8_t bin = (bcd >> 4) * 10;
	bin += bcd & 0x0F;
	
	return bin;
}

uint8_t bin2bcd(uint8_t bin) {
	uint8_t high = bin / 10;
	uint8_t low = bin - (high *10);
	
	return (high << 4) | low;
}
