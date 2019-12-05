/*
 * dac.h
 *
 * Created: 11/10/2019 5:41:11 PM
 *  Author: sharoncomora
 */ 

#include <avr/io.h>

#ifndef DAC_H_
#define DAC_H_

void dac_init(void);

void gpio_init_daca(void);
void dac_write(uint16_t data);

#endif /* DAC_H_ */