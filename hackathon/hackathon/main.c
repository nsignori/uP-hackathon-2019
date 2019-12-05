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

int main(void)
{
	for (int i = 0; i < 256; i++) {
		sin[i] = sin[i] << 2;
	}
	clock_init();
	speaker_init();
	//baud=0; bsel=0 => baud = 2MHz
	USARTE0_init(0,0);
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
	
	char * song = mary;
    while (1) 
    {
		if (quarterSecElapsed) {
			quarterSecElapsed = 0;
			if (!noteDuration) {
				note = song[songVectIndexer++];
				set_note(note);
				noteDuration = song[songVectIndexer++] - '0';
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
			TCC0.PER = (uint16_t) 119;
			break;
		}
		case '3': {
			TCC0.PER = (uint16_t) 113;
			break;
		}
		case 'D': {
			TCC0.PER = (uint16_t) 106;
			break;
		}
		case '4': {
			TCC0.PER = (uint16_t) 100;
			break;
		}
		case 'E': {
			TCC0.PER = (uint16_t) 95;
			break;
		}
		case 'F': {
			TCC0.PER = (uint16_t) 89;
			break;
		}
		case 'G': {
			TCC0.PER = (uint16_t) 84;
			break;
		}
		case 'Y': {
			TCC0.PER = (uint16_t) 79;
			TCC1.CNT = 0;
			break;
		}
		case '7': {
			TCC0.PER = (uint16_t) 75;
			break;
		}
		case 'U': {
			TCC0.PER = (uint16_t) 71;
			break;
		}
		case '8': {
			TCC0.PER = (uint16_t) 67;
			break;
		}
		case 'I': {
			TCC0.PER = (uint16_t) 63;
			break;
		}
	}
}

