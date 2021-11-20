/**
 * Author: Jesse Both
 * Date: 11/19/2021
 * 
 * Assignment:  Project 3
 *              Alternative Hearing Device
 * 
 * Purpose:     To provide an alternative form of hearing
 *              for the hearing impaired.
 * 
 * Inputs: 
 *          - Audio Transducer
 *          - Rotary Encoder
 *          - Onboard Button
 * Outputs: 
 *          - LEDs
 *          - Vibration Motor
 * 
 * Constraints:
 *          - Detect sound and will stimulate an alternative sense rather than sound.
 *          - Provide a visual and physical que that noise is nearby.
 *          -  Desired sound sensitivity can be adjusted.
 *          - Toggle on and off the device.
 * 
 * Subroutines:
 *              main()
 * 
 * Sources:
 * 
*/
#include "mbed.h"
#include "1802.h"
#include "CSE321_project3_jessebot_gpio.h"

#define LCD_COLS 16
#define LCD_ROWS 2


CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x10DOTS, PB_9, PB_8);

int main()
{
    LCD.begin();
    thread_sleep_for(2000);

    
    gpio_enable((char *)"B");
    gpio_moder(GPIOB, 11, GPIO_OUTPUT);
    while (true) {
        
        gpio_toggle(GPIOB, 11);

        LCD.setCursor(0, 0);
        char hello[12] = "Hello World";
        LCD.print(hello);

        LCD.setCursor(0, 1);
        LCD.block(3);

        thread_sleep_for(2000);
        LCD.clear();
    }
}