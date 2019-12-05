#include "usart.h"

void usartd0_init(uint16_t BSEL, uint8_t BSCALE) {
	PORTD.OUTSET = PIN3_bm;
	PORTD.DIRSET = PIN3_bm;
	PORTD.DIRCLR = PIN2_bm;
	
	USARTD0.BAUDCTRLA = (uint8_t) BSEL;
	USARTD0.BAUDCTRLB = (uint8_t) ( (BSCALE << 4) | (BSEL >> 8) );
	
	USARTD0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc 
					| USART_PMODE_ODD_gc
					| (USART_CHSIZE_8BIT_gc);
	
	USARTD0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	USARTD0.CTRLA = USART_RXCINTLVL_LO_gc;
}

void usartd0_out_char(char c) {
	while (!(USARTD0.STATUS & USART_DREIF_bm));
	USARTD0.DATA = c;
}

void usartd0_out_string(char * str) {
	while(*str) {
		usartd0_out_char(*(str++));
	}
}

char usartd0_in_char(void) {
	while(!(USARTD0.STATUS & USART_RXCIF_bm));
	return USARTD0.DATA;
}

void usartd0_in_string(uint16_t * buf) {
	//loop counter to store
	int i = 0;
	
	//pointer to tempBuf, which is string received
	
	
	//read in the first char in the sequence
	uint8_t c = usartd0_in_char();
	
	//while "return" key not pressed (carriage return)
	while((uint8_t) (c) != 0x0D) {
		
		//echo the character typed back to the user
		echo(c);
		
		//store char received in next pos in buffer
		buf[i] = c;
		
		//increment loop counter
		i++;
		
		//get the next char; check for carriage return in loop condition
		c = usartd0_in_char();
	}
}

void echo(char c) {
	USARTD0.DATA = c;
}

void usartd0_in_string_hex(uint16_t * buf) {
	int i = 0;
	//read in the first char in the sequence
	uint8_t c = usartd0_in_char();
	
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
		c = usartd0_in_char();
	}
	
}

void usartd0_enable_interrupts(char intType, char intLevel) {
	//receive
	if (intType == 'r' || intType == 'R') {
		if (intLevel == 'l' || intLevel == 'L') {
			USARTD0.CTRLA |= USART_RXCINTLVL_LO_gc;
		}
		else if (intLevel == 'm' || intLevel == 'M') {
			USARTD0.CTRLA |= USART_RXCINTLVL_MED_gc;
		}
		else if (intLevel == 'h' || intLevel == 'H') {
			USARTD0.CTRLA |= USART_RXCINTLVL_HI_gc;
		}
	}
	else if (intType == 't' || intType == 't') {
		if (intLevel == 'l' || intLevel == 'L') {
			USARTD0.CTRLA |= USART_TXCINTLVL_LO_gc;
		}
		else if (intLevel == 'm' || intLevel == 'M') {
			USARTD0.CTRLA |= USART_TXCINTLVL_MED_gc;
		}
		else if (intLevel == 'h' || intLevel == 'H') {
			USARTD0.CTRLA |= USART_TXCINTLVL_HI_gc;
		}
	}
}