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

volatile int songVectIndexer = 0;
volatile uint8_t noteDuration = 0;

//global flag to indicate when quarter sec has elapsed
volatile uint8_t quarterSecElapsed = 0;

int main(void)
{
	clock_init();
	
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
	
	
    /* Replace with your application code */
    while (1) 
    {

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

