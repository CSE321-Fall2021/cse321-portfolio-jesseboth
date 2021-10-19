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
char get_char_keypad(char row, char col);
void set_row_keypad(char *row);
void delay_keypad(char *pause, char *flag);
void set_key(char c);
char *get_key();