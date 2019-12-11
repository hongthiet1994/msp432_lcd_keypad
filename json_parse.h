#ifndef __JSON_PARSE_H
#define __JSON_PARSE_H
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_OUTPUT_LEN		100
int getValueString(const char* stringdata,char* fieldName,char* outputString);
int getValueInt(const char* jsonData,char* fieldName,uint8_t* outputNumber);
void free_string(char* string,uint32_t len);

#endif