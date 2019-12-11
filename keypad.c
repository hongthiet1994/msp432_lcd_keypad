#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "keypad.h"


uint8_t ui8_key_input = 0; 
uint16_t ui16_status = 0;

const unsigned int  key1[4][4] ={{1,2,3,13}
,{4,5,6,14}
,{7,8,9,15}
,{11,10,12,16}};


const unsigned char     key2[10][5] =  {{'+','-','*','/','1'}
,{'A','B','C','|','2'}
,{'D','E','F','%','3'}
,{'G','H','I','(','4'}
,{'J','K','L',')','5'}
,{'M','N','O','@','6'}
,{'P','Q','R','S','7'}
,{'T','U','V',',','8'}
,{'W','X','Y','Z','9'}
,{'#','$','.','?','0'}};

const unsigned char     key3[10][5] =  {{'+','-','*','/','1'}
,{'a','b','c','|','2'}
,{'d','e','f','%','3'}
,{'g','h','i','(','4'}
,{'j','k','l',')','5'}
,{'m','n','o','@','6'}
,{'p','q','r','s','7'}
,{'t','u','v',',','8'}
,{'w','x','y','z','9'}
,{'#','$','.','?','0'}};



void keybad_init()
{
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7 );
  GPIO_interruptEdgeSelect(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7 ,
                           GPIO_HIGH_TO_LOW_TRANSITION);
  GPIO_clearInterruptFlag(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7);
  GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7);
  
  GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0+GPIO_PIN1+GPIO_PIN4+GPIO_PIN5);
  
  GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);
  
  GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN0+GPIO_PIN1+GPIO_PIN4+GPIO_PIN5);
  GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN7);
  Interrupt_enableInterrupt(INT_PORT6);  
}


/*
// The function scan keys in rows
//  @param : x is the number row
*/
void scan_row(uint16_t x)
{
  GPIO_setOutputLowOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_1);
  GPIO_setOutputHighOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_2);
  GPIO_setOutputHighOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_3);
  GPIO_setOutputHighOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_4);
  if(!GPIO_getInputPinValue(GPIO_PORT_P6,ui16_status))
  {
    ui8_key_input = key1[0][x-1];
    //returnKey();
  }
  
  GPIO_setOutputLowOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_2);
  GPIO_setOutputHighOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_1);
  if(!GPIO_getInputPinValue(KEYPAD_PORT_COL,ui16_status))
  {
    
    ui8_key_input = key1[1][x-1];
    // returnKey();
  }
  
  GPIO_setOutputLowOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_3);
  GPIO_setOutputHighOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_2);
  if(!GPIO_getInputPinValue(KEYPAD_PORT_COL,ui16_status))
  {
    ui8_key_input = key1[2][x-1];
    // returnKey();
  }
  GPIO_setOutputLowOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_4);
  GPIO_setOutputHighOnPin(KEYPAD_PORT_ROW, KEYPAD_PIN_ROW_3);
  if(!GPIO_getInputPinValue(KEYPAD_PORT_COL,ui16_status))
  {
    ui8_key_input = key1[3][x-1];
    //returnKey();
  }
  GPIO_setOutputLowOnPin(KEYPAD_PORT_ROW,GPIO_PIN1+GPIO_PIN0+GPIO_PIN4+GPIO_PIN5);
}