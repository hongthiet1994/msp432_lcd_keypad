#include <string.h>
#include <math.h>
#include "driverlib.h"
#include "module_timer.h"

extern uint8_t ui8_time_open_door;

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
