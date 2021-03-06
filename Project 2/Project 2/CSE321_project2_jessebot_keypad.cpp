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
#include "CSE321_project2_jessebot_keypad.h"

char keys[4][4] = { {'1', '2', '3', 'A'},
                    {'4', '5', '6', 'B'},
                    {'7', '8', '9', 'C'},
                    {'*', '0', '#', 'D'} };
char key[2];

/* returns the key based on the input 
input:
        row - row on keypad
        col - col on keypad
output:
        character pressed
*/
char get_char_keypad(char row, char col){
    return keys[row][col];                  // return corresponding character
}

/* turn on the specific row based on input
input:
        row - current row
*/
void set_row_keypad(char *row){
    // pin 5 - PE_13 -> row 4
    // pin 6 - PF_15 -> row 3
    // pin 7 - PD_8  -> row 2
    // pin 8 - PD_9  -> row 1
    if(*row == KEYPAD_ROWS){
        *row = 0;
    }

    if(*row == 0){
        gpio_off(GPIOE, 13);
        gpio_off(GPIOF, 15);
        gpio_off(GPIOD, 8);
        gpio_on(GPIOD, 9);
    }
    else if(*row == 1){
        gpio_off(GPIOE, 13);
        gpio_off(GPIOF, 15);
        gpio_on(GPIOD, 8);
        gpio_off(GPIOD, 9);
    }
    else if(*row == 2){
        gpio_off(GPIOE, 13);
        gpio_on(GPIOF, 15);
        gpio_off(GPIOD, 8);
        gpio_off(GPIOD, 9);
    }
    else {
        gpio_on(GPIOE, 13);
        gpio_off(GPIOF, 15);
        gpio_off(GPIOD, 8);
        gpio_off(GPIOD, 9);
    }
}

/* delay keypad until pause is 0 - sets the flag
input:
        pause - int that decrements
        flag - allows button to be pressed when sets
*/
void delay_keypad(char *pause, char *flag){
    if(*pause>0){
        gpio_on(GPIOA, 5);      // activate indicator LED
        (*pause)--;
    }
    else{
        *flag = 1;
        gpio_off(GPIOA, 5);     // deactivate indicator LED
    }
}

/* sets the key pressed
input: 
        c - valid key on board
*/
void set_key(char c){
    key[0] = c;
}

/* get the key that was pressed 
output:
        key - key stored in key
*/
char *get_key(){
    return key;
}