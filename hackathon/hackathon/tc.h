#include <avr/io.h>

#ifndef TIMER_H_
#define TIMER_H_

void tcc0_init(void);
void tcc0_disable(void);
void tcc0_enable(void);
void tcc1_disable(void);
void tcc1_enable(void);
void change_freq_tcc0(uint32_t freq);
void tcc1_init(void);


#endif