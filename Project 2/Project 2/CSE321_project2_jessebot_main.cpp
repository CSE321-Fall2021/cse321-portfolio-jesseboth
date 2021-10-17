/**
 * Author: Jesse Both
 * Date: 10/10/2021
 * 
 * Assignment: Project 2 Timer System
 * 
 * Purpose:   Count down alarm system utilizing
 *            bare metal methodology.
 * 
 * Inputs:  4x4 keypad
 *              * A - start timer
 *              * B - stop timer
 *              * C - reverse count
 *              * D - trigger input time
 *              * 0 - 9 - Digits for time
 * 
 * Outputs: LED
 *              * -
 *          LCD (model 1802)
 *              * "Time Remaining: m:ss"
 *              * "Times Up"
 *              * Prompt to enter time
 * 
 * Constraints: 
 *              Bare-Metal
 *              Time entered format: m:ss (max time 9:59)
 *              A - start timer
 *              B - stop/turn off
 *              D - trigger input time
 *              User is prompted to enter time
 *              When a value is pressed an led lights up
 *              LCD displays "Time Remaining: m:ss"
 *              When timer hits 0 LCD displays "Times Up", LEDs turn on
 *              Must run forever
 *              
 * Subroutines: Main
 * 
 * Sources: RMO432
 *          Ticker (https://os.mbed.com/docs/mbed-os/v6.15/apis/ticker.html)
 * 
*/

#include "mbed.h"
#include "1802.h"
#include "CSE321_project2_jessebot_timer.h"
#include "CSE321_project2_jessebot_keypad.h"
#include "CSE321_project2_jessebot_gpio.h"

#define LCD_COLS 16
#define LCD_ROWS 2

Ticker TIME;
CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8);

InterruptIn Column0(PF_14);
InterruptIn Column1(PE_11);
InterruptIn Column2(PE_9);
InterruptIn Column3(PF_13);

char timer_flag;
char press_flag = 0;    // allows key press to function when set
char press_pause = 0;   // delays keypress
char row = 0;           // row selection set
char timer_cursor = 6;
char digit_num = 0;
char pressed = 0;
char new_state = 1;
char state = 0;
int inc_by = -1;       // default to decrease
/*   state:
        0 - do nothing wait for 'D'
        1 - input digits m:ss
        2 - wait for 'A' and 'C'
        3 - count down - check for 'B'
*/

void timer_isr(){
    timer_flag = 1;
    inc_timer();
    if(goal_timer()){
        set_inc_by_timer(0);
    }
}
void column0_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 0);

        if(state == 1 && c != '*' && (digit_num != 1 || (digit_num == 1 && c < '6'))){
                set_press_timer(c);
                set_key(c);
            
        }
    }
}
void column1_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 1);

        if(state == 1 && (digit_num != 1 || (digit_num == 1 && c < '6'))){
            set_press_timer(c);
            set_key(c);
        }
    }
}
void column2_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 2);
    
        if(state == 1 && c != '#' && (digit_num != 1 || (digit_num == 1 && c < '6'))){
            set_press_timer(c);
            set_key(c);
        }
    }
}
void column3_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 3);

        if(state == 0 && c == 'D'){
            state = 1;
            new_state = 1;
            timer_cursor = 6;
            pressed = 0;
        }
        else if(state == 2){
            if(c == 'C'){}          //TODO
            else if(c == 'A'){
                set_inc_by_timer(inc_by); 
                state = 3;
            }
        }
        else if(state == 3 && c == 'B'){
            set_inc_by_timer(0);
            state = 2;
        }
    }
}

int main()
{
    TIME.attach(&timer_isr, 1s);
    Column0.rise(&column0_isr);
    Column1.rise(&column1_isr);
    Column2.rise(&column2_isr);
    Column3.rise(&column3_isr);

    LCD.begin();
    set_timer(0, 30);

    /* enable ports (DEF) */
    gpio_enable((char*)"DEF");

    /* set MODER */
    gpio_moder(GPIOE, 13, GPIO_OUTPUT);     // set PE_13 to output
    gpio_moder(GPIOF, 15, GPIO_OUTPUT);     // set PF_15 to output
    gpio_moder(GPIOD, 8,  GPIO_OUTPUT);     // set PD_8 to output
    gpio_moder(GPIOD, 9,  GPIO_OUTPUT);     // set PD_9 to output

    while (true) {

        if(state == 1){
            if (new_state){   
                LCD.clear();
                LCD.setCursor(2, 0);
                LCD.print("Enter a time:");
                LCD.setCursor(6, 1);

                LCD.print("m:ss");
                new_state = 0;
            }
            else if(get_key()[0] != 0 && digit_num < 3){
                LCD.setCursor(timer_cursor, 1);
                LCD.print(get_key());

                if(timer_cursor == 6)   {timer_cursor+=2;}
                else if(timer_cursor<9) {timer_cursor++; }

                digit_num++;
                set_key(0);
            }
            if(digit_num == 3){
                decode_timer();
                new_state = 1;
                state = 2;
            }
        }
        else if(state == 2){
            if (new_state){
                LCD.setCursor(0, 0);
                LCD.print("Press 'A' or 'C'");
                new_state = 0;
            }
        }
        else if(state == 3){
            if(timer_flag){            
                LCD.clear();

                LCD.setCursor(0, 0);
                LCD.print("Time Remaining:");
                LCD.setCursor(6, 1);
                LCD.print(string_timer());
                timer_flag = 0;

                if(goal_timer()){
                    LCD.clear();
                    LCD.setCursor(4, 0);
                    LCD.print("Times Up");
                }
            }
        }
        else{
            if(new_state){            
                LCD.clear();
                LCD.setCursor(2, 0);
                LCD.print("Press 'D' to");
                LCD.setCursor(2, 1);
                LCD.print("enter a time");
            }
        }

        set_row_keypad(&++row); // (also sleeps for 10ms)
        delay_keypad(&press_pause, &press_flag);
    }
}



