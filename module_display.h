#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PIN_LCD_RESET             GPIO_PIN4
#define PORT_LCD_SPI              GPIO_PORT_P4
#define PORT_LCD_RESET            GPIO_PORT_P2


void lcd_init();