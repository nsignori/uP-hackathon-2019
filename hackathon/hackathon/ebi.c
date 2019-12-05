/*
 * ebi.c
 *
 * Created: 12/5/2019 12:44:51 PM
 *  Author: sharoncomora
 */ 
 
#include <avr/io.h>

#define base_addr 0x370000
#define block_size 1024

void ebi_init(void) {
	
	PORTH.DIR = 0x37;       // Enable RE, WE, CS0, CS1, ALE1
	PORTH.OUT = 0x33;
	PORTK.DIR = 0xFF;
	
	EBI.CTRL =	EBI_SRMODE_ALE1_gc | 
				EBI_IFMODE_3PORT_gc;
	
	EBI.CS1.BASEADDR = (uint16_t) (base_addr>>8) & 0xFFFF;          // Set CS1 range to 0x370000 - 0x37FFFF
    EBI.CS1.CTRLA = EBI_CS_MODE_SRAM_gc | EBI_CS_ASPACE_64KB_gc;
				
}