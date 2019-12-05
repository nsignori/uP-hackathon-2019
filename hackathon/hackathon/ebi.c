/*
 * ebi.c
 *
 * Created: 12/5/2019 12:44:51 PM
 *  Author: sharoncomora
 */ 
 
#include <avr/io.h>

#define base_addr 0x4000
#define block_size 1024

void ebi_init(void) {
	
	PORTH.DIR = 0x37;       // Enable RE, WE, CS0, CS1, ALE1
	PORTH.OUT = 0x33;
	PORTK.DIR = 0xFF;
	
	EBI.CTRL =	EBI_SDDATAW_8BIT_gc |
				EBI_LPCMODE_ALE1_gc |
				EBI_SRMODE_ALE1_gc |
				EBI_IFMODE_3PORT_gc;
	
	EBI.CS1.CTRLA = EBI_CS_ASPACE_1KB_gc |
					EBI_CS_MODE_SRAM_gc;
					
	EBI.CS0.BASEADDRH = (uint8_t) (base_addr>>16) & 0xFF;
	EBI.CS0.BASEADDRL = (uint8_t) (base_addr>>8) & 0xFF;
				
}