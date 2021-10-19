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
    char press[6];      // mss
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

void int_timer(){
    if(string_length(timer.press) < TIMER_MAX_LEN){
        timer.minutes = string_to_int_wlen(timer.str, 1);
        timer.seconds = string_to_int_wlen(timer.str+2, 2);
    }
    else if(string_length(timer.press) == TIMER_MAX_LEN){
        timer.minutes = string_to_int_wlen(timer.str, 2);
        timer.seconds = string_to_int_wlen(timer.str+3, 2);
    }
    
    if(timer.seconds > 59){
        timer.minutes++;
        timer.seconds-=60;
    }
}

/* sets the value for incrementation 
intput:
        by - +1 or -1
*/
void set_inc_by_timer(int by){
    timer.inc_by = by;
}

void set_press_timer(char c){
    if(timer.press_i == 0 && c == '0'){}
    else if(timer.press_i < TIMER_SET_LEN){
        timer.press[timer.press_i++] = c;
    }
    printf("%s\n", timer.press);
}

void reset_press_timer(){
    while(timer.press_i > 0){
        timer.press[timer.press_i--] = 0;
    }
}

char *output_press_timer(){
    // mm:ss
    int i, cur, end, colon;  
    if(timer.press_i < TIMER_MAX_LEN){
        i = 0;
        cur = 3;
        end = timer.press_i-1;
        colon = 1;

    }
    else if(timer.press_i == TIMER_MAX_LEN){
        i = 0;
        cur = 4;
        end = timer.press_i-1;
        colon = 2;
    }
    else{
        return (char *)0;
    }

    while(i<timer.press_i){
        timer.str[cur--] = timer.press[end--];
        i++;
        if(cur == colon){
            timer.str[cur--] = ':';
        }
    }
    while(cur >= 0){
        timer.str[cur--] = '0';
        if(cur == colon){
            timer.str[cur--] = ':';
        }
    }
    return timer.str;
}

void swap_timer(){
    int temp_m, temp_s;
    temp_m = timer.min_goal;
    temp_s = timer.sec_goal;
    timer.min_goal = timer.minutes;
    timer.sec_goal = timer.seconds;
    timer.minutes = temp_m;
    timer.seconds = temp_s;
}

void reset_timer(){
    reset_press_timer();
    timer.minutes = 0;
    timer.seconds = 0;
    timer.inc_by = 0;
    timer.min_goal = 0;
    timer.sec_goal = 0;
    timer.press_i = 0;
}