/*
 * ebi_test.c
 *
 * Created: 12/5/2019 1:04:39 PM
 *  Author: sharoncomora
 */ 

#include <avr/io.h>
#include "lcd.h"

int main(void) {
	
	lcd_init();
	while(1) {
		lcd_write_instruction(0b00000110);
	}
	while(1) {
		lcd_write_char(0x45);
	}
	return 0;
	
}