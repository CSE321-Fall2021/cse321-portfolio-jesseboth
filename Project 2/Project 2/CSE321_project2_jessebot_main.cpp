/**
 * Author: Jesse Both
 * Date: 10/10/2021
 * 
 * Assignment: Project 2 Timer System
 * 
 * Purpose:   Alarm system utilizing bare metal methodology.
 * 
 * Inputs:      4x4 keypad
 *                  * A - start timer
 *                  * B - pause timer/reset timer
 *                  * C - reverse count
 *                  * D - trigger input time
 *                  * 0 - 9 - Digits for time
 * 
 * Outputs:     LED
 *              Blue LED 
 *                  * Key press
 *              Sequential LEDs
 *                  * 2 yellow/2 red
 *                  * Lights up with alarm
 *              LCD (model 1802)
 *                  * "Time Remaining: m:ss"
 *                  * "Times Up"
 *                  * Prompt to enter time
 * 
 * Constraints: 
 *              Bare-Metal
 *              Time entered format: m:ss (max time 9:59)
 *              A - start timer
 *              B - stop/turn off
 *              C - set to increment/decrement
 *              D - trigger input time
 *              User is prompted to enter time
 *              When a value is pressed an led lights up
 *              LCD displays "Time Remaining: m:ss"
 *              When timer hits 0 LCD displays "Times Up", LEDs turn on
 *              Must run forever
 * 
 * External Files:
 *              CSE321_project2_jessebot_timer.h
 *              CSE321_project2_jessebot_keypad.h
 *              CSE321_project2_jessebot_gpio.h
 *              CSE321_project2_jessebot_lib.h
 *              
 * Subroutines: main()    
 *              timer_isr()
 *              column0_isr()
 *              column1_isr()
 *              column2_isr()
 *              column3_isr()
 * 
 * Globals:
 *              CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8)
 *              InterruptIn Column0(PF_14)
 *              InterruptIn Column1(PE_11)
 *              InterruptIn Column2(PE_9)
 *              InterruptIn Column3(PF_13)
 *              timer_flag - flag to update LCD 
 *              press_flag - flag to allow a press
 *              press_pause - int to delapy input
 *              row - current active row 
 *              new_state - flag that indicate state change
 *              inc_by - increment or decrement
 *              blinky - used for alarm LEDs
 *              c_flag - set when 'C' is pressed
 *              state - current state
 *                  * 0 - do nothing wait for 'D' - 'B' turns off alarm
 *                  * 1 - input digits m:ss, wait for A or C
 *                  * 2 - paused 'A' starts timer, 'B' resets
 *                  * 3 - count down - check for 'B'
 *                  * 4 - make LEDs blink;
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

InterruptIn Column0(PF_14); // correlates to 147* - keypad pin 4
InterruptIn Column1(PE_11); // correlates to 2580 - keypad pin 3
InterruptIn Column2(PE_9);  // correlates to 369# - keypad pin 2
InterruptIn Column3(PF_13); // correlates to ABCD - keypad pin 1

char timer_flag;        // timer flag to set LCD
char press_flag = 0;    // allows key press to function when set
char press_pause = 0;   // delays keypress
char row = 0;           // row selection set
char new_state = 1;     // Used when a new state is triggered
int inc_by = -1;        // default to decrease
int blinky = 0;         // value to light up sequential LEDs
char c_flag = 0;        // flag for C pressed
char state = 0;         // current state
/*   state:
        0 - do nothing wait for 'D' - 'B' turns off alarm
        1 - input digits m:ss, wait for A or C
        2 - paused 'A' starts timer, 'B' resets
        3 - count down - check for 'B'
        4 - make LEDs blink;
*/
/* isr to set the timer or turn timer off */
void timer_isr(){
    timer_flag = 1;
    inc_timer();
    if(goal_timer()){
        set_inc_by_timer(0);
    }
}
/* isr for column 0 (147*) */
void column0_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 0);

        if(state == 1 && c != '*'){
                set_press_timer(c);
                set_key(c);
        }
    }
}
/* isr for column 1 (2580) */
void column1_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 1);

        if(state == 1){
            set_press_timer(c);
            set_key(c);
        }
    }
}
/* isr for column 2 (369#) */
void column2_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 2);
    
        if(state == 1 && c != '#'){
            set_press_timer(c);
            set_key(c);
        }
    }
}
/* isr for column 2 (ABCD) */
void column3_isr(){
    if(press_flag){
        press_pause = PAUSE_FOR;
        press_flag = 0;
        char c = get_char_keypad(row, 3);

        if(state == 0){
            if(c == 'D'){
                blinky = 0;
                state = 1;
                new_state = 1;
            }
            else if(c == 'B'){
                new_state = 1;
                blinky = 0;
            }
        }
        else if(state == 1 || state == 2){

            /* check if 'C' was pressed */
            if(c == 'C' && state == 1){
                c_flag = 1;
                inc_by *= -1;
            }  
            /* check if 'B' was pressed */
            if(c == 'B' && state == 2){
                new_state = 1;
                reset_timer();
                inc_by = -1;
                state = 0;
            }
            /* check if 'A' was pressed */
            else if(c == 'A'){
                set_inc_by_timer(inc_by); 
                if(state == 1){
                    new_state = 1;
                }
                state = 3;
            }
        }
        /* check if 'B' was pressed */
        else if(state == 3 && c == 'B'){
            set_inc_by_timer(0);
            state = 2;
            new_state = 1;
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
    set_timer(10, 30);

    /* enable ports (ADEF) */
    gpio_enable((char*)"ABDEF");

    /* set MODER */
    /* KeyPad output */
    gpio_moder(GPIOE, 13, GPIO_OUTPUT);     // set PE_13 for row 4
    gpio_moder(GPIOF, 15, GPIO_OUTPUT);     // set PF_15 for row 3
    gpio_moder(GPIOD, 8,  GPIO_OUTPUT);     // set PD_8  for row 2
    gpio_moder(GPIOD, 9,  GPIO_OUTPUT);     // set PD_9  for row 1

    /* LEDs */
    gpio_moder(GPIOA, 5,  GPIO_OUTPUT);     // set PA_5  for blue LED
    gpio_moder(GPIOB, 11, GPIO_OUTPUT);     // set PB_11 for sequential (0)
    gpio_moder(GPIOB, 10, GPIO_OUTPUT);     // set PB_10 for sequential (1)
    gpio_moder(GPIOE, 15, GPIO_OUTPUT);     // set PE_15 for sequential (2)
    gpio_moder(GPIOE, 14, GPIO_OUTPUT);     // set PE_14 for sequential (3)

    while (true) {

        /* Input State */
        if(state == 1){
            /* initialize enter time state*/
            if (new_state){  
                gpio_sequential_off();
                LCD.clear();
                LCD.setCursor(2, 0);
                LCD.print("Enter a time:");
                LCD.setCursor(TIMER_LOC, 1);

                LCD.print("m:ss");
                new_state = 0;
            }
            /* check what key was pressed */
            else if(get_key()[0] != 0){
                LCD.setCursor(TIMER_LOC, 1);
                LCD.print(output_press_timer());

                set_key(0);
            }
            /* indicate which direction the timer is counting*/
            if(c_flag){
                LCD.setCursor(15, 1);
                if(inc_by == 1){
                    LCD.print("^");     // up
                }
                else{
                    LCD.print("v");     // down
                }
                c_flag = 0;
            }
        }
        /* Pause State */
        else if(state == 2){
            /* intialize paused state */
            if (new_state){
                LCD.clear();
                LCD.setCursor(0, 0);
                LCD.print("Paused:");

                LCD.setCursor(TIMER_LOC, 1);
                LCD.print(string_timer());      // output time

                new_state = 0;
            }
        }
        /* Count State */
        else if(state == 3){
            /* intialize counting state */
            if(new_state){
                int_timer();

                if(inc_by == 1){
                    swap_timer();               // swap goal and current timer
                }
                new_state = 0;
            }
            /* Do operation every second */
            if(timer_flag){  
                LCD.clear();
                LCD.setCursor(0, 0);          
                if(inc_by == 1){
                    LCD.print("Time Passed:");
                }
                else{
                    LCD.print("Time Remaining:");
                }

                LCD.setCursor(TIMER_LOC, 1);
                LCD.print(string_timer());
                timer_flag = 0;

                /* go to next state if at goal */
                if(goal_timer()){
                    state = 4;
                    new_state = 1;
                    reset_timer();
                }
            }
        }
        /* Times Up */
        else if(state == 4){
            /* intialize state for Times up */
            if(new_state){
                LCD.clear();
                if(inc_by == 1){
                    LCD.setCursor(2, 0);
                    LCD.print("Time Reached");
                    inc_by = -1;                // set to default
                }
                else{
                    LCD.setCursor(4, 0);
                    LCD.print("Times Up");
                }
                new_state = 0;    
            }
            blinky++;
            state = 0;
        }
        /* Default State */
        else{
            /* initialize defualt state */
            if(new_state){   
                gpio_sequential_off();       
                LCD.clear();
                LCD.setCursor(2, 0);
                LCD.print("Press 'D' to");
                LCD.setCursor(2, 1);
                LCD.print("enter a time");
                new_state = 0;
            }

            /* make LEDs Blink */
            if(blinky != 0){    
                if(++blinky > TIME_DELAY){
                    blinky = 1;
                    LCD.setCursor(1, 1);
                    LCD.print("New Timer: 'D'");
                }
                gpio_sequential(blinky);
            }
        }

        set_row_keypad(&++row);                     // set next row                     
        delay_keypad(&press_pause, &press_flag);    // activates/deactivates blue LED
        thread_sleep_for(10);                       // sleep for 10ms
    }
}



