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
#include "keypad.h"

#define LCD_COLS 16
#define LCD_ROWS 2

Ticker TIME;
CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8);

InterruptIn Column0(PF_14);
InterruptIn Column1(PE_11);
InterruptIn Column2(PE_9);
InterruptIn Column3(PF_13);

char timer_flag;
char row = 0;

void timer_isr(){
    timer_flag = 1;
    inc_timer(1);
}
void column0_isr(){
    printf("0, %d\n", row);
}
void column1_isr(){
    printf("1, %d\n", row);
}
void column2_isr(){
    printf("2, %d\n", row);
}
void column3_isr(){
    printf("3, %d\n", row);
}


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
int main()
{
    TIME.attach(&timer_isr, 1s);
    Column0.rise(&column0_isr);
    Column1.rise(&column1_isr);
    Column2.rise(&column2_isr);
    Column3.rise(&column3_isr);

    LCD.begin();
    set_timer(9, 30);

    /* enable ports (DEF) */
    RCC->AHB2ENR |= 0x38;

    /* set 0's for output */
    GPIOE->MODER &= ~(0x8000000);
    GPIOF->MODER &= ~(0x80000000);
    GPIOD->MODER &= ~(0xA0000);

    /* set 1's for output */
    GPIOE->MODER |= (0x4000000);
    GPIOF->MODER |= (0x40000000);
    GPIOD->MODER |= (0x50000);

    while (true) {
        if(timer_flag){            
            LCD.clear();
            LCD.setCursor(0, 0);
            LCD.print("Hello World");
        
            LCD.setCursor(6, 1);
            LCD.print(string_timer());

            timer_flag = 0;
        }

        // pin 5 - PE_13 -> row 4
        // pin 6 - PF_15 -> row 3
        // pin 7 - PD_8  -> row 2
        // pin 8 - PD_9  -> row 1
        row++;
        if(row == 0){
            GPIOE->ODR &= ~(0x2000);
            GPIOF->ODR &= ~(0x8000);
            GPIOD->ODR &= ~(0x100);
            GPIOD->ODR |= 0x200;
            thread_sleep_for(10);
        }
        else if(row == 1){
            GPIOE->ODR &= ~(0x2000);
            GPIOF->ODR &= ~(0x8000);
            GPIOD->ODR |= 0x100;
            GPIOD->ODR &= ~(0x200);
            thread_sleep_for(10);
        }
        else if(row == 2){
            GPIOE->ODR &= ~(0x2000);
            GPIOF->ODR |= 0x8000;
            GPIOD->ODR &= ~(0x100);
            GPIOD->ODR &= ~(0x200);
            thread_sleep_for(10);
        }
        else {
            GPIOE->ODR |= 0x2000;
            GPIOF->ODR &= ~(0x8000);
            GPIOD->ODR &= ~(0x100);
            GPIOD->ODR &= ~(0x200);
            thread_sleep_for(10);
            row=-1;
        }
    }
}

