#include "driverlib.h"
#include <string.h>
#include "module_uart.h"
#include "json_parse.h"

const eUSCI_UART_Config uartConfig =
{
  EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
  26,                                     // BRDIV = 78
  1,                                       // UCxBRF = 2
  0,                                       // UCxBRS = 0
  EUSCI_A_UART_NO_PARITY,                  // No Parity
  EUSCI_A_UART_LSB_FIRST,                  // LSB First
  EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
  EUSCI_A_UART_MODE,                       // UART mode
  EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};



char buffer_rxdata[MAX_BUFFER];

char RXData;

uint8_t ui8_numofopen = 0;
uint8_t ui8_numofclose = 0;
uint16_t ui16_index_buffer_RX_uart = 0;
uint8_t  ui8_num_cmd = 0;


void init_UART_ESP()
{
   // config UART
  GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                                             GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
  UART_initModule(EUSCI_A2_BASE, &uartConfig);
  UART_enableModule(EUSCI_A2_BASE);
  UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
  Interrupt_enableInterrupt(INT_EUSCIA2);

}

void send_string_UART(char* data_string)
{
  for(int i=0;i<strlen(data_string);i++)
  {
    UART_transmitData(EUSCI_A2_BASE,data_string[i]);
  }
}




// uart esp32
void EUSCIA2_IRQHandler(void)
{
  uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
  
  MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);
  
  if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
  {
    RXData = MAP_UART_receiveData(EUSCI_A2_BASE);   
    
    if(RXData == '{')
    {
      ui8_numofopen++;
      if(ui8_numofopen == 1)
      {
        // start receive
        
        ui16_index_buffer_RX_uart = 0;
        buffer_rxdata[ui16_index_buffer_RX_uart] = RXData;
        
      }
      else
      {
        ui16_index_buffer_RX_uart++;
        buffer_rxdata[ui16_index_buffer_RX_uart] = RXData;
      }
    }
    else
    {
      if(RXData == '}')
      {
        ui8_numofclose++;
        if(ui8_numofclose == ui8_numofopen)
        {
          ui16_index_buffer_RX_uart++;
          buffer_rxdata[ui16_index_buffer_RX_uart] = RXData;
          
          getValueInt(buffer_rxdata,"CMD",&ui8_num_cmd);
          
        }
        else
        {
          ui16_index_buffer_RX_uart++;
          buffer_rxdata[ui16_index_buffer_RX_uart] = RXData; 
        }        
      }
      else
      {
        ui16_index_buffer_RX_uart++;
        buffer_rxdata[ui16_index_buffer_RX_uart] = RXData;
      }      
    }    
  }  
}

void reset_Receiver_uart()
{
ui8_numofclose=0;
ui8_numofopen=0;
ui16_index_buffer_RX_uart=0;
ui8_num_cmd = 0;
}