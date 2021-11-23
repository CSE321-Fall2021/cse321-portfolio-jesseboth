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
#include "mbed.h"
#include "CSE321_project3_jessebot_lib.h"

#define GPIO_INPUT      0x0
#define GPIO_OUTPUT     0x1
#define GPIO_ALTERNATE  0x2
#define GPIO_ANALOG     0x3

/* turn gpio pin off
input: 
        GPIO - GPIO port
        pin - pin 0-15
output:
        gpio deactivate
*/
void gpio_off(GPIO_TypeDef *GPIO, int pin);

/* turn on gpio pin
input:
        GPIO - GPIO port
        pin - pin 0-15
output:
        gpio activate
*/
void gpio_on(GPIO_TypeDef *GPIO, int pin);

/* toggle gpio pin
input:
        GPIO - GPIO port
        pin - pin 0-15
output:
        gpio on/off
*/
void gpio_toggle(GPIO_TypeDef *GPIO, int pin);

/* check gpio pin input
input:
        GPIO - GPIO port
        pin - pin 0-15
output:
        true/false
*/
int gpio_check(GPIO_TypeDef *GPIO, int pin);

/* enable ports based on string of chars 
input:
        ports - string of chars ('AB' enables ports A and B)
*/
void gpio_enable(char *ports);

/* set the moder (set values define in header)
input:
        GPIO - GPIO port
        pin - pin 0-15
        set - mode
*/
void gpio_moder(GPIO_TypeDef *GPIO, char pin, char set);

/* make LEDs bink sequentially 
input: 
        blink - value that indicates which led to light up
output:
        LEDs
*/
void gpio_sequential(int blink);

/* turns off all sequential related LEDs*/
void gpio_sequential_off();