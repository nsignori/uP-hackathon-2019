/*
 * hackathon.c
 *
 * Created: 12/4/2019 10:42:35 PM
 * Author : Nick and spencer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "dac.h"
#include "dma.h"
#include "usart.h"
#include "lut_8_1.h"
#include "tc.h"
#include "songs.h"


extern void clock_init(void);
void speaker_init(void);
void init_gpio(void);
void sys_interr_init(void);
void set_note(char note);

volatile int songVectIndexer = 0;
volatile uint8_t noteDuration = 0;
volatile char note = 0;
//global flag to indicate when quarter sec has elapsed
volatile uint8_t quarterSecElapsed = 0;


// IR Flags
volatile uint8_t codes[2];
volatile uint8_t nextCode = 5; // Init to 5 so it doesn't trigger UART stuff

int main(void)
{
	PORTJ.DIRSET = 0xF;
	clock_init();
	speaker_init();
	//bscale=0; bsel=1110 => baud = 2MHz
	USARTE0_init(1110, 0);
	dac_init();
	dma_init(sin, &DACA_CH1DATA);
	
	//enable usart for low-level receive interrupts
	USARTE0_enable_interrupts('R', 'L');
	
	//enable frequency timer (DMA)
	tcc0_init();
	
	//enable note timer (0.25 s)
	tcc1_init();
	tcc1_enable();
	sys_interr_init();
	
	char* song = mary;
	uint8_t songSize = sizeof(mary);
	PORTJ.OUT = 0x1;
    while (1) 
    {
		if(nextCode == 2) {
			nextCode = 3;
			if(codes[0] == 0x55 && codes[1] == 0x77) { // Button 1 - 0x5577
				song = mary;
				songVectIndexer = 0;
				songSize = sizeof(mary);
				noteDuration = 0;
				PORTJ.OUT = 0x1;
			} else if(codes[0] == 0x57 && codes[1] == 0x75) { // Button 2 - 0x5775
				song = twinkle;
				songVectIndexer = 0;
				songSize = sizeof(twinkle);
				noteDuration = 0;
				PORTJ.OUT = 0x2;
			} else if(codes[0] == 0xD7 && codes[1] == 0x57) { // Button 3 - 0xD757
				song = jingle;
				songVectIndexer = 0;
				songSize = sizeof(jingle);
				noteDuration = 0;
				PORTJ.OUT = 0x4;
			} else if(codes[0] == 0x57 && codes[1] == 0xD7) { // Button 4 - 0x57D7
				song = bday;
				songVectIndexer = 0;
				songSize = sizeof(bday);
				noteDuration = 0;
				PORTJ.OUT = 0x8;
			}
		}
		
		if (quarterSecElapsed) {
			quarterSecElapsed = 0;
			if (!noteDuration) {
				note = song[songVectIndexer++];
				set_note(note);
				noteDuration = song[songVectIndexer++] - '0';
				if(songVectIndexer >= songSize-1) {
					songVectIndexer = 0;
				}
			}
			
			noteDuration--;
		}
    }
}

ISR(TCC1_OVF_vect) {
	quarterSecElapsed = 1;
}

void speaker_init(void) {
	PORTC.OUTSET = PIN7_bm;
	PORTC.DIRSET = PIN7_bm;
}

void init_gpio(void) {
	PORTD.OUTSET = PIN4_bm | PIN6_bm;
	PORTD.DIRSET = PIN4_bm | PIN6_bm;
}


void sys_interr_init(void) {
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
}

void set_note(char note) {
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
	while (TCC1.CNT < 3000);
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc;
	switch(note) {
		case 'C': {
			TCC0.PER = 120; // 1046.50 Hz
			break;
		}
		case 'D': {
			TCC0.PER = 108; // 1174.66 Hz
			break;
		}
		case 'E': {
			TCC0.PER = 96; // 1318.51 Hz
			break;
		}
		case 'F': {
			TCC0.PER = 91; // 1396.91 Hz
			break;
		}
		case 'G': {
			TCC0.PER = 81; // 1567.98 Hz
			break;
		}
		case 'A': {
			TCC0.PER = 71; // 1760 Hz
			break;
		}
		case 'B': {
			TCC0.PER = 64; // 1975.53 Hz
			break;
		}
		case '-': {
			TCC0.CTRLA = TC_CLKSEL_OFF_gc;
		}
	}
}

ISR(USARTE0_RXC_vect) {
	char newChar = USARTE0_in_char();
	if(newChar == 0xD5) {
		nextCode = 0;
	} else if (nextCode < 2) {
		codes[nextCode++] = newChar;
	}
}

