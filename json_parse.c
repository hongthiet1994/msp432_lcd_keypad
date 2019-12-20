#include "json_parse.h"



/***  getValueString
**
**  Parameters:
**      Input stringdata 
**      iStart
**      iEnd
**      fieldName         
**      outputString      
**  Return Value:
**      none    
**  Description:
**    	parser string in stringdata: {"CMD":1,"TYPE":"ABC"}
**			Outputstring: ABC
***/
int getValueString(const char* stringdata,char* fieldName,char* outputString)
{
  uint32_t iStart = 0;
  uint32_t iEnd = strlen(stringdata);
  char fieldPlus[20]={0};
  uint32_t patternLen=0;
  uint32_t i=0,m=0,n=0;   
  strcat(fieldPlus,"\"");
  strcat(fieldPlus,fieldName);
  strcat(fieldPlus,"\":\"");  
  patternLen =strlen(fieldPlus);  
  i = iStart; 
  while (i <= iEnd - patternLen)
  {
    m = 0;
    // if first character of search string matches    
    if(stringdata[i+m]==fieldPlus[m])
    {
      while((m<patternLen) && (stringdata[i+m]==fieldPlus[m])) 
      {        
        m++;
      }
      if(m==patternLen)
      {   
        n = 0;
        while((m+i < iEnd) && ((n < MAX_OUTPUT_LEN) && stringdata[m+i] != '\"'))
        {
          outputString[n]=stringdata[i+m];
          m++;
          n++;
        }
        return 0;
      }         
    }
    i++;
  }
  return -1;   
}


/***  getValueInt
**
**  Parameters:
**      Input stringdata 
**      iStart
**      iEnd
**      fieldName         
**      outputNumber      
**  Return Value:
**      none    
**  Description:
**    	parser string in stringdata: {"CMD":1,"TYPE":234}
**			outputNumber: 234
***/
int getValueInt(const char* jsonData,char* fieldName,uint8_t* outputNumber)
{
  uint32_t iStart =0;
  uint32_t iEnd = strlen(jsonData);
  
  char fieldPlus[20]={0};
  uint32_t patternLen=0;
  char bufferOutputnumber[11]={0};
  uint32_t i=0,m=0,n=0;   
  strcat(fieldPlus,"\"");
  strcat(fieldPlus,fieldName);
  strcat(fieldPlus,"\":");  
  patternLen =strlen(fieldPlus);    
  i = iStart;  
  while (i <= (iEnd - patternLen))
  {
    m = 0;
    // if first character of search string matches    
    if(jsonData[i+m]==fieldPlus[m])
    {
      while((m<patternLen) && (jsonData[i+m] == fieldPlus[m])) 
      {        
        m++;
      }
      if(m==patternLen)
      {   
        n = 0;
        while((m+i < iEnd) && (n < MAX_OUTPUT_LEN) && (jsonData[m+i] != ',') && (jsonData[m+i] != '}'))
        {
          bufferOutputnumber[n]=jsonData[i+m];
          m++;
          n++;
        }
        *outputNumber=atol(bufferOutputnumber);         
        return 0;
      }         
    }
    i++;
  }
  return -1;  
}
void free_string(char* string_input,uint32_t len)
{  
  memcpy(string_input,0x00,len);
}