/**
 * Author: Jesse Both
 * Date: 9/23/2021
 * 
 * Assignment:...
 * 
 * Purpose:   Activates PA_1 to turn on an LED
 *            with the push of a button in PB_1
 * 
 * Inputs:  Button - PB_1
 * Outputs: LED - PA_1
 * 
 * Constraints:
 * 
 * Subroutines:
 * 
 * Sources:
 * 
*/

#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    RCC->AHB2ENR |= 0x3;        //enable port A and B

    /*output*/
    GPIOA->MODER &= ~(0x8);     //set bit 1 to 0 PA1[1]
    GPIOA->MODER |= 0x4;        //set bit 2 to 1 PA1[0]

    /*input*/
    GPIOB->MODER &= ~(0xC);     //set bit 2 and 3 to 0 PB1[1:0]

    while (true) {

        /*check if button is pressed*/
        if((GPIOB->IDR & 0x2) != 0x2){
            GPIOA->ODR |= 0x2;      //activate LED         
        }
        else{
            GPIOA->ODR &= ~(0x2);   //deactivate LED
        }

        thread_sleep_for(500);
    }
}

