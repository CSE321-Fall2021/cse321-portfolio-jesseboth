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
    char str[6]; // mm:ss
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
input:
        by (incrementation value)
*/
void inc_timer(int by){
    timer.seconds += by;        //inc seconds 
    
    //check if minutes should be increased.
    if(timer.seconds == 60){
        timer.minutes += by;
        timer.seconds = 0;
    }
    else if(timer.seconds == 0){
        timer.minutes += by;
        timer.seconds = 59;
    }
    
}

/* check if goal is reached
input:
        m (minutes)
        s (seconds)
output: 
        goal reached t/f
*/
int goal_timer(int m, int s){
    if(timer.minutes == m && timer.seconds == s){
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

