#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define KEYPAD_PORT_ROW         GPIO_PORT_P5
#define KEYPAD_PORT_COL         GPIO_PORT_P6

#define KEYPAD_PIN_ROW_1        GPIO_PIN0     
#define KEYPAD_PIN_ROW_2        GPIO_PIN1
#define KEYPAD_PIN_ROW_3        GPIO_PIN4
#define KEYPAD_PIN_ROW_4        GPIO_PIN5

#define KEYPAD_PIN_COL_1        GPIO_PIN4
#define KEYPAD_PIN_COL_2        GPIO_PIN5         
#define KEYPAD_PIN_COL_3        GPIO_PIN6
#define KEYPAD_PIN_COL_4        GPIO_PIN7


enum NUMBER_KEY
{
  KEY_NUMBER_1 = 1,
  KEY_NUMBER_2,
  KEY_NUMBER_3,
  KEY_NUMBER_4,
  KEY_NUMBER_5,
  KEY_NUMBER_6,
  KEY_NUMBER_7,
  KEY_NUMBER_8,
  KEY_NUMBER_9,
  KEY_NUMBER_0,
  KEY_CASE,
  KEY_ENTER,
  KEY_UP,
  KEY_DOWN,
  KEY_SELECT,
  KEY_BACK
};
void init_keybad();
void scan_row( uint16_t x);