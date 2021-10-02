/**
 * Editor: Jesse Both
 * Date: 10/4/2021
 * 
 * Assignment: Fix the code
 * 
 * Purpose: To develop better coding prractices
 * 
 * Inputs: BUTTON1
 * Outputs: LED2
 * 
 * Constraints:
 * 
 * Subroutines:
 *              polling()
 *              set_flag (interrupt)
 *              toggle_blink (interrupt)
 * Sources:
 * 
*/

#include "mbed.h"

// Create a thread to drive an LED to have an on 
// time of 2000 ms and off time 500 ms
Thread controller;

void polling();          // loops forever

DigitalOut led(LED2);    // establish blue led as an output
InterruptIn button_handler(BUTTON1); 

void set_flag();        // set flag for toggling led
void toggle_blink();    // turns blinking led on or off

int blink = 0;          // When blink == 0, led will blink
int flag = 0;           // When flag == 1, led will toggle

int main() {
    // start the allowed execution of the thread
    printf("----------------START----------------\n");
    printf("Starting state of thread: %d\n", controller.get_state());
    controller.start(polling);
    printf("State of thread right after start: %d\n", controller.get_state());
    button_handler.rise(set_flag);
	button_handler.fall(toggle_blink);

  return 0;
}

// make the handler
void polling() {
    while (true) {
        if(blink == 0){
            led = !led;             // toggle led (on)
            printf("LED on\n");       
            thread_sleep_for(2000); //Thread_sleep is a time delay function, causes a 2000 unit delay

            led = !led;             // toggle led (off)
            printf("LED off\n"); 
            thread_sleep_for(500);  //Thread_sleep is a time delay function, causes a 500 unit delay
        }
    }
}

/* required flag == 1 to toggle blink*/
void set_flag() {
    flag=1;             // togle the state of the thread
}

void toggle_blink() {
    if (flag == 1){
        blink++; 
        blink %= 2;     // toggle blink
        flag=0;         // reset flag
    }
}