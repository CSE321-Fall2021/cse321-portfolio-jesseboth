/**
 * Author: Jesse Both
 * 
 * Assignment:  Project 2 Timer System
 * 
 * Purpose:     Library to deal with timer manipulation.
 * 
 * Constraints: 
 *              see main
 * 
 * Subroutines: 
 *              void set_timer(int m, int s)
 *              struct timer get_timer()
 *              void inc_timer(int by)
 *              int goal_timer(int m, int s)
 *              char *string_timer()
 *              void int_timer()
 *              void set_inc_by_time
 * 
 * 
 * Global Vars: 
 *              timer (struct)
 *                  * minutes - current minutes
 *                  * seconds - current seconds
 *                  * inc_by - increment or decrement or zero
 *                  * str[TIMER_SET_LEN+2] - output string m:ss
 *                  * min_goal - goal 0 or set minutes 'C' dependent
 *                  * sec_goal - goal 0 or set seconds 'C' dependent
 *                  * press[TIMER_SET_LEN+1] - storage string for input
 *                  * press_i - press index
 *              
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
    int inc_by = 0;             // default 0
    char str[TIMER_SET_LEN+2];  // m:ss
    char min_goal = 0;          // default 0
    char sec_goal = 0;          // default 0 
    char press[TIMER_SET_LEN+1];// mss
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

/* returns timer struct */
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
    int x = 0;      // index
    if(timer.minutes < 10){
        timer.str[x++] = timer.minutes + '0';       // string to int
    }
    else{
        // get 10's place by itself and convert to a char
        timer.str[x++] = ((timer.minutes - (timer.minutes % 10)) / 10) + '0';
        timer.str[x++] = (timer.minutes % 10) + '0';
    }

    timer.str[x++] = ':'; //place ':'
    if(timer.seconds < 10){
        timer.str[x++] = '0';                       // place 0
        timer.str[x++] = timer.seconds + '0';       // string to int
    }
    else{
        // get 10's place by itself and convert to a char
        timer.str[x++] = ((timer.seconds - (timer.seconds % 10)) / 10) + '0';
        timer.str[x++] = (timer.seconds % 10) + '0'; // ones digit
    }
    timer.str[x] = 0;   // null terminate
    return timer.str;
}

/* convert timer string to ints */
void int_timer(){
    if(string_length(timer.press) < TIMER_MAX_LEN){
        timer.minutes = string_to_int_wlen(timer.str, 1);
        timer.seconds = string_to_int_wlen(timer.str+2, 2);
    }
    else if(string_length(timer.press) == TIMER_MAX_LEN){
        timer.minutes = string_to_int_wlen(timer.str, 2);
        timer.seconds = string_to_int_wlen(timer.str+3, 2);
    }
    
    /* make time a 'valid' time */
    if(timer.seconds > 59){
        timer.minutes++;
        timer.seconds-=60;
    }

    /* make time within range of valid time */
    if(timer.minutes >= TIMER_MAX_MIN){
        timer.minutes = TIMER_MAX_MIN-1;
        timer.seconds = 59;
    }
}

/* sets the value for incrementation 
intput:
        by - +1 or -1
*/
void set_inc_by_timer(int by){
    timer.inc_by = by;
}

/* set the 'press_timer' string at the current
    index with the input.
input:
        c - char (0-9)
*/
void set_press_timer(char c){
    if(timer.press_i == 0 && c == '0'){}        // ignore leading 0's
    else if(timer.press_i < TIMER_SET_LEN){
        timer.press[timer.press_i++] = c;       // place in placeholder string
    }
    printf("%s\n", timer.press);
}

/* set the press string to null */
void reset_press_timer(){
    while(timer.press_i > 0){
        timer.press[timer.press_i--] = 0;       // make placeholder string null
    }
}

/* get the timer in the correct format m:ss */
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
        return (char *)0;       // null
    }

    while(i<timer.press_i){
        timer.str[cur--] = timer.press[end--];      // place digit
        i++;                                    
        /* check if colon is appropriate */
        if(cur == colon){
            timer.str[cur--] = ':';
        }
    }
    while(cur >= 0){
        timer.str[cur--] = '0';                     // place 0's
        /* check if colon is approriate */
        if(cur == colon){
            timer.str[cur--] = ':';
        }
    }
    return timer.str;
}

/* swap the goal and the current time*/
void swap_timer(){
    int temp_m, temp_s;
    temp_m = timer.min_goal;
    temp_s = timer.sec_goal;
    timer.min_goal = timer.minutes;
    timer.sec_goal = timer.seconds;
    timer.minutes = temp_m;
    timer.seconds = temp_s;
}

/* reset timer values */
void reset_timer(){
    reset_press_timer();
    timer.minutes = 0;
    timer.seconds = 0;
    timer.inc_by = 0;
    timer.min_goal = 0;
    timer.sec_goal = 0;
    timer.press_i = 0;
}