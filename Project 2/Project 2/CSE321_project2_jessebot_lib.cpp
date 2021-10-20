/**
 * Author: Jesse Both
 * 
 * Assignment:  Project 2 Timer System
 * 
 * Purpose:     Library to deal with misc. operations.
 * 
 * Constraints: 
 *              see main
 * 
 * Subroutines: 
 *              string_length(char *str)
 *              string_to_int(char *str)
 *              string_to_int_wlen(char *str, int len)
 * 
 * Global Vars: N/A
 *              
 * 
 * Sources: Source Code (GPIO_TypeDef)
 *        
 * 
*/

#include "CSE321_project2_jessebot_lib.h"

/* get string length 
input: 
        string
*/
int string_length(char *str){
    int i;
    for(i=0; *str != 0; i++, str++);
    return i;
}

/* convert string to int 
input: 
        str
output:
        int
*/
int string_to_int(char *str){
    int mult = 1;
    char *cpy = str-1; 
    str += string_length(str)-1;
    int ret = 0;
    while(str != cpy){
        ret += (*str - '0')*mult;
        mult*=10;
        str--;
    }
    return ret;
}

/* string to int with known lenght
input:
        str
        length - string length
output:
        int
*/
int string_to_int_wlen(char *str, int len){
    int mult = 1;
    char *cpy = str-1; 
    str += len-1;
    int ret = 0;
    while(str != cpy){
        ret += (*str - '0')*mult;
        mult*=10;
        str--;
    }
    return ret;
}


