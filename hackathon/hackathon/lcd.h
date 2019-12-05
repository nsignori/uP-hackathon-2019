/*
 * lcd.h
 *
 * Created: 12/5/2019 2:11:30 PM
 *  Author: sharoncomora
 */ 


#ifndef LCD_H_
#define LCD_H_
//for PORTC 
#define DB0 PIN7_bm
#define DB1 PIN6_bm
#define DB2 PIN5_bm
#define DB3 PIN4_bm
#define DB4 PIN3_bm
#define DB5 PIN2_bm
#define DB6 PIN1_bm
#define DB7 PIN0_bm

//for PORTF
#define RS  PIN5_bm
#define RW	PIN6_bm
#define E	PIN7_bm

void lcd_init(void);

void lcd_write_char(char c);

void lcd_write_string(char * str);




#endif /* LCD_H_ */