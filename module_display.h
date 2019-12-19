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

void begin();
void init_LCD();