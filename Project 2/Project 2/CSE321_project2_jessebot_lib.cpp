#include "CSE321_project2_jessebot_lib.h"
int string_length(char *str){
    int i;
    for(i=0; *str != 0; i++, str++);
    return i;
}

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


