#include "driverlib.h"
#include <string.h>
#include "module_uart.h"

void send_string_UART(char* data_string)
{
  for(int i=0;i<strlen(data_string);i++)
  {
    UART_transmitData(EUSCI_A2_BASE,data_string[i]);
  }
}