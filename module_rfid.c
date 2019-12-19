#include <string.h>
#include <math.h>
#include "driverlib.h"
#include "main.h"
#include "module_timer.h"

extern uint8_t ui8_check;
extern bool bo_edge_select;
extern uint16_t ui16_status;
uint8_t ui8_row = 0;
uint8_t ui8_col = 0;
uint8_t ui8_bit1 = 0;
uint32_t ui32_RFID_code=0;
bool bo_tag_RFID = false;
bool bo_read_complete = false;
/*
// The function interrup of PORT2, pin input RFID
//     - read RFID and return code RFID
*/
void INT_PORT2_Haldler(void)
{
  ui16_status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
  MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2,ui16_status);
  uint8_t array[11][5];
  uint8_t array1[8][4];
  uint8_t array2[8];
  if (GPIO_PIN6 & ui16_status)
  {    
    Time_A0_100ns(1);
    if(ui8_row<11 && bo_read_complete)
    {      
      array[ui8_row][ui8_col] = bo_edge_select;
      ui8_col++;
      if(ui8_col>4)
      {
        ui8_col = 0;
        ui8_row++;
      }
    }
    if(bo_edge_select)
    {
      ui8_bit1++;
      if(ui8_bit1==9)
      {
        bo_read_complete = true;
      }
    }
    else 
      ui8_bit1 = 0;
    if(ui8_row == 11)
    {
      for(int i=0;i<10;i++)
      {
        if((array[i][0]+array[i][1]+array[i][2]+array[i][3])%2 == array[i][4])
        {
          ui8_check = CHECK_TRUE;
        }
        else
        {
          ui8_check = CHECK_FALSE;
          break;
        }
      }
      if(ui8_check )
      {
        for(int i =0;i<8;i++)
        {
          for(int j=0;j<4;j++)
            
          {
            array1[i][j] = array[2+i][j];
          }
        }
        for(int i=0;i<8;i++)
        {
          array2[i] = array2[i]<<4;
          for(int j=0;j<4;j++)
          {
            
            array2[i]= array2[i]<<1  | array1[i][j];
          }
          
        }
        ui32_RFID_code = 0;
        for(int i=0;i<8;i++)
        {
          ui32_RFID_code = ui32_RFID_code + (array2[i] *(int) pow(16,7-i));
        }
        bo_tag_RFID = true;
        ui8_check = CHECK_FALSE;
        process_keypad();
      }
      
      bo_read_complete =  false;
      ui8_bit1 = 0;
      ui8_row =  ui8_col = 0;  
    }
  }
  
}


