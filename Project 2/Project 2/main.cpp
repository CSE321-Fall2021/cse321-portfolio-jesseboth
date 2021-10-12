/**
 * Author: Jesse Both
 * Date: 10/10/2021
 * 
 * Assignment: Project 2 Timer System
 * 
 * Purpose:   Count down alarm system utilizing
 *            bare metal methodology.
 * 
 * Inputs:  3x4 keypad
 *              * A - start timer
 *              * B - stop timer
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
#include "timer.h"

#define LCD_COLS 16
#define LCD_ROWS 2

Ticker TIME;
CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8);
char timer_flag;

void timer_isr(){
    timer_flag = 1;
}

int main()
{
    TIME.attach(&timer_isr, 1s);
    LCD.begin();

    set_timer(9, 30);
    
    while (true) {
        if(timer_flag){            
            LCD.clear();
            LCD.setCursor(0, 0);
            LCD.print("Hello World");
        
            inc_timer(1);
            LCD.setCursor(6, 1);
            LCD.print(string_timer());

            timer_flag = 0;
        }
    }
}

