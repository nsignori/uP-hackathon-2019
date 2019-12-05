/*
 * lcd.c
 *
 * Created: 12/5/2019 2:11:39 PM
 *  Author: sharoncomora
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "ebi.h"

#define lcd_port 0x370000

void lcd_init(void) {
	ebi_init();
}

void lcd_write_instruction(char instruction) {
	uint8_t bitStream = 0;
	//write RS, RW low
	bitStream = ~RS & ~RW;
	__far_mem_write(lcd_port, bitStream);
	
	//set enable low
	bitStream &= ~E;
	__far_mem_write(lcd_port, bitStream);
	
	//write the instruction to DB
	__far_mem_write(lcd_port, instruction);
	
	//set enable high
	bitStream |= E;
	__far_mem_write(lcd_port, bitStream);
	
	//set enable low
	bitStream &= ~E;
	__far_mem_write(lcd_port, bitStream);
	
}

char lcd_read(void) {
	
	
}
void lcd_write_char(char c) {
	uint8_t bitStream = 0;
	//write RS high (data, not instruction)
	__far_mem_write(lcd_port, bitStream);
	
	//write RW low (writing, not reading)
	bitStream &= ~RW;
	__far_mem_write(lcd_port, bitStream);
	
	//write E low
	bitStream &= ~E;
	__far_mem_write(lcd_port, bitStream);
	
	//write char to data bus
	__far_mem_write(lcd_port, c);
	
	//set enable high
	bitStream |= E;
	__far_mem_write(lcd_port, bitStream);
	
	//set enable low
	bitStream &= ~E;
	__far_mem_write(lcd_port, bitStream);
}

void lcd_write_string(char * str) {
	while(*str) {
		lcd_write_char(*(str++));
	}
}