#ifndef __LCD_H
#define __LCD_H
#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define OUTPUT_HIGH     GPIO_setOutputHighOnPin
#define OUTPUT_LOW      GPIO_setOutputLowOnPin

#define Port_lcd        GPIO_PORT_P4
#define Cs              GPIO_PIN0
#define SDA             GPIO_PIN2
#define A0              GPIO_PIN4
#define SCLK            GPIO_PIN5

#define RST             GPIO_PIN4

extern const unsigned char font[][6] ;
extern const unsigned int  key1[4][4];
extern const unsigned char     key2[10][5];
extern const unsigned char     key3[10][5] ;
extern char logo [] ;

time_t getsec(RTC_C_Calendar x);

void keybad_init();
void lcd_write(bool cd, uint8_t byte);
void lcd_clear(uint8_t x1,uint8_t y1,uint8_t x2, uint8_t y2);
void lcd_clear_all();
void lcd_gotoxy(uint8_t x, uint8_t y);
void glcd_gotoxy(uint8_t x, uint8_t y);
void lcd_putc(uint16_t data,bool color);
void lcd_puts(char *s,bool color);
void lcd_init();
void lcd_image(char x1, char y1, char array[],char x2,char y2);
 extern void delay(uint32_t t);
#endif