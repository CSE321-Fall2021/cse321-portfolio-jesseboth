/**
 * Author: Jesse Both
 * Date: 10/06/2021
 * 
 * Assignment: Project 2 Preperation
 * 
 * Purpose:   Output name via serial communication
 *            Make external LED blink periodically
 * 
 * Inputs:  
 * Outputs: LED - PA_1
 * 
 * Constraints: Bare-Metal
 * 
 * Subroutines: Main
 * 
 * Sources: RMO432
 * 
*/

#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    RCC->AHB2ENR |= 0x1;        //enable port A

    /*output*/
    GPIOA->MODER &= ~(0x8);     //set bit 1 to 0 PA1[1]
    GPIOA->MODER |= 0x4;        //set bit 2 to 1 PA1[0]

    while (true) {
        printf("Jesse Both\n");

        GPIOA->ODR |= 0x2;      //activate LED  
        thread_sleep_for(2000); // leave on for 2s

        GPIOA->ODR &= ~(0x2);   //deactivate LED
        thread_sleep_for(2000); // leave off for 2s
    }
}