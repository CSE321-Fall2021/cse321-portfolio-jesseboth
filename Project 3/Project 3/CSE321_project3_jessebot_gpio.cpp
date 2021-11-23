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
 *              gpio_enable(char *ports)
 *              gpio_moder(GPIO_TypeDef *GPIO, char pin, char set)
 *              gpio_sequential(int blink)
 *              gpio_sequential_off()
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

/* make LEDs bink sequentially 
input: 
        blink - value that indicates which led to light up
output:
        LEDs
*/
void gpio_sequential(int blink){
    char mod = blink%100;

    if(mod == 85){
        gpio_on(GPIOE, 15);
        gpio_off(GPIOE, 14);
    }
    else if(mod == 68){
        gpio_on(GPIOE, 14);
        gpio_off(GPIOE, 15);
    }
    else if(mod == 51){
        gpio_on(GPIOE, 15);
        gpio_off(GPIOB, 10);
    }
    else if(mod == 34){
        gpio_on(GPIOB, 10);
        gpio_off(GPIOB, 11);
    }
    else if(mod == 17){
        gpio_on(GPIOB, 11);
        gpio_off(GPIOB, 10);
    }
    else if(mod == 0){
        gpio_on(GPIOB, 10);
        gpio_off(GPIOE, 15);
    }
}

/* turns off all sequential related LEDs*/
void gpio_sequential_off(){
    gpio_off(GPIOB, 11);
    gpio_off(GPIOB, 10);
    gpio_off(GPIOE, 15);
    gpio_off(GPIOE, 14);
}
