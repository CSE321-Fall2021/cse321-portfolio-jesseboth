/**
 * Author: Jesse Both
 * 
 * Assignment:  Project 2 Timer System
 * 
 * Purpose:     Library to deal with timer
 *              manipulation.
 * 
 * Global Vars: timer (struct)
 * 
 * Subroutines: 
 *              void set_timer(int m, int s);
 *              struct timer get_timer();
 *              void inc_timer(int by);
 *              int goal_timer(int m, int s);
 *              char *string_timer();
 * 
 * Sources: 
 *        
 * 
*/
#include "CSE321_project2_jessebot_timer.h"

// storage location for timer elements
struct timer{
    int minutes;
    int seconds;
    int inc_by = 0;     // default 0
    char str[6];        // mm:ss
    char min_goal = 0;  // default 0
    char sec_goal = 0;  // default 0 
    char press[5];      // mss
    char press_i = 0;
} timer;


/*
sets values in struct
input: 
        m (minutes)
        s (seconds)
*/
void set_timer(int m, int s){
    timer.minutes = m;
    timer.seconds = s;
}

/* returns struct */
struct timer get_timer(){
    return timer;
}

/* increments the timer by input

*/
void inc_timer(){
    timer.seconds += timer.inc_by;        //inc seconds 
    
    //check if minutes should be increased.
    if(timer.seconds == 60){
        timer.minutes += timer.inc_by;
        timer.seconds = 0;
    }
    else if(timer.seconds == -1){
        timer.minutes += timer.inc_by;
        timer.seconds = 59;
    }
}

/* check if goal is reached
output: 
        goal reached t/f
*/
int goal_timer(){
    if(timer.minutes == timer.min_goal && timer.seconds == timer.sec_goal){
        return true;
    }
    return false;
}

/* sets string in struct and returns string
output:
        string mm:ss
*/
char *string_timer(){
    int x = 0; // index
    if(timer.minutes < 10){
        timer.str[x++] = timer.minutes + '0';
    }
    else{
        // get 10's place by itself and convert to a char
        timer.str[x++] = ((timer.minutes - (timer.minutes % 10)) / 10) + '0';
        timer.str[x++] = (timer.minutes % 10) + '0';
    }

    timer.str[x++] = ':'; //place ':'
    if(timer.seconds < 10){
        timer.str[x++] = '0';
        timer.str[x++] = timer.seconds + '0';
    }
    else{
        // get 10's place by itself and convert to a char
        timer.str[x++] = ((timer.seconds - (timer.seconds % 10)) / 10) + '0';
        timer.str[x++] = (timer.seconds % 10) + '0';
    }
    timer.str[x] = 0;   // null terminate
    return timer.str;
}

/* sets the value for incrementation 
intput:
        by - +1 or -1
*/
void set_inc_by_timer(int by){
    timer.inc_by = by;
}

void set_press_timer(char c){
    if(timer.press_i < 3){
        timer.press[timer.press_i++] = c;
    }
}

void reset_press_timer(){
    while(timer.press_i > 0){
        timer.press[timer.press_i--] = 0;
    }
}

void decode_timer(){
    if(strlen(timer.press) == 3){
        timer.str[0] = timer.press[0];
        timer.minutes = string_to_int(timer.str);
        timer.str[1] = ':';
        timer.str[2] = timer.press[1];
        timer.str[3] = timer.press[2];
        timer.seconds = string_to_int(timer.str+2);
        
    }
    else{
        timer.str[0] = timer.press[0];
        timer.str[1] = timer.press[1];
        timer.minutes = string_to_int(timer.str);
        timer.str[2] = ':';
        timer.str[3] = timer.press[2];
        timer.str[4] = timer.press[3];
        timer.seconds = string_to_int(timer.str+3);
    }
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

int string_length(char *str){
    int i;
    for(i=0; *str != 0; i++, str++);
    return i;
}