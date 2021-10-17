#include "CSE321_project2_jessebot_keypad.h"

char keys[4][4] = { {'1', '2', '3', 'A'},
                    {'4', '5', '6', 'B'},
                    {'7', '8', '9', 'C'},
                    {'*', '0', '#', 'D'} };
char key[2];
char get_char_keypad(char row, char col){
    printf("%c\n", keys[row][col]);
    return keys[row][col];    
}

void set_row_keypad(char *row){
    // pin 5 - PE_13 -> row 4
    // pin 6 - PF_15 -> row 3
    // pin 7 - PD_8  -> row 2
    // pin 8 - PD_9  -> row 1

    if(*row == 0){
        gpio_off(GPIOE, 13);
        gpio_off(GPIOF, 15);
        gpio_off(GPIOD, 8);
        gpio_on(GPIOD, 9);
        thread_sleep_for(10);
    }
    else if(*row == 1){
        gpio_off(GPIOE, 13);
        gpio_off(GPIOF, 15);
        gpio_on(GPIOD, 8);
        gpio_off(GPIOD, 9);
        thread_sleep_for(10);
    }
    else if(*row == 2){
        gpio_off(GPIOE, 13);
        gpio_on(GPIOF, 15);
        gpio_off(GPIOD, 8);
        gpio_off(GPIOD, 9);
        thread_sleep_for(10);
    }
    else {
        gpio_on(GPIOE, 13);
        gpio_off(GPIOF, 15);
        gpio_off(GPIOD, 8);
        gpio_off(GPIOD, 9);
        thread_sleep_for(10);
        *row=-1;
    }
}

void delay_keypad(char *pause, char *flag){
    if(*pause>0){
        (*pause)--;
    }
    else{
        *flag = 1;
    }
}

void set_key(char c){
    key[0] = c;
}

char *get_key(){
    return key;
}