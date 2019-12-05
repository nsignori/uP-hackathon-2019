/*
 * ebi_test.c
 *
 * Created: 12/5/2019 1:04:39 PM
 *  Author: sharoncomora
 */ 

#include <avr/io.h>
#include "ebi.h"
#include "ebi_driver.h"

int main(void) {
	ebi_init();
	
	while(1) {
		__far_mem_write(0x370000, 0x55);
	}
	return 0;
	
}