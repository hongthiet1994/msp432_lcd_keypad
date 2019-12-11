#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "module_rtc.h"



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
