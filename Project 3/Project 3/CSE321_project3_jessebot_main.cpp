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
 *          EventQueue: https://os.mbed.com/docs/mbed-os/v6.15/apis/eventqueue.html
 *
 */
#include "mbed.h"
#include "PinNames.h"
#include "mbed_events.h"
#include "1802.h"
#include "CSE321_project3_jessebot_gpio.h"

#define LCD_COLS 16
#define LCD_ROWS 2
#define MAX_LVL 10

CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x10DOTS, PB_9, PB_8);
EventQueue EQ(32 * EVENTS_EVENT_SIZE);
Thread THREAD;
InterruptIn pwr(BUTTON1); // pwr button for device
DigitalOut pwr_ind(LED1);      // on/off indicator


char BUTTON_flag = 1;       // flag to debounce user button
char ON_flag = 1;           // flag determine if the system is reading audio

/* #region  TESTING */
int here=0;
/* #endregion */ 



void set_lvl(int l, int row, char *str){
    LCD.setCursor(0, row);
    LCD.print(str);

    LCD.setCursor(5, row);
    LCD.block(l);

    LCD.clear_until(MAX_LVL - l);
}

void BUTTON_rise_handler(){  
    if(BUTTON_flag){
        ON_flag ^= 1;
        pwr_ind = !pwr_ind;
        EQ.call(printf, "HERE %d\n", here++);
        BUTTON_flag = 0;
    }
}

void BUTTON_fall_handler(){
    BUTTON_flag = 1;
}

int main(){
    int x = 0;
    int flag = 0;
    pwr_ind = 1;
    THREAD.start(callback(&EQ, &EventQueue::dispatch_forever));
    pwr.rise(BUTTON_rise_handler);
    pwr.fall(EQ.event(BUTTON_fall_handler));


    LCD.begin();
    set_lvl(5, 1, (char *)"vol:");

    while (true){

        /* #region TESTING */
        if(ON_flag){
            if(!LCD.displayCheck()){
                LCD.displayON();
            }
            set_lvl(x, 0, (char *)"lvl:");
            thread_sleep_for(50);


            if (x == MAX_LVL){
                flag = 1;
            }
            else if (x == 0){
                flag = 0;
            }

            if (flag){
                x--;
            }
            else{
                x++;
            }
        }
        else{
            if(LCD.displayCheck()){
                LCD.displayOFF();
            }
        }

        /* #endregion */
    }
}