/*
 * lcd.h
 *
 * Created: 12/5/2019 2:11:30 PM
 *  Author: sharoncomora
 */ 


#ifndef LCD_H_
#define LCD_H_

#define DB4 PIN4_bm
#define DB5 PIN5_bm
#define DB6 PIN6_bm
#define DB7 PIN7_bm
#define RS  PIN0_bm
#define RW	PIN1_bm
#define E	PIN2_bm

void lcd_init(void);

void lcd_write_char(char c);

void lcd_write_string(char * str);




#endif /* LCD_H_ */