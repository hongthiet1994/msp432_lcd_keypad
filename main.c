//#include "lcd.h"
#include <string.h>
#include <math.h>
#include "json_parse.h"
#include "module_keypad.h"
#include "module_display.h"
#include "module_rtc.h"
#include "lcd_st7565_lib.h"
#include "main.h"
#include "module_uart.h"
#include "module_itoa.h"
#include "module_timer.h"


#define ADDRESS_NUMBER_MEMBER   0x3E000

#define ADDRESS_USER_INFOR      0x3E001
//#define address_start_infor     0x3E001


#define CHECK_FALSE             0
#define CHECK_TRUE              1
#define CHECK_DISABLED          2
#define LENGTH_ARRAY            6
#define LENGTH_ARRAY1           3
#define MIN_KEY                 6
#define MAX_KEY                 10

#define TIME_LOCK               36000
#define MAX_WRONG               3
#define SIZE_KEY                10

#define TOTAL                   120

#define PRESS_ENTER_ONEC        1
#define PRESS_ENTER_TWICE       2
#define PRESS_ENTER_THREE       3


#define IP_LEN                  16
#define SSID_LEN                32

extern char buffer_rxdata[MAX_BUFFER];

extern const unsigned char font[][6] ;
extern const unsigned int  key1[4][4];
extern const unsigned char     key2[10][5];
extern const unsigned char     key3[10][5] ;
extern char  logo [] ;





extern RTC_C_Calendar newTime;




struct infor
{
  char          ch_user[SIZE_KEY];
  char          ch_pass[SIZE_KEY];
  uint8_t       ui8_ID;
  uint32_t      ui32_RFID;
  uint8_t       bo_role;
  uint8_t       ui8_wrong;
  uint32_t      ui32_timeopen;
}employees[TOTAL],employees_backspace;


enum NUMBER_KEY
{
  key_1 = 1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  key_7,
  key_8,
  key_9,
  key_0,
  key_case,
  key_enter,
  key_up,
  key_down,
  key_select,
  key_back
};

enum number_line
{
  line0=0,
  line1,
  line2,
  line3,
  line4,
  line5
};

void menu_returnKey(); 
void delete_returnKey();
void manage_returnKey();
void list_returnKey();
void profile_returnKey();
void RFID_returnKey();
void check_tag_RFID();
void returnKey();


void write_flash();
void add_RFID();
void change_password();
void lock_unlock_user();
void delete_user();
void list_user();
void manage_user();
void add_user();
void login();
void menu();
void get_character();

void special_Keys(int a);


void Time32_INT2_1ms(uint16_t t);
void Time32_INT1_1ms(uint16_t t);






bool bo_read_complete = false;
extern bool bo_tag_RFID;
bool bo_check_tag = false;
bool bo_key_role= false;
extern bool bo_edge_select;
extern bool press_key;
bool check = false;
bool add_user_rfid = false;
char buffer_num[SIZE_KEY];
char buffer_ID[SIZE_KEY];
char buffer_role[SIZE_KEY];
char buffer_wrong[SIZE_KEY];
char buffer_RFID[SIZE_KEY];
char buffer_timeOpen[SIZE_KEY];
char str_buffer_RFID[SIZE_KEY];
char str_key_user[SIZE_KEY];
char str_key_pass[SIZE_KEY];
char ssid[SSID_LEN];
char address_IP[IP_LEN];

char buffer_txdata[MAX_BUFFER];



int8_t i8_counter = 0;
int8_t x_lcd = 0,y_lcd = 0;
extern int8_t x_blink,y_blink;
int8_t line_in_menu = 0;
int8_t line_in_manage = 0;
int8_t line_in_list = 0;
uint8_t rx_id ;
uint8_t ui8_check = CHECK_FALSE;
uint8_t ui8_state = 0;
uint8_t i=0;
uint8_t ui8_press_enter = 0;
uint8_t ui8_font_word = 0;
uint8_t ui8_employee_code=0;
uint8_t ui8_employee_code_edit=0;
uint8_t ui8_number_member = 0;
uint8_t ui8_operation_select=0;
extern uint8_t ui8_key_input; 
uint8_t ui8_key_input_befor=0;
uint8_t ui8_key_input_late=0;
uint8_t ui8_bit1 = 0;
uint8_t ui8_row = 0;
uint8_t ui8_col = 0;

uint8_t ui8_time_open_door = 0;
uint8_t cout = 0;


extern uint8_t  ui8_num_cmd;

extern uint16_t ui16_status;
uint16_t ui16_idle = 0;
uint16_t ui16_count = 0;

uint32_t ui32_present_time;
uint32_t ui32_RFID_code=0;

char* UART_ssid= "SSID";
char* UART_ip  = "IP";
char* list_menu[LENGTH_ARRAY1] = {"System Information","User Management","Setting"};
char* list_edit[LENGTH_ARRAY]={"Profile User","Change Password User","Delete User",
"Lock/Unlock User","Add Tag RFID","Add User"};

void delay(uint32_t t)
{
  for(uint32_t i =0;i<10000;i++)
  {
    for(uint32_t j=0;j<t;j++);
  }
}

int main(void)
{
  // config and read Flash  
  FlashCtl_setWaitState(FLASH_BANK0, 2);
  FlashCtl_setWaitState(FLASH_BANK1, 2);
  
  
  PCM_setCoreVoltageLevel(PCM_VCORE1);
  FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,
                           FLASH_SECTOR30 | FLASH_SECTOR31);
  
  ui8_number_member = *(int *) ADDRESS_NUMBER_MEMBER;
  for(uint32_t x = 0;x <3000;x++)
  {
    employees[0].ch_user[x]= *((char *)ADDRESS_USER_INFOR+x ) ;
  }
  // config frequency
  CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);                   
  CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1); 
  
  //CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_4); 
  CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
  CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  
  
  
  // config input RFID                            
  GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN6);
  GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN6,GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN6);
  GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN6);
  // CONFIG OUTPUT DOOR
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
  GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
  GPIO_disableInterrupt(GPIO_PORT_P2, GPIO_PIN5);
  
  // config RTC
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
                                              GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
  CS_setExternalClockSourceFrequency(32000,48000000);
  CS_startLFXT(false);
  
  init_RTC(); 
  init_TIMER();
  init_UART_ESP();  
  // init
  init_LCD();
  init_keybad();
  clear_all_LCD();   
  begin();  
  Interrupt_enableMaster();
  
  while(1)
  {
    if(ui8_num_cmd!=0)
    {
      if(ui8_num_cmd == 1)
      {
        free_string(ssid,SSID_LEN);
        free_string(address_IP,IP_LEN);
        getValueString(buffer_rxdata,"SSID",ssid);
        getValueString(buffer_rxdata,"IP",address_IP);
        free_string(buffer_rxdata,MAX_BUFFER);
      }
      else if(ui8_num_cmd == 2)
      {
        for(int i=0;i<ui8_number_member;i++)
        {
          itoa(i,buffer_num);
          itoa(employees[i].ui32_RFID,buffer_RFID);
          itoa(employees[i].ui32_timeopen,buffer_timeOpen);
          itoa(employees[i].bo_role,buffer_role);
          itoa(employees[i].ui8_wrong,buffer_wrong);
          itoa(employees[i].ui8_ID,buffer_ID);
          
          strcat(buffer_txdata,"{\"CMD\":2,\"MEMBER\":");
          strcat(buffer_txdata,buffer_num);
          strcat(buffer_txdata,",\"USER\":\"");
          strcat(buffer_txdata,employees[i].ch_user);
          strcat(buffer_txdata,"\",\"PASS\":\"");
          strcat(buffer_txdata,employees[i].ch_pass);
          strcat(buffer_txdata,"\",\"RFID\":");
          strcat(buffer_txdata,buffer_RFID);
          strcat(buffer_txdata,",\"ROLE\":");
          strcat(buffer_txdata,buffer_role);
          strcat(buffer_txdata,",\"WRONG\":");
          strcat(buffer_txdata,buffer_wrong);
          strcat(buffer_txdata,",\"OPEN\":");
          strcat(buffer_txdata,buffer_timeOpen);
          strcat(buffer_txdata,",\"ID\":");
          strcat(buffer_txdata,buffer_ID);
          strcat(buffer_txdata,"}");
          
          send_string_UART(buffer_txdata);
          free_string(buffer_num,MAX_KEY);
          free_string(buffer_ID,MAX_KEY);
          free_string(buffer_txdata,MAX_BUFFER);
          free_string(buffer_RFID,MAX_KEY);
          free_string(buffer_timeOpen,MAX_KEY);
        }
        
      }
      else 
      {
        
        getValueInt(buffer_rxdata,"ID",&rx_id);
        for(int i=0;i<ui8_number_member;i++)
        {
          if(employees[i].ui8_ID == rx_id)
          {
            ui8_employee_code_edit = i;
            check = CHECK_TRUE;
            break;
          }
          check = CHECK_FALSE;
        }
        if(check == CHECK_TRUE)
        {
          if(ui8_num_cmd == 3)
          {
            free_string(str_key_pass,SIZE_KEY);
            getValueString(buffer_rxdata,"PASS",str_key_pass);
            free_string(employees[ui8_employee_code_edit].ch_pass,SIZE_KEY);
            strcpy(employees[ui8_employee_code_edit].ch_pass,str_key_pass);
            
            send_string_UART("{\"CMD\":3,\"CHECK\":\"SUCCESS\"}");
            
          }
          else if(ui8_num_cmd == 4)
          {
            for(i=ui8_employee_code_edit;i<ui8_number_member-1;i++)
            {
              employees[i] = employees[i+1];
            }
            employees[ui8_number_member-1] = employees_backspace;
            ui8_number_member--;
          }
          else if(ui8_num_cmd == 5)
          {
            if(employees[ui8_employee_code_edit].ui8_wrong == 3)
            {
              employees[ui8_employee_code_edit].ui8_wrong = 0;
            }
            else
            {
              employees[ui8_employee_code_edit].ui8_wrong = 3;
            }
          }
          else if(ui8_num_cmd == 6)
          {
            uint32_t rx_rfid = 0;
            free_string(buffer_RFID,SIZE_KEY);
            getValueString(buffer_rxdata,"RFID",buffer_RFID);
            rx_rfid = atoi(buffer_RFID);
            employees[ui8_employee_code_edit].ui32_RFID = rx_rfid;
          }
          else if(ui8_num_cmd == 7)
          {
            free_string(str_key_user,SIZE_KEY);
            free_string(str_key_pass,SIZE_KEY);
            free_string(buffer_RFID,SIZE_KEY);
            
            getValueString(buffer_rxdata,"USER",str_key_user);
            getValueString(buffer_rxdata,"PASS",str_key_pass);
            getValueString(buffer_rxdata,"RFID",buffer_RFID);
            getValueInt(buffer_rxdata,"ROLE",&bo_key_role);            
            strcpy(employees[ui8_number_member].ch_user, str_key_user);
            strcpy(employees[ui8_number_member].ch_pass, str_key_pass);
            employees[ui8_number_member].bo_role =  bo_key_role;
            employees[ui8_number_member].ui32_timeopen =  0;
            employees[ui8_number_member].ui8_wrong =  0;
            employees[ui8_number_member].ui8_ID = employees[ui8_number_member -1].ui8_ID +1;
            ui8_number_member++;
          }
          write_flash();
          free_string(buffer_rxdata,MAX_BUFFER);
          
        }
        else
        {
          send_string_UART("{\"CMD\":3,\"CHECK\":\"FAILE\"}") ;
          free_string(buffer_rxdata,MAX_BUFFER);
        }
      }
      check = CHECK_FALSE;
      reset_Receiver_uart();
    }
    if(press_key)
    {
      returnKey();
      press_key = false;
    }    
  }  
}

void T32_INT1_IRQHandler(void)
{
  Timer32_clearInterruptFlag(TIMER32_0_BASE);
  lcd_gotoxy(x_lcd,y_lcd);
  lcd_putc(ui8_key_input_late,1);
  if(ui8_press_enter == 0)
    str_key_user[i8_counter] = ui8_key_input_late;
  else if(ui8_press_enter == PRESS_ENTER_ONEC)
  {
    str_key_pass[i8_counter] = ui8_key_input_late;
    if(ui8_state == STATE_LOGIN)
    {
      lcd_gotoxy(x_lcd,y_lcd);
      lcd_putc('*',1);
    }
  }
  i8_counter++;
  x_lcd++;
  x_blink = x_lcd;
  ui16_count = 0;
  ui8_key_input_befor = 0;
  Time32_INT2_1ms(300); 
}


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
        returnKey();
      }
      
      bo_read_complete =  false;
      ui8_bit1 = 0;
      ui8_row =  ui8_col = 0;  
    }
  }
  
}



/*
// The function returns the function of the key that corresponds to each mode
*/
void returnKey(void)
{
  switch (ui8_state)
  {
  case STATE_IDLE :
    if(ui8_key_input == key_enter)
    {
      login();
    }
    check_tag_RFID();
    break;
  case STATE_LOGIN :
    get_character();
    check_tag_RFID(); 
    break;
  case STATE_MENU :
    menu_returnKey();
    break;
  case STATE_INFOR :
    if(ui8_key_input == key_back)
    {
      menu();
    }
    break;
  case STATE_PROFILE :
    profile_returnKey();
    break;
  case STATE_ADD_USER :
    get_character();
    break;
  case STATE_MANAGE :
    manage_returnKey();
    break;
  case STATE_DELETE :
    delete_returnKey();
    break;
  case STATE_CHANGEPASS :
    get_character();
    break;
  case STATE_LIST :
    list_returnKey();
    break;
  case STATE_ADD_RFID_CODE :
    RFID_returnKey();
    break;
  case STATE_CHOOSE : 
    if(ui8_key_input==key_enter)
    {
      ui16_idle = 0;
      menu();
    }
    break;
  default :
    break;
  }
  
}
/*
// The function handle keys with special functions in different modes
// example : key_enter, key_back...
*/
void special_Keys(int a)
{  
  if(ui8_key_input_befor != 0 )
  {    
    Timer32_setCount  (TIMER32_0_BASE, 1);
    Timer32_enableInterrupt(TIMER32_0_BASE);
    Timer32_startTimer(TIMER32_0_BASE, true);
  }  
  if(ui8_key_input_befor == 0 )
  {
    ui16_count = 0;
    if(a == key_enter)
    {
      ui8_press_enter ++;
      if(ui8_press_enter == PRESS_ENTER_ONEC)
      {
        lcd_gotoxy(x_blink, y_blink);
        lcd_putc(' ',1);
        if(ui8_state ==   STATE_CHANGEPASS)
        {
          x_lcd = 8;
        }
        else
        {
          x_lcd = 5;
        } 
        y_lcd = 4;
        i8_counter = 0;
      }
      else if(ui8_press_enter == PRESS_ENTER_TWICE)
      {
        lcd_gotoxy(x_blink,y_blink);
        lcd_putc(' ',1);
        if(ui8_state == STATE_LOGIN)
        {
          if(!strcmp(str_key_user,"")  || !strcmp(str_key_pass,"")  )
          {
            login();
            lcd_clear(0,21,7,7);
            lcd_gotoxy(0,7);
            lcd_puts("Enter full information",1);
            
          }
          else
          {
            
            for(int j=0;j<ui8_number_member;j++)
            {
              //if(!strcmp(str_key_user, employees[j].ch_user ) ) 
              if(1)  //edited by hongthiet  
              {
                ui8_employee_code = j;
                if(employees[ui8_employee_code].ui8_wrong== MAX_WRONG)
                {
                  ui32_present_time = getsec(newTime);
                  
                  //if(ui32_present_time > employees[ui8_employee_code].ui32_timeopen)
                  if(1)  //edited by hongthiet
                  {
                    employees[ui8_employee_code].ui8_wrong = 0;
                    
                  }
                  else
                  {  
                    ui8_check = CHECK_DISABLED;
                    break;
                  }
                }
                
                if(!strcmp(str_key_pass , employees[j].ch_pass)
                   &&(employees[ui8_employee_code].ui8_wrong< MAX_WRONG) )
                {
                  
                  ui8_check = CHECK_TRUE;
                  employees[ui8_employee_code].ui8_wrong = 0;
                  break;
                }
                else
                {
                  employees[ui8_employee_code].ui8_wrong++;
                  if(employees[ui8_employee_code].ui8_wrong == MAX_WRONG)                  
                  {
                    employees[ui8_employee_code].ui32_timeopen = getsec(newTime) + TIME_LOCK;
                    ui8_check = CHECK_DISABLED;
                    break;
                  }
                  else
                  {
                    ui8_check = CHECK_FALSE;
                  }
                }
                
              }
            }
            
            write_flash();
            if(ui8_check == CHECK_TRUE)
            {
              Time_A1_1s();
              if(employees[ui8_employee_code].bo_role)
              {
                clear_all_LCD();
                lcd_gotoxy(5,2);
                lcd_puts(employees[ui8_employee_code].ch_user,1);
                lcd_gotoxy(1,4);
                lcd_puts("Access Successful ",1);
                lcd_gotoxy(0,7);
                lcd_puts("Press Enter to Menu",1);
                ui8_state = STATE_CHOOSE;
                ui16_idle = MAX_TIME_WAITING - 3;
                Interrupt_disableInterrupt(INT_PORT2);
                Time32_INT2_1ms(300);
              }
              
              else
              {
                clear_all_LCD();
                lcd_gotoxy(5,2);
                lcd_puts(employees[ui8_employee_code].ch_user,1);
                lcd_gotoxy(1,4);
                lcd_puts("Access Successful ",1);
                ui8_state = STATE_WAWITING;
                ui16_idle = MAX_TIME_WAITING - 3;
                Interrupt_disableInterrupt(INT_PORT2);
                Time32_INT2_1ms(300);
              }
              
            }
            else if(ui8_check == CHECK_DISABLED)
            {
              lcd_clear(0,21,0,7);
              lcd_gotoxy(4,3);
              lcd_puts("your account",1);
              lcd_gotoxy(1,4);
              lcd_puts("has been disabled",1);
              //delay(800);
              ui8_state = STATE_IDLE;
              Interrupt_enableInterrupt(INT_PORT2);
            }
            else if(ui8_check == CHECK_FALSE)
            {
              login();
              lcd_gotoxy(0,7);
              lcd_puts("Acc or pass incorrect",1);
              Interrupt_enableInterrupt(INT_PORT2);
            }
          }
          
          ui8_check = CHECK_FALSE;
        }
        else if( ui8_state == STATE_ADD_USER)
        {
          Interrupt_disableInterrupt(INT_T32_INT2);
          Timer32_disableInterrupt(TIMER32_1_BASE);
          i8_counter = 0;
          lcd_clear(6,21,6,6);
          lcd_gotoxy(6,6);
          lcd_puts("Admin",0);
          lcd_gotoxy(14,6);
          lcd_puts("Member",1);
          bo_key_role = true;
        }
        else if(ui8_state == STATE_CHANGEPASS)
        {
          Interrupt_disableInterrupt(INT_T32_INT2);
          Timer32_disableInterrupt(TIMER32_1_BASE);
          lcd_clear(6,21,5,6);
          lcd_gotoxy(1,5);
          lcd_puts("Are you sure change?",1);
          lcd_gotoxy(3,6);
          lcd_puts("Yes",0);
          lcd_gotoxy(10,6);
          lcd_puts("No",1);
          ui8_check = CHECK_TRUE;
        }
      }
      else if(ui8_press_enter == PRESS_ENTER_THREE && ui8_state == STATE_ADD_USER)
      {
        if(!strcmp(str_key_user,"")  || !strcmp(str_key_pass,"") || (strlen(str_key_user)<MIN_KEY)
           || (strlen(str_key_user)>MAX_KEY) || (strlen(str_key_pass)<MIN_KEY) || (strlen(str_key_pass)>MAX_KEY))
        {
          add_user();
          lcd_clear(0,21,7,7);
          lcd_gotoxy(0,7);
          lcd_puts("Enter full information",1);
        }
        else
        {
          for(int j=0;j<ui8_number_member;j++)
          {
            if(!strcmp(str_key_user, employees[j].ch_user ) ) 
            {
              add_user();
              lcd_clear(0,21,7,7);
              lcd_gotoxy(0,7);
              lcd_puts("Acc already exists",1);
              ui8_check = CHECK_DISABLED;
              break;
              
            }
            ui8_check = CHECK_TRUE;
          }
          if(ui8_check == CHECK_TRUE)
          {
            strcpy(employees[ui8_number_member].ch_user, str_key_user);
            strcpy(employees[ui8_number_member].ch_pass, str_key_pass);
            employees[ui8_number_member].bo_role =  bo_key_role;
            employees[ui8_number_member].ui32_timeopen =  0;
            employees[ui8_number_member].ui8_wrong =  0;
            employees[ui8_number_member].ui8_ID = employees[ui8_number_member -1].ui8_ID +1;
            ui8_employee_code_edit = ui8_number_member;
            ui8_key_input = 0;
            add_user_rfid = true;
            add_RFID();
            
          }
          ui8_check = CHECK_FALSE;
        }
      }
      // press_enter ==2
      else if(ui8_press_enter == PRESS_ENTER_THREE && ui8_state ==   STATE_CHANGEPASS && ui8_check)
      {
        if(!strcmp(str_key_user,str_key_pass) && (strlen(str_key_user)>=MIN_KEY) && (strlen(str_key_user)<=MAX_KEY) 
           && (strcmp(str_key_pass,employees[ui8_employee_code_edit].ch_pass)!=0))
        {
          free_string(employees[ui8_employee_code_edit].ch_pass,SIZE_KEY);
          strcpy(employees[ui8_employee_code_edit].ch_pass,str_key_pass);
          write_flash();
          manage_user();
        }
        else
        {
          change_password();
          lcd_gotoxy(0,7);
          lcd_puts("Invalid password",1);
          
          
        }
      }
      else if(ui8_press_enter == PRESS_ENTER_THREE && ui8_state ==   STATE_CHANGEPASS && !ui8_check) 
      {
        manage_user();
      }
    } 
    // button backspace   
    if(a == key_back)
    {
      lcd_gotoxy(x_lcd, y_lcd);
      lcd_putc(' ',1);
      x_lcd--;
      if(x_lcd < 5)
      {
        x_lcd = 5;
      }
      lcd_gotoxy(x_lcd, y_lcd);
      lcd_putc(' ',1);
      if(ui8_press_enter == 0)
      {
        str_key_user[i8_counter]= '\0';
      }
      else if(ui8_press_enter == PRESS_ENTER_ONEC)
      {
        str_key_pass[i8_counter]= '\0';
      }
      i8_counter--;
      if(ui8_state == STATE_ADD_USER && i8_counter<0)
      {
        manage_user(); 
      }
      if(ui8_state == STATE_CHANGEPASS && i8_counter<0)
      {
        list_user();
      }
      if(ui8_state == STATE_LOGIN && i8_counter<0)  
      {
        begin();
      }
    }
    
    // button fontcase
    if(ui8_key_input == key_case)
    {
      ui8_key_input_befor = 0; 
      ui8_font_word++;
      if(ui8_font_word > 3 ) 
      {
        ui8_font_word = 0;
      }
      if((ui8_font_word%3) == 0)
      {
        lcd_gotoxy(18,0);
        lcd_puts("abc",0);
      }
      else if ((ui8_font_word%3)==1)
      {
        lcd_gotoxy(18,0);
        lcd_puts("ABC",0);
      }
      else
      {
        lcd_gotoxy(18,0);
        lcd_puts("123",0);
      }
    }
    if(ui8_key_input == key_up && ui8_state == STATE_ADD_USER && ui8_press_enter == PRESS_ENTER_TWICE)
    {
      lcd_clear(6,21,6,6);
      lcd_gotoxy(6,6);
      lcd_puts("Admin",0);
      lcd_gotoxy(14,6);
      lcd_puts("Member",1);
      bo_key_role = true;
    }
    if(ui8_key_input == key_down && ui8_state == STATE_ADD_USER && ui8_press_enter == PRESS_ENTER_TWICE)
    {
      lcd_clear(6,21,6,6);
      lcd_gotoxy(6,6);
      lcd_puts("Admin",1);
      lcd_gotoxy(14,6);
      lcd_puts("Member",0);
      bo_key_role = false;
    }
    if(ui8_key_input == key_up && ui8_state == STATE_CHANGEPASS && ui8_press_enter == PRESS_ENTER_TWICE)
    {
      lcd_clear(6,21,6,6);
      lcd_gotoxy(3,6);
      lcd_puts("Yes",0);
      lcd_gotoxy(10,6);
      lcd_puts("No",1);
      ui8_check = CHECK_TRUE;
    }
    if(ui8_key_input == key_down && ui8_state == STATE_CHANGEPASS && ui8_press_enter == PRESS_ENTER_TWICE)
    {
      lcd_clear(6,21,6,6);
      lcd_gotoxy(3,6);
      lcd_puts("Yes",1);
      lcd_gotoxy(10,6);
      lcd_puts("No",0);
      ui8_check = CHECK_FALSE;
    }
    ui8_key_input_befor = 0;
  }
}

/*
// The function config TIMER32_1 , and time interrup is 1ms
//  @param t is the number ms
*/
void Time32_INT1_1ms(uint16_t t)
{
  Interrupt_enableInterrupt(INT_T32_INT1);
  Timer32_setCount  (TIMER32_0_BASE, 48000 * t);
  Timer32_enableInterrupt(TIMER32_0_BASE);
  Timer32_startTimer(TIMER32_0_BASE, true);
  
}

/*
// The function config TIMER32_2 , and time interrup is 1ms
//  @param : t is the number ms
*/
void Time32_INT2_1ms(uint16_t t)
{
  Interrupt_enableInterrupt(INT_T32_INT2);
  Timer32_setCount  (TIMER32_1_BASE, 48000 * t);
  Timer32_enableInterrupt(TIMER32_1_BASE);
  Timer32_startTimer(TIMER32_1_BASE, true);
  
}

/*
// The function return mode = mode_changepass and screen :

//------------------------------
*/
void change_password()
{  
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(2,0);
  lcd_puts("CHANGE PASSWORD",1);
  lcd_gotoxy(0,2);
  lcd_puts("NewPass:",1);
  lcd_gotoxy(0,4);
  lcd_puts("Retype :",1);
  if((ui8_font_word%3) == 0)
  {
    lcd_gotoxy(18,0);
    lcd_puts("abc",0);
  }
  else if ((ui8_font_word%3)== 1)
  {
    lcd_gotoxy(18,0);
    lcd_puts("ABC",0);
  }
  else
  {
    lcd_gotoxy(18,0);
    lcd_puts("123",0);
  }
  x_lcd = x_blink = 8;
  y_lcd = y_blink = 2;
  for(i=0;i<10;i++)
  {
    str_key_user[i]='\0';
    str_key_pass[i]='\0';
  }
  i8_counter = 0;
  ui8_state = STATE_CHANGEPASS;
  ui8_press_enter = 0;
  ui8_key_input_befor = 0;
  Time32_INT2_1ms(300);
}
/*
// The function return mode = mode_delete and screen :

*/
void delete_user()
{
  
  ui8_state = STATE_DELETE;
  clear_all_LCD();
  
  lcd_gotoxy(2,2);
  lcd_puts("Are you sure want ",1);
  lcd_gotoxy(3,3); 
  lcd_puts("delete this user",1);
  lcd_gotoxy(4,5);
  lcd_puts("Yes: Enter",1);
  lcd_gotoxy(4,6);
  lcd_puts("No : Back",1);
}
void lock_unlock_user()
{
  
  if(employees[ui8_employee_code_edit].ui8_wrong == MAX_WRONG)
  {
    employees[ui8_employee_code_edit].ui8_wrong = 0;
    employees[ui8_employee_code_edit].ui32_timeopen = 0;
    write_flash();
    list_user();
  }
  else
  {
    employees[ui8_employee_code_edit].ui8_wrong = MAX_WRONG;
    employees[ui8_employee_code_edit].ui32_timeopen = getsec(newTime) + TIME_LOCK;
    write_flash();
    list_user();
  }
}
void profile_user()
{
  
  ui8_state = STATE_PROFILE;
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(3,0);
  lcd_puts("PROFILE USER ",1);
  lcd_gotoxy(0,2);
  lcd_puts("User:",1);
  lcd_puts(employees[ui8_employee_code_edit].ch_user,1);
  lcd_gotoxy(0,3);
  lcd_puts("Pass:",1);
  lcd_puts(employees[ui8_employee_code_edit].ch_pass,1);
  lcd_gotoxy(0,4);
  lcd_puts("Role:",1);
  if(employees[ui8_employee_code_edit].bo_role)
  {
    lcd_puts("Admin",1);
  }
  else
  {
    lcd_puts("Member",1);
  }
  lcd_gotoxy(0,5);
  lcd_puts("RFID:",1);
  if(employees[ui8_employee_code_edit].ui32_RFID==0)
  {
    lcd_putc('0',1);
  }
  else
  {
    itoa(employees[ui8_employee_code_edit].ui32_RFID,str_buffer_RFID);
    lcd_puts(str_buffer_RFID,1);
  }
  lcd_gotoxy(0,6);
  lcd_puts("ID: ",1);
  itoa(employees[ui8_employee_code_edit].ui8_ID,buffer_ID);
  lcd_puts(buffer_ID,1);
  
}


void login()
{  
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(8,0);
  lcd_puts("LOGIN",1);
  lcd_gotoxy(0,2);
  lcd_puts("User:",1);
  lcd_gotoxy(0,4);
  lcd_puts("Pass:",1);
  if((ui8_font_word%3) == 0)
  {
    lcd_gotoxy(18,0);
    lcd_puts("abc",0);
  }
  else if ((ui8_font_word%3)== 1)
  {
    lcd_gotoxy(18,0);
    lcd_puts("ABC",0);
  }
  else
  {
    lcd_gotoxy(18,0);
    lcd_puts("123",0);
  }
  x_lcd = x_blink =5;
  y_lcd = y_blink = 2;
  for(i=0;i<10;i++)
  {
    str_key_user[i]='\0';
    str_key_pass[i]='\0';
  }
  i8_counter = 0;
  ui8_state = STATE_LOGIN;
  Interrupt_enableInterrupt(INT_PORT2);
  ui8_press_enter = 0;
  ui8_key_input_befor = 0;
  Time32_INT2_1ms(300);
}
void menu()
{  
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(20,0);
  lcd_putc(0x7e,1);
  lcd_gotoxy(6,0);
  lcd_puts("MAIN MENU",1);
  for(i=0;i<LENGTH_ARRAY1;i++)
  {
    lcd_gotoxy(0,i+2);
    lcd_puts(list_menu[i],1);
  }
  lcd_gotoxy(0,line_in_menu+2);
  lcd_puts(list_menu[line_in_menu],0);
  ui8_state = STATE_MENU;
  ui8_operation_select = 0;  
  Time32_INT2_1ms(300);
}
void get_character()
{
  
  if(ui8_key_input>=key_1 && ui8_key_input <=key_0&& i8_counter <MAX_KEY)
  {
    Interrupt_disableInterrupt(INT_T32_INT2);
    Timer32_disableInterrupt(TIMER32_1_BASE);
    Time32_INT1_1ms(TIME_WAITING_KEY);
    lcd_clear(0,21,7,7);
    if(ui8_key_input == ui8_key_input_befor)
    {
      
      ui16_count++;
      if(ui16_count == 6) 
      {
        ui16_count = 1;
      }
      
      if((ui8_font_word%3)==0)
      {
        ui8_key_input_late = key3[ui8_key_input-1][ui16_count -1];
      }
      else if ((ui8_font_word%3)==1)
      {
        ui8_key_input_late = key2[ui8_key_input-1][ui16_count -1];
      }
      else
      {
        if(ui8_press_enter == 0)
        {
          ui8_key_input_late = ui8_key_input + 48;
          if(ui8_key_input_late == 58)
          {
            ui8_key_input_late = 48;
          }
          str_key_user[i8_counter] = ui8_key_input_late;
        }
        else
        {
          ui8_key_input_late = ui8_key_input + 48;
          if(ui8_key_input_late == 58)
          {
            ui8_key_input_late = 48;
          }
          str_key_pass[i8_counter] = ui8_key_input_late;
          lcd_gotoxy(x_lcd, y_lcd);
          lcd_putc('*',1);
        }
        i8_counter++;
        ui8_key_input_late = ui8_key_input+48;
        if(ui8_key_input_late ==58)
        {
          ui8_key_input_late = 48;
        }
        x_lcd++;
      }
      lcd_gotoxy(x_lcd, y_lcd);
      lcd_putc(ui8_key_input_late,1);
      
    }
    else if(ui8_key_input_befor == 0)
    {
      
      ui16_count = 1;
      if((ui8_font_word%3)==0)
      {
        ui8_key_input_late = key3[ui8_key_input-1][ui16_count -1];
      }
      else if ((ui8_font_word%3)== 1)
      {
        ui8_key_input_late = key2[ui8_key_input-1][ui16_count -1];
      }
      else
      {
        ui8_key_input_late = ui8_key_input+48;
        if(ui8_key_input_late == 58)
        {
          ui8_key_input_late = 48;
        }
      }
      lcd_gotoxy(x_lcd, y_lcd);
      lcd_putc(ui8_key_input_late,1);
      
    }
    else
    {
      if(ui8_press_enter == 0)
      {
        if((ui8_font_word%3) == 0)
        {
          str_key_user[i8_counter] = key3[ui8_key_input_befor - 1][ui16_count-1];
        }
        else if ((ui8_font_word%3)== 1)
        {
          str_key_user[i8_counter] = key2[ui8_key_input_befor-1][ui16_count -1];
        }
        else
        {
          ui8_key_input_late = ui8_key_input_befor+48;
          if(ui8_key_input_late == 58) 
          {
            ui8_key_input_late = 48;
          }
          str_key_user[i8_counter]= ui8_key_input_late;
        }
        
      }
      else if(ui8_press_enter == PRESS_ENTER_ONEC)
      {
        if((ui8_font_word%3)== 0)
        {
          str_key_pass[i8_counter] = key3[ui8_key_input_befor - 1][ui16_count-1];
        }
        else if ((ui8_font_word%3)==1)
        {
          str_key_pass[i8_counter] = key2[ui8_key_input_befor-1][ui16_count -1];
        }
        else
        {
          ui8_key_input_late = ui8_key_input_befor+48;
          if(ui8_key_input_late == 58)
          {
            ui8_key_input_late = 48;
          }
          str_key_pass[i8_counter] = ui8_key_input_late;
        }
        if(ui8_state == STATE_LOGIN)
        {
          lcd_gotoxy(x_lcd, y_lcd);
          lcd_putc('*',1);
        }
      }
      i8_counter++;
      ui16_count = 1;
      x_lcd++;
      if((ui8_font_word%3) == 0)
      {
        ui8_key_input_late = key3[ui8_key_input-1][ui16_count -1];
      }
      else if ((ui8_font_word%3)==1)
      {
        ui8_key_input_late = key2[ui8_key_input-1][ui16_count -1];
      }
      else
      {
        ui8_key_input_late = ui8_key_input+48;
        if(ui8_key_input_late == 58) 
        {
          ui8_key_input_late = 48;
        }
      }
      lcd_gotoxy(x_lcd, y_lcd);
      lcd_putc(ui8_key_input_late,1); 
    }
    ui8_key_input_befor = ui8_key_input;
  }
  else 
  {
    special_Keys(ui8_key_input);
  }
  y_blink = y_lcd;
  x_blink = x_lcd;
}

void write_flash()
{
  if(!MAP_FlashCtl_eraseSector(ADDRESS_NUMBER_MEMBER))
    while(1);
  if(!MAP_FlashCtl_programMemory (&ui8_number_member, (void*) ADDRESS_NUMBER_MEMBER, 1))
    while(1);
  if(!MAP_FlashCtl_programMemory (&employees[0], (void*) ADDRESS_USER_INFOR, 3960))
    while(1);
}

void list_user()
{
  
  ui8_state = STATE_LIST;
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(20,0);
  lcd_putc(0x7e,1);
  lcd_gotoxy(6,0);
  lcd_puts("LIST USER",1);
  for(i=(line_in_list/5)*5;(i<(line_in_list/5)*5+5) && ( i < ui8_number_member);i++)
  {
    lcd_gotoxy(0,(i%5)+2);
    lcd_puts(employees[i].ch_user,1);
    lcd_gotoxy(12,(i%5)+2);
    if(employees[i].ui8_wrong!=MAX_WRONG)
    {
      lcd_putc('v',1);
    }
    else
    {
      lcd_putc('x',1);
    }
    
  }
  lcd_gotoxy(0,line_in_list%5+2);
  lcd_puts(employees[line_in_list].ch_user,0);
  if((line_in_list/5)>0)
  {
    lcd_gotoxy(14,1);
    lcd_putc(30,1);
  }
  else
  {
    lcd_clear(0,21,1,1);
  }
  if(((ui8_number_member-1)/5)!= (line_in_list/5))
  {
    lcd_gotoxy(14,7);
    lcd_putc(31,1);
  }
  else
  {
    lcd_clear(0,21,7,7); 
  }
  lcd_gotoxy(14,((int)((float)line_in_list/(float)ui8_number_member)*5+2));
  lcd_putc('|',1);
}
void manage_user()
{
  clear_all_LCD();  
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(20,0);
  lcd_putc(0x7e,1);
  lcd_gotoxy(3,0);
  lcd_puts("MANANEMENT USER",1);
  for(i=0;i<LENGTH_ARRAY;i++)
  {
    lcd_gotoxy(0,i+2);
    lcd_puts(list_edit[i],1);
  }
  lcd_gotoxy(0,line_in_manage+2);
  lcd_puts(list_edit[line_in_manage],0);
  ui8_state = STATE_MANAGE;
  
}
void add_user()
{
  
  ui8_state = STATE_ADD_USER;
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(2,0);
  lcd_puts("ADD NEW USER",1);
  lcd_gotoxy(0,2);
  lcd_puts("User:",1);
  lcd_gotoxy(0,4);
  lcd_puts("Pass:",1);
  lcd_gotoxy(0,6);
  lcd_puts("Role: Admin   Member",1);
  if((ui8_font_word%3) == 0)
  {
    lcd_gotoxy(18,0);
    lcd_puts("abc",0);
  }
  else if ((ui8_font_word%3)== 1)
  {
    lcd_gotoxy(18,0);
    lcd_puts("ABC",0);
  }
  else
  {
    lcd_gotoxy(18,0);
    lcd_puts("123",0);
  }
  x_lcd = x_blink =5;
  y_lcd = y_blink = 2;
  for(i=0;i<10;i++)
  {
    str_key_user[i]='\0';
    str_key_pass[i]='\0';
  }
  i8_counter = 0;
  ui8_press_enter = 0;
  ui8_key_input_befor = 0;
  Time32_INT2_1ms(300);
}
void system_information()
{
  send_string_UART("{\"CMD\":1}");   
  ui8_state = STATE_INFOR;
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(2,0);
  lcd_puts("SYSTEM INFORMATION",1);
  lcd_gotoxy(0,2);
  lcd_puts("WIFI: ",1);
  lcd_puts(ssid,1);
  lcd_gotoxy(0,3);
  lcd_puts("IP: ",1);
  lcd_puts(address_IP,1);  
}


void add_RFID()
{
  
  ui32_RFID_code = 0;
  clear_all_LCD();
  lcd_gotoxy(0,0);
  lcd_putc(0x7f,1);
  lcd_gotoxy(4,0);
  lcd_puts("ADD TAG RFID",1);
  lcd_gotoxy(0,3);
  lcd_puts("Press Enter: Save",1);
  lcd_gotoxy(0,4);
  lcd_puts("Press Back : Cancel",1);
  lcd_gotoxy(0,7);
  lcd_puts("Please place the tag",1);
  ui8_state = STATE_ADD_RFID_CODE;
  Interrupt_enableInterrupt(INT_PORT2);
}
void list_returnKey()
{
  if(ui8_key_input == key_up)
  {
    lcd_clear(0,21,2,6);
    line_in_list--;
    if(line_in_list < 0)      line_in_list = ui8_number_member - 1;
    for(i=(line_in_list/5)*5;(i<(line_in_list/5)*5+5) && ( i < ui8_number_member);i++)
    {
      lcd_gotoxy(0,(i%5)+2);
      lcd_puts(employees[i].ch_user,1);
      lcd_gotoxy(12,(i%5)+2);
      if(employees[i].ui8_wrong!=MAX_WRONG)
      {
        lcd_putc('v',1);
      }
      else
      {
        lcd_putc('x',1);
      }
    }
    lcd_gotoxy(0,line_in_list%5+2);
    lcd_puts(employees[line_in_list].ch_user,0);
    if((line_in_list/5)>0)
    {
      lcd_gotoxy(14,1);
      lcd_putc(30,1);
    }
    else
    {
      lcd_clear(0,21,1,1);
    }
    if(((ui8_number_member-1)/5)!= (line_in_list/5))
    {
      lcd_gotoxy(14,7);
      lcd_putc(31,1);
    }
    else
    {
      lcd_clear(0,21,7,7);
    }
    lcd_gotoxy(14,((int)((float)line_in_list/(float)ui8_number_member)*5+2));
    lcd_putc('|',1);
  }
  else if(ui8_key_input == key_down)
  {
    lcd_clear(0,21,2,6);
    line_in_list++;
    if(line_in_list > ui8_number_member - 1)     
    {
      line_in_list = 0;
    }
    for(i=(line_in_list/5)*5;(i<(line_in_list/5)*5+5) && ( i < ui8_number_member);i++)
    {
      lcd_gotoxy(0,(i%5)+2);
      lcd_puts(employees[i].ch_user,1);
      lcd_gotoxy(12,(i%5)+2);
      if(employees[i].ui8_wrong!=MAX_WRONG)
      {
        lcd_putc('v',1);
      }
      else
      {
        lcd_putc('x',1);
      }
    }
    lcd_gotoxy(0,line_in_list%5+2);
    lcd_puts(employees[line_in_list].ch_user,0);
    if((line_in_list/5)>0)
    {
      lcd_gotoxy(14,1);
      lcd_putc(30,1);
    }
    else
      lcd_clear(0,21,1,1);
    if(((ui8_number_member-1)/5)!= (line_in_list/5))
    {
      lcd_gotoxy(14,7);
      lcd_putc(31,1);
    }
    else
    {
      lcd_clear(0,21,7,7);
    }
    lcd_gotoxy(14,((int)((float)line_in_list/(float)ui8_number_member)*5+2));
    lcd_putc('|',1);
  }
  else if(ui8_key_input == key_back)
  {
    line_in_list = 0;
    manage_user();
  }
  else if(ui8_key_input == key_select)
  {
    ui8_employee_code_edit = line_in_list;
    if(ui8_operation_select == line0)
    {
      profile_user();
    }
    if(ui8_operation_select == line1)
    {
      change_password();
    }
    if(ui8_operation_select == line2)
    {
      delete_user();
    }
    if(ui8_operation_select == line3)
    {
      
      lock_unlock_user();
    }
    if(ui8_operation_select == line4)
    {
      add_RFID();
    }
  }
}
void manage_returnKey()
{
  if(ui8_key_input == key_up)
  {
    lcd_clear(0,21,2,7);
    line_in_manage--;
    if(line_in_manage < 0)     
    {
      line_in_manage = LENGTH_ARRAY -1;
    }
    for(i=0;i<LENGTH_ARRAY;i++)
    {
      lcd_gotoxy(0,i+2);
      lcd_puts(list_edit[i],1);
    }
    lcd_gotoxy(0,line_in_manage+2);
    lcd_puts(list_edit[line_in_manage],0);
  }
  if(ui8_key_input == key_down)
  {
    lcd_clear(0,21,2,7);
    line_in_manage++;
    if(line_in_manage > LENGTH_ARRAY -1)  
    {
      line_in_manage = 0;
    }
    for(i=0;i<LENGTH_ARRAY;i++)
    {
      lcd_gotoxy(0,i+2);
      lcd_puts(list_edit[i],1);
    }
    lcd_gotoxy(0,line_in_manage+2);
    lcd_puts(list_edit[line_in_manage],0);
  }
  if(ui8_key_input == key_back)
  {
    line_in_manage = 0;
    menu();
  }
  if(ui8_key_input == key_select)
  {
    ui8_operation_select = line_in_manage;
    if(ui8_operation_select!=line5)
    {
      list_user();
    }
    else
    {
      add_user();
    }
  } 
}
void delete_returnKey()
{
  if(ui8_key_input == key_enter)
  {
    for(i=ui8_employee_code_edit;i<ui8_number_member-1;i++)
    {
      employees[i] = employees[i+1];
    }
    employees[ui8_number_member-1] = employees_backspace;
    ui8_number_member--;
    write_flash();
    if(ui8_employee_code_edit == ui8_employee_code)
    {
      login();
    }
    else if(ui8_employee_code_edit == ui8_number_member )
    {
      line_in_list = ui8_number_member - 1;
      list_user();
    }
    else
    {
      list_user();
    }
  }
  else if(ui8_key_input == key_back)
  {
    list_user();
  }
}
void menu_returnKey()
{
  if(ui8_key_input == key_select)
  {
    if(line_in_menu == line0)
    {
      system_information();
      
    }
    else if(line_in_menu == line1)
    {
      manage_user();
    }
    else if (line_in_menu == line2 )
    {
      
    }
  }
  if(ui8_key_input == key_back)
  {
    begin();
    bo_tag_RFID = false;
  }
  else if(ui8_key_input == key_up)
  {
    line_in_menu--;
    if(line_in_menu < 0)
      line_in_menu = LENGTH_ARRAY1 - 1;
    for(i=0;i<LENGTH_ARRAY1;i++)
    {
      lcd_gotoxy(0,i+2);
      lcd_puts(list_menu[i],1);
    }
    lcd_gotoxy(0,line_in_menu+2);
    lcd_puts(list_menu[line_in_menu],0);
  }
  else if(ui8_key_input == key_down)
  {
    line_in_menu++;
    if(line_in_menu > LENGTH_ARRAY1-1)
      line_in_menu = 0;
    for(i=0;i<LENGTH_ARRAY1;i++)
    {
      lcd_gotoxy(0,i+2);
      lcd_puts(list_menu[i],1);
    }
    lcd_gotoxy(0,line_in_menu+2);
    lcd_puts(list_menu[line_in_menu],0);
  }
}
void profile_returnKey()
{
  if(ui8_key_input == key_back)
  {
    list_user();
  }
}
void RFID_returnKey()
{
  if (bo_tag_RFID && ui32_RFID_code != 0)
  {
    
    for(int j=0;j<ui8_number_member;j++)
    {
      if(ui32_RFID_code == employees[j].ui32_RFID)
      {
        bo_check_tag = true;
        break;
      }
      bo_check_tag = false;
    }
    if(bo_check_tag)
    {
      lcd_clear(0,21,0,7);
      lcd_gotoxy(1,4);
      lcd_puts("Card already exists",1);
      delay(300);
      add_RFID();
    }
    else
    {
      
      itoa(ui32_RFID_code,str_buffer_RFID);
      lcd_clear(0,21,0,7);
      lcd_gotoxy(6,2);
      lcd_puts(str_buffer_RFID,1);
      lcd_gotoxy(0,4);
      lcd_puts("Add tag RFID success",1);
      lcd_gotoxy(0,6);
      lcd_puts("Press Enter: Save",1);
      lcd_gotoxy(0,7);
      lcd_puts("Press Back : Cancel",1);
      Interrupt_disableInterrupt(INT_PORT2);
      
    }
  }
  if(ui8_key_input == key_back )
  {
    
    list_user();
    Interrupt_disableInterrupt(INT_PORT2);
  }
  if(ui8_key_input == key_enter )
  {
    employees[ui8_employee_code_edit].ui32_RFID = ui32_RFID_code;
    ui32_RFID_code = 0;
    if(add_user_rfid)
    {
      ui8_number_member++;
      add_user_rfid = false;
    }
    
    write_flash();
    list_user();
  }
}

void check_tag_RFID()
{
  if (bo_tag_RFID && ui32_RFID_code != 0)
  {
    Interrupt_disableInterrupt(INT_T32_INT1);
    for(int j=0;j<ui8_number_member;j++)
    {
      if(ui32_RFID_code == employees[j].ui32_RFID)
      {
        ui8_employee_code = j;
        bo_check_tag = true;
        break;
      }
      bo_check_tag = false;
    }
    if(bo_check_tag && employees[ui8_employee_code].ui8_wrong != MAX_WRONG) 
    {
      bo_tag_RFID = false;
      ui32_RFID_code = 0;
      bo_check_tag = 0;
      Time_A1_1s();
      if(employees[ui8_employee_code].bo_role)
      {
        clear_all_LCD();
        lcd_gotoxy(6,2);
        lcd_puts(employees[ui8_employee_code].ch_user,1);
        lcd_gotoxy(1,4);
        lcd_puts("Access Successful ",1);
        lcd_gotoxy(0,7);
        lcd_puts("Press Enter to Menu",1);
        ui8_state = STATE_CHOOSE;
        ui16_idle = MAX_TIME_WAITING - 3;
        Interrupt_disableInterrupt(INT_PORT2);
        Time32_INT2_1ms(300);
      }
      else
      {
        clear_all_LCD();
        lcd_gotoxy(6,2);
        lcd_puts(employees[ui8_employee_code].ch_user,1);
        lcd_gotoxy(1,4);
        lcd_puts("Access Successful ",1);
        ui8_state = STATE_WAWITING;
        ui16_idle = MAX_TIME_WAITING - 2;
        Interrupt_disableInterrupt(INT_PORT2);
        Time32_INT2_1ms(300);
      }
    }
    else
    {
      bo_tag_RFID = false;
      ui32_RFID_code = 0;
      bo_check_tag = 0;
      clear_all_LCD();
      lcd_gotoxy(3,3);
      lcd_puts("Acces Denied",1);
      ui8_state = STATE_WAWITING;
      ui16_idle = MAX_TIME_WAITING - 2;
      Interrupt_disableInterrupt(INT_PORT2);
      Time32_INT2_1ms(300);
    }    
  }
}

