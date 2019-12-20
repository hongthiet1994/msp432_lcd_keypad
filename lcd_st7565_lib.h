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

#define MAX_CHARACTER_IN_LINE     21
#define MAX_LINE                  10
enum DISPLAY_ALIGN
{
  DISPLAY_ALIGN_NONE,
  DISPLAY_ALIGN_CENTRAL,
  DISPLAY_ALIGN_LEFT,
  DISPLAY_ALIGN_RIGHT  
};

enum DISPLAY_COLOUR
{
  COLOR_WHITE,
  COLOR_BLACK  
};


enum TYPE_INPUT
{
  INPUT_LOWERCASE_LETTERS,
  INPUT_CAPITAL_LETTER,
  INPUT_NUMBER  
};

void lcd_image(char x1, char y1, char array[],char x2,char y2);
void lcd_gotoxy(uint8_t x, uint8_t y);
void glcd_gotoxy(uint8_t x, uint8_t y);
void display_char(uint8_t data,bool color);
void lcd_puts(char *s,bool color);
void lcd_clear(uint8_t x1,uint8_t y1,uint8_t x2, uint8_t y2);
void clear_all_LCD();
void lcd_write(bool cd, uint8_t byte);
void display_icon(uint8_t icon,uint8_t x, uint8_t y,uint8_t color);
void display_string(char* string,uint8_t len, uint8_t pos_x, uint8_t pos_y, uint8_t  color, uint8_t align);