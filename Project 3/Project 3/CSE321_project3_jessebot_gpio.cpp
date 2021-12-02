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

/* turn gpio pin off
input: 
        GPIO - GPIO port
        pin - pin 0-15
output:
        gpio deactivate
*/
void gpio_off(GPIO_TypeDef *GPIO, int pin){
    GPIO->ODR &= ~(1<<pin);
}

/* turn on gpio pin
input:
        GPIO - GPIO port
        pin - pin 0-15
output:
        gpio activate
*/
void gpio_on(GPIO_TypeDef *GPIO, int pin){
    GPIO->ODR |= (1<<pin);
}

/* toggle gpio pin
input:
        GPIO - GPIO port
        pin - pin 0-15
output:
        gpio on/off
*/
void gpio_toggle(GPIO_TypeDef *GPIO, int pin){
    GPIO->ODR ^= (1<<pin);
}

/* check gpio pin input
input:
        GPIO - GPIO port
        pin - pin 0-15
output:
        true/false
*/
int gpio_check(GPIO_TypeDef *GPIO, int pin){
   return (GPIO->IDR & (1<<pin))>>pin;
}

/* enable ports based on string of chars 
input:
        ports - string of chars ('AB' enables ports A and B)
*/
void gpio_enable(char *ports){
    int length = string_length(ports);
    for(int i = 0; i < length; i++){
        RCC->AHB2ENR |= (1<<(ports[i]-'A'));    // enable each port within 'ports'
    }
}

/* set the moder (set values define in header)
input:
        GPIO - GPIO port
        pin - pin 0-15
        set - mode
*/
void gpio_moder(GPIO_TypeDef *GPIO, char pin, char set){
    GPIO->MODER &= ~((set^0x3)<<(pin*2));   // set 0 bits
    GPIO->MODER |= (set<<(pin*2));          // set 1 bits
}