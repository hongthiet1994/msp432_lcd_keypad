#include <string.h>
#include <math.h>
#include "driverlib.h"
#include "module_timer.h"
#include "module_display.h"
#include "lcd_st7565_lib.h"

extern uint16_t ui16_idle;
extern uint8_t ui8_time_open_door;
extern uint8_t ui8_state;
extern int8_t x_blink,y_blink;


extern bool bo_tag_RFID;
bool bo_input_pin_RFID = false;
bool bo_edge_select = true;
bool bo_input_sensor= false;


Timer_A_UpModeConfig upConfig =
{
  TIMER_A_CLOCKSOURCE_ACLK,              
  TIMER_A_CLOCKSOURCE_DIVIDER_1,          
  PERIOD_TIME_A,                          
  TIMER_A_TAIE_INTERRUPT_ENABLE,         
  TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    
  TIMER_A_DO_CLEAR                        
    
};
void init_TIMER()
{
  // TIMER_A
  Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
  Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);
  
   // config TIMER32
  Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
  Interrupt_enableInterrupt(INT_T32_INT1);
  
  Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
  Interrupt_enableInterrupt(INT_T32_INT2);
}


void Time_A0_100ns(uint16_t t)
{
  upConfig.timerPeriod= PERIOD_TIME_A;
  upConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
  Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
  Interrupt_enableInterrupt(INT_TA0_N);
  Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);  
}
/*
// The function config TIMER_A1 in up mode, and time interrup is 1s
// start TIMER_A1 - start time close the door 
// open the door
*/
void Time_A1_1s()
{  
  ui8_time_open_door = 0;
  GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
  upConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
  upConfig.timerPeriod= 2000;
  Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);
  Interrupt_enableInterrupt(INT_TA1_N);
  Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
  
}



void TA0_N_IRQHandler(void)
{
  Timer_A_clearInterruptFlag(TIMER_A0_BASE);
  bo_input_pin_RFID = GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN6);
  if(bo_input_pin_RFID)
  {    
    GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN6,GPIO_HIGH_TO_LOW_TRANSITION);
    bo_edge_select = true;
  }
  else 
  {
    bo_edge_select = false;
    GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN6,GPIO_LOW_TO_HIGH_TRANSITION);
  }
  
}
void TA1_N_IRQHandler(void)
{
  Timer_A_clearInterruptFlag(TIMER_A1_BASE);
  ui8_time_open_door++;
  bo_input_sensor = GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5);
  if(!bo_input_sensor)
  {
    ui8_time_open_door = TIME_OPEN_DOOR_S;
    
  }
  if(ui8_time_open_door > TIME_OPEN_DOOR_S)
  {
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
    ui8_time_open_door = 0;
    Interrupt_disableInterrupt(INT_TA1_N);
  }
}


// Timer blink _ 300ms
void T32_INT2_IRQHandler(void)
{  
  Timer32_clearInterruptFlag(TIMER32_1_BASE);
  if(ui8_state != STATE_IDLE)
    ui16_idle++;
  
  if(ui16_idle > MAX_TIME_WAITING )
  {
    begin();
    bo_tag_RFID = false;
    ui16_idle = 0;
  }
  if(ui8_state == STATE_LOGIN|| ui8_state == STATE_ADD_USER || ui8_state == STATE_CHANGEPASS)
  {
    display_icon_blink(ui16_idle,x_blink,y_blink);  //600ms
  }
  Timer32_setCount  (TIMER32_1_BASE, 48000 * TIME_WAITING_KEY);
  Timer32_enableInterrupt(TIMER32_1_BASE);
  Timer32_startTimer(TIMER32_1_BASE, true);
}

