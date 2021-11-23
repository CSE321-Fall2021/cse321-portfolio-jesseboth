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
#define BUTTON_DELAY 5

CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x10DOTS, PB_9, PB_8);
EventQueue EQ(32 * EVENTS_EVENT_SIZE);
Thread THREAD;
Ticker TICK;
InterruptIn pwr(PD_5, PullUp);        // pwr button for device
DigitalOut pwr_ind(LED1);               // on/off indicator

char BUTTON_flag = 1;       // flag to debounce user button
char but_delay = 0;
char ON_flag = 1;           // flag determine if the system is reading audio
char ROTARY_flag = 1;       // flag to debounce rotary encoder

int volume = 2;

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

void BUTTON_debounce(){
    if(!BUTTON_flag && !but_delay){
        BUTTON_flag = 1;
    }
    else{
        but_delay--;
    }
}

void BUTTON_rise_handler(){  
    if(BUTTON_flag){
        ON_flag ^= 1;
        pwr_ind = !pwr_ind;
        but_delay = BUTTON_DELAY;
        BUTTON_flag = 0;
    }
}

/*
PD_7: CLk
PD_6: DT
PD_5: SW
*/

int main(){
    char rot_clk, rot_dt, rot_clk_str, rot_dt_str;
    pwr_ind = 1;
    THREAD.start(callback(&EQ, &EventQueue::dispatch_forever));
    pwr.rise(EQ.event(BUTTON_rise_handler));
    TICK.attach(EQ.event(BUTTON_debounce), 50ms);

    gpio_enable((char *)"D");
    gpio_moder(GPIOD, 7, GPIO_INPUT);       // rotary CLK
    gpio_moder(GPIOD, 6, GPIO_INPUT);       // rotary DT


    LCD.begin();
    set_lvl(3, 0, (char *)"lvl:");
    set_lvl(volume, 1, (char *)"vol:");

    while (true){
        if(ON_flag){
            if(!LCD.displayCheck()){
                LCD.displayON();
            }
            /* #region ROTARY */
            rot_clk = gpio_check(GPIOD, 7);
            rot_dt = gpio_check(GPIOD, 6);

            if(ROTARY_flag && !rot_clk){
                rot_clk_str = rot_clk;
                rot_dt_str = rot_dt;
                ROTARY_flag = 0;

                if(rot_clk == rot_dt && volume>0){
                    volume--;
                }
                else if(volume<MAX_LVL){
                    volume++;
                }
                set_lvl(volume, 1, (char *)"vol:");
            }
            else if(!ROTARY_flag && rot_clk && rot_dt){
                ROTARY_flag = 1;
            }
            /* #endregion ROTARY */
        }
        else{
            if(LCD.displayCheck()){
                LCD.displayOFF();
            }
        }
    }
}