#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "module_rtc.h"
#include "module_display.h"
#include "lcd_st7565_lib.h"

extern uint8_t ui8_state;
char * DaysOfWeek[] = { "SUN", "MON", "TUE", "WED", "THU","FRI","SAT" };

RTC_C_Calendar newTime;

const RTC_C_Calendar currentTime =
{
  0,
  10,
  11,
  4,
  5,
  9,
  2019
};

void init_RTC()
{
RTC_C_initCalendar(&currentTime, RTC_C_FORMAT_BINARY);
  newTime = currentTime;
  RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);
  RTC_C_clearInterruptFlag(
                           RTC_C_CLOCK_READ_READY_INTERRUPT|RTC_C_TIME_EVENT_INTERRUPT
                             | RTC_C_CLOCK_ALARM_INTERRUPT);
  RTC_C_enableInterrupt(
                        RTC_C_CLOCK_READ_READY_INTERRUPT|RTC_C_TIME_EVENT_INTERRUPT
                          | RTC_C_CLOCK_ALARM_INTERRUPT);
  RTC_C_startClock();
  Interrupt_enableInterrupt(INT_RTC_C);
}
void RTC_C_IRQHandler(void)
{
  uint32_t status;
  status = MAP_RTC_C_getEnabledInterruptStatus();
  MAP_RTC_C_clearInterruptFlag(status);
  newTime = MAP_RTC_C_getCalendarTime();  
  if(ui8_state == STATE_IDLE)
  {
    lcd_gotoxy(11,0);
    display_char((newTime.hours)/10+48,1);
    display_char((newTime.hours)%10+48,1);
    display_char(':',1);
    display_char((newTime.minutes)/10+48,1);
    display_char((newTime.minutes)%10+48,1);
    display_char(':',1);
    display_char((newTime.seconds)/10+48,1);
    display_char((newTime.seconds)%10+48,1);
    
    lcd_gotoxy(7,1);
    lcd_puts(DaysOfWeek[newTime.dayOfWeek],1);
    display_char(',',1);
    display_char((newTime.dayOfmonth)/10+48,1);
    display_char((newTime.dayOfmonth)%10+48,1);
    display_char('/',1);
    display_char((newTime.month)/10+48,1);
    display_char((newTime.month)%10+48,1);
    display_char('/',1);
    display_char((newTime.year)/1000+48,1);
    display_char(((newTime.year)%1000)/100+48,1);
    display_char(((newTime.year)%100)/10+48,1);
    display_char(((newTime.year)%10)+48,1);
  }
  
}

time_t getsec(RTC_C_Calendar x)
{
  struct tm t;
  t.tm_year = x.year - 1970;
  t.tm_mon = x.month;
  t.tm_mday = x.dayOfmonth;
  t.tm_hour = x.hours;
  t.tm_min = x.minutes;
  t.tm_sec = x.seconds;
  t.tm_isdst = -1;
  return mktime(&t);
}
