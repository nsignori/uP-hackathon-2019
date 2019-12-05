/*
 * quarter_sec_timer.c
 *
 * Created: 12/5/2019 10:59:24 AM
 *  Author: sharoncomora
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "tc.h"

void sys_interr_init(void);
extern void clock_init(void);

int main(void) {
	clock_init();
	PORTC.OUTSET = PIN0_bm;
	PORTC.DIRSET = PIN0_bm;
	TCC0.PER = 7812;
	TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;
	TCC0.INTCTRLA = TC0_OVFINTLVL0_bm;
	sys_interr_init();
	while(1);
	return 0;
}

ISR(TCC0_OVF_vect) {
	PORTC.OUTTGL = PIN0_bm;
}

void sys_interr_init(void) {
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
}
