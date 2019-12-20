#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PIN_LCD_RESET             GPIO_PIN4
#define PORT_LCD_SPI              GPIO_PORT_P4
#define PORT_LCD_RESET            GPIO_PORT_P2


enum STATES 
{
  STATE_IDLE=1,
  STATE_LOGIN,
  STATE_MENU,
  STATE_INFOR,
  STATE_MANAGE,
  STATE_SETTING,
  STATE_LIST,
  STATE_PROFILE,
  STATE_DELETE,
  STATE_CHANGEPASS,
  STATE_LOCK_UNLOCK,
  STATE_ADD_RFID_CODE,
  STATE_ADD_USER,
  STATE_WAWITING,       
  STATE_CHOOSE
};

#define ICON_ARROW      0x7f
#define ICON_ARROW_X    0
#define ICON_ARROW_Y    0

#define ICON_BLINK_UP      '_'
#define ICON_BLINK_DOWN    ' '



#define STRING_LOGIN       "LOGIN"
#define LEN_STRING_LOGIN   strlen(STRING_LOGIN)
#define STRING_LOGIN_X      8
#define STRING_LOGIN_Y      0


#define STRING_USER         "User"
#define LEN_STRING_USER     strlen(STRING_USER) 
#define STRING_USER_X       0    
#define STRING_USER_Y       2

#define STRING_PASS         "Pass"
#define LEN_STRING_PASS     strlen(STRING_USER) 
#define STRING_PASS_X       0    
#define STRING_PASS_Y       4


void begin();
void init_LCD();
void display_screen_delete_user();
void process_keypad();
void display_icon_type_input(uint8_t ui8_type_input);
void display_icon_blink(uint8_t value,uint8_t x,uint8_t y);