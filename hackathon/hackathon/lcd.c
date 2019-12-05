/*
 * lcd.c
 *
 * Created: 12/5/2019 2:11:39 PM
 *  Author: sharoncomora
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "ebi.h"

void lcd_init(void) {
	
	PORTC.OUTSET = 0xFF;
	PORTC.DIRSET = 0xFF;
	PORTF.OUTSET = RS | RW | E;
	PORTF.DIRSET = RS | RW | E;
}

void lcd_write_instruction(char instruction) {
	uint8_t bitStream = 0;
	//write R~S, R~W low
	bitStream = ~RS & ~RW;
	PORTF.OUT = bitStream;
	
	
	
	//write the instruction to DB
	PORTC.OUT = instruction;
	
	//set enable high
	bitStream |= E;
	PORTF.OUT = bitStream;
	
	//set enable low
	bitStream &= ~E;
	PORTF.OUT = bitStream;
	
}

void lcd_write_char(char c) {
	uint8_t bitStream = 0;
	//write RS, RW low
	bitStream = ~RS & ~RW;
	PORTF.OUT = bitStream;
	
	//write the char to DB
	PORTC.OUT = c;
	
	//set enable high
	bitStream |= E;
	PORTF.OUT = bitStream;
	
	//set enable low
	bitStream &= ~E;
	PORTF.OUT = bitStream;
}

void lcd_write_string(char * str) {
	while(*str) {
		lcd_write_char(*(str++));
	}
}