#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Port_lcd        GPIO_PORT_P4
#define Cs              GPIO_PIN0
#define SDA             GPIO_PIN2
#define A0              GPIO_PIN4
#define SCLK            GPIO_PIN5

void lcd_image(char x1, char y1, char array[],char x2,char y2);
void lcd_gotoxy(uint8_t x, uint8_t y);
void glcd_gotoxy(uint8_t x, uint8_t y);
void lcd_putc(uint16_t data,bool color);
void lcd_puts(char *s,bool color);
void lcd_clear(uint8_t x1,uint8_t y1,uint8_t x2, uint8_t y2);
void lcd_clear_all();
void lcd_write(bool cd, uint8_t byte);