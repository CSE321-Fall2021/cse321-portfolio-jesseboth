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
 * Sources: 
 *        
 * 
*/
#include "mbed.h"

/** get string length 
input: 
        @param string
*/
int string_length(char *str);

/** convert string to int 
input: 
        @param str
output:
        @return int
*/
int string_to_int(char *str);

/** string to int with known length
input:
        @param str
        @param length - string length
output:
        @return int
*/
int string_to_int_wlen(char *str, int len);

