/**
 * Author: Jesse Both
 * 
 * Assignment:  Project 2 Timer System
 * 
 * Purpose:     Library to deal with GPIO manipulation.
 * 
 * Constraints: 
 *              see main
 * 
 * Subroutines: 
 *              gpio_off(GPIO_TypeDef *GPIO, int pin)
 *              gpio_on(GPIO_TypeDef *GPIO, int pin)
 *              gpio_toggle(GPIO_TypeDef *GPIO, int pin)
 *              gpio_check(GPIO_TypeDef *GPIO, int pin)
 *              gpio_enable(char *ports)
 *              gpio_moder(GPIO_TypeDef *GPIO, char pin, char set)
 * 
 * Global Vars: N/A
 *              
 * 
 * Sources: Source Code (GPIO_TypeDef)
 *        
 * 
*/
#include "CSE321_project3_jessebot_gpio.h"

/** turn gpio pin off
input: 
        @param GPIO GPIO port     
        @param pin pin within GPIO port
output:
        @result gpio deactivate
*/
void gpio_off(GPIO_TypeDef *GPIO, int pin){
    GPIO->ODR &= ~(1<<pin);
}

/** turn on gpio pin
input:
        @param GPIO GPIO port     
        @param pin pin within GPIO port
output:
        @result gpio activate
*/
void gpio_on(GPIO_TypeDef *GPIO, int pin){
    GPIO->ODR |= (1<<pin);
}

/** toggle gpio pin
input:
        @param GPIO GPIO port     
        @param pin pin within GPIO port
output:
        @result gpio on/off
*/
void gpio_toggle(GPIO_TypeDef *GPIO, int pin){
    GPIO->ODR ^= (1<<pin);
}

/** check gpio pin input
input:
        @param GPIO GPIO port     
        @param pin pin within GPIO port
output:
        @return true/false
*/
int gpio_check(GPIO_TypeDef *GPIO, int pin){
   return (GPIO->IDR & (1<<pin))>>pin;
}

/** enable ports based on string of chars 
input:
        @param ports string of chars ('AB' enables ports A and B)
output:
        @result enables all ports from ports string
*/
void gpio_enable(char *ports){
    int length = string_length(ports);
    for(int i = 0; i < length; i++){
        RCC->AHB2ENR |= (1<<(ports[i]-'A'));    // enable each port within 'ports'
    }
}

/** set the moder (set values define in header)
input:
        @param GPIO GPIO port     
        @param pin pin within GPIO port
        @param set mode
                @see GPIO_INPUT
                @see GPIO_OUTPUT
                @see GPIO_ALTERNATE
                @see GPIO_ANALOG

output:
        @result sets pin to correct mode relateive to set
*/
void gpio_moder(GPIO_TypeDef *GPIO, char pin, char set){
    GPIO->MODER &= ~((set^0x3)<<(pin*2));   // set 0 bits
    GPIO->MODER |= (set<<(pin*2));          // set 1 bits
}