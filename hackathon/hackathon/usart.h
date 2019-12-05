#include <avr/io.h>

#ifndef USART_H_
#define USART_H_

/***************************************************
Initializes USARTE0 with baud rate specified by
BSEL, BSCALE
***************************************************/
void USARTE0_init(uint16_t BSEL, uint8_t BSCALE);
/***************************************************
Transmits a char
***************************************************/
void USARTE0_out_char(char c);
/***************************************************
Transmits a string
***************************************************/
void USARTE0_out_string(char * str);
/***************************************************
Receives a char
***************************************************/
char USARTE0_in_char(void);
/***************************************************
Receives a string
***************************************************/
void USARTE0_in_string(uint16_t * buf);

void USARTE0_in_string_hex(uint16_t * buf);

void echo(char c);
/***************************************************
Optionally initialize interrupts
-	intType expects 'r' for receive or 't' for transmit
-	intLevel expects 'l', 'm', or 'h'
***************************************************/
void USARTE0_enable_interrupts(char intType, char intLevel);

#endif