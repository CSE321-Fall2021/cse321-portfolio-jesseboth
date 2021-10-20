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
#include "mbed.h"
#include "CSE321_project2_jessebot_lib.h"

#define TIMER_MAX_LEN 4  // code is capable of mm:ss
#define TIMER_SET_LEN 3  // set 3 for m:ss or 4 for mm:ss
#define TIMER_MAX_MIN 10 // value to truncate down to 9:59
#define TIMER_LOC 6
#define TIME_DELAY 500   // 5 seconds before prompt
struct timer;

void set_timer(int m, int s);
struct timer get_timer();
void inc_timer();
int goal_timer();
char *string_timer();
void int_timer();
void set_inc_by_timer(int by);
void set_press_timer(char c);
void reset_press_timer();
char *output_press_timer();
void swap_timer();
void reset_timer();
