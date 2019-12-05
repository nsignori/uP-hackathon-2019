#include "dac.h"

void dac_init(void) {
	DACA.CTRLA = DAC_CH1EN_bm;
	
	DACA.CTRLB = DAC_CHSEL_SINGLE1_gc | DAC_CH1TRIG_bm;
	
	DACA.CTRLC = ADC_REFSEL_INT1V_gc;
	
	DACA.CTRLA |= DAC_ENABLE_bm;
}

void gpio_init_daca(void) {
	PORTA.OUTSET = PIN2_bm | PIN3_bm;
	PORTA.DIRSET = PIN2_bm | PIN3_bm;
}

