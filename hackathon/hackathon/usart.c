#include "usart.h"

void USARTE0_init(uint16_t BSEL, uint8_t BSCALE) {
	//PORTD.OUTSET = PIN3_bm;
	//PORTD.DIRSET = PIN3_bm;
	PORTE.DIRCLR = PIN2_bm;
	
	USARTE0.BAUDCTRLA = (uint8_t) BSEL;
	USARTE0.BAUDCTRLB = (uint8_t) ( (BSCALE << 4) | (BSEL >> 8) );
	
	USARTE0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc
					| (USART_CHSIZE_8BIT_gc);
	
	USARTE0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	//USARTE0.CTRLA = USART_RXCINTLVL_MED_gc;
}

void USARTE0_out_char(char c) {
	while (!(USARTE0.STATUS & USART_DREIF_bm));
	USARTE0.DATA = c;
}

void USARTE0_out_string(char * str) {
	while(*str) {
		USARTE0_out_char(*(str++));
	}
}

char USARTE0_in_char(void) {
	while(!(USARTE0.STATUS & USART_RXCIF_bm));
	return USARTE0.DATA;
}

/*
void USARTE0_in_string(uint16_t * buf) {
	//loop counter to store
	int i = 0;
	
	//pointer to tempBuf, which is string received
	
	
	//read in the first char in the sequence
	uint8_t c = USARTE0_in_char();
	
	//while "return" key not pressed (carriage return)
	while((uint8_t) (c) != 0x0D) {
		
		//echo the character typed back to the user
		echo(c);
		
		//store char received in next pos in buffer
		buf[i] = c;
		
		//increment loop counter
		i++;
		
		//get the next char; check for carriage return in loop condition
		c = USARTE0_in_char();
	}
}

void echo(char c) {
	USARTE0.DATA = c;
}

/*
void USARTE0_in_string_hex(uint16_t * buf) {
	int i = 0;
	//read in the first char in the sequence
	uint8_t c = USARTE0_in_char();
	
	//while "return" key not pressed
	while((uint8_t) (c) != 0x0D) {
		echo(c);
		//if input char is not a hex char then return false
		if (!checkHex(c)) {
			buf = 0;
			break;
		}
		//store char received in next pos in buffer
		*(buf + i) = c;
		//read in the next char for loop condition
		i++;
		c = USARTE0_in_char();
	}
	
}
*/

void USARTE0_enable_interrupts(char intType, char intLevel) {
	//receive
	if (intType == 'r' || intType == 'R') {
		if (intLevel == 'l' || intLevel == 'L') {
			USARTE0.CTRLA |= USART_RXCINTLVL_LO_gc;
		}
		else if (intLevel == 'm' || intLevel == 'M') {
			USARTE0.CTRLA |= USART_RXCINTLVL_MED_gc;
		}
		else if (intLevel == 'h' || intLevel == 'H') {
			USARTE0.CTRLA |= USART_RXCINTLVL_HI_gc;
		}
	}
	else if (intType == 't' || intType == 't') {
		if (intLevel == 'l' || intLevel == 'L') {
			USARTE0.CTRLA |= USART_DREINTLVL_LO_gc;
		}
		else if (intLevel == 'm' || intLevel == 'M') {
			USARTE0.CTRLA |= USART_DREINTLVL_MED_gc;
		}
		else if (intLevel == 'h' || intLevel == 'H') {
			USARTE0.CTRLA |= USART_DREINTLVL_HI_gc;
		}
	}
}