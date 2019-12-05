#include "tc.h"

void tcc0_init(void) {
	uint32_t numer = 32000000;
	uint32_t freq = 1760;
	uint32_t denom = freq * 256;
	uint16_t per = numer / denom;
	
	TCC0.PER = per;
	TCC0.INTCTRLA = TC0_OVFINTLVL0_bm;
	
	/* set evsys ch0 */
	EVSYS.CH0MUX = EVSYS_CHMUX_TCC0_OVF_gc;
	
	TCC0.CNT = 0;
	
}
void tcc0_disable(void) {
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
	
}

void tcc0_enable(void) {
	TCC0.CNT = 0;
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc;
}

void tcc1_disable(void) {
	TCC1.CTRLA = TC_CLKSEL_OFF_gc;
	
}

void tcc1_enable(void) {
	TCC1.CNT = 0;
	TCC1.CTRLA = TC_CLKSEL_DIV1024_gc;
}

void tcc1_init(void) {
	/* 5ms */
	TCC1.PER = 8000;
	TCC1.INTCTRLA = TC1_OVFINTLVL0_bm;
	TCC1.CNT = 0;
}


