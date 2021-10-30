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
 * Global Vars:
 *              keys - 4x4 array
 *              key  - single char
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
 * Sources: 
 *        
 * 
*/
#include "mbed.h"
#include "CSE321_project2_jessebot_gpio.h"

/*
    Keypad Matrix Config

    COL
    pin 1 - PF_13
    pin 2 - PE_9
    pin 3 - PE_11
    pin 4 - PF_14
    
    ROW
    pin 5 - PE_13
    pin 6 - PF_15
    pin 7 - PD_8
    pin 8 - PD_9

*/
#define PAUSE_FOR 25 //*10 ms
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

/* returns the key based on the input 
input:
        row - row on keypad
        col - col on keypad
output:
        character pressed
*/
char get_char_keypad(char row, char col);

/* turn on the specific row based on input
input:
        row - current row
*/
void set_row_keypad(char *row);

/* delay keypad until pause is 0 - sets the flag
input:
        pause - int that decrements
        flag - allows button to be pressed when sets
*/
void delay_keypad(char *pause, char *flag);

/* sets the key pressed
input: 
        c - valid key on board
*/
void set_key(char c);

/* get the key that was pressed 
output:
        key - key stored in key
*/
char *get_key();