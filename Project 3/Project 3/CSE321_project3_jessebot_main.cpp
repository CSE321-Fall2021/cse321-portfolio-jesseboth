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
 * TODO: LCD updates running on seperate threads overlap -> add to event queue?
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
#define MAX_SEN 4
#define BUTTON_DELAY 5
#define SOUND_MULT .5


/*
PD_5: CLk
PD_6: DT
PD_7: SW
*/
#define ROTARY_CLK GPIOD, 5
#define ROTARY_DT GPIOD, 6
#define ROTARY_SW PD_7

#define SOUND_1 GPIOE, 3
#define SOUND_2 GPIOF, 8
#define SOUND_3 GPIOF, 7
#define SOUND_4 GPIOF, 9
#define SOUND_5 GPIOG, 1

CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x10DOTS, PB_9, PB_8);
EventQueue EQ(32 * EVENTS_EVENT_SIZE);
Thread THREAD;
Ticker DEBOUNCE;
Ticker NOISE_CHECK;
Ticker NOISE_RESET;
InterruptIn pwr(ROTARY_SW, PullUp);        // pwr button for device
DigitalOut pwr_ind(LED1);               // on/off indicator

char BUTTON_flag = 1;       // flag to debounce user button
char but_delay = 0;
char ON_flag = 1;           // flag determine if the system is reading audio
char ROTARY_flag = 1;       // flag to debounce rotary encoder
int show_lvl = 0;
char SOUND_flag = 0;
int sens = 2;
double mult = 1;

/* #region  TESTING */
int here=0;
/* #endregion */ 



void set_lvl(int l, int row, char *str, int max){
    LCD.setCursor(0, row);
    LCD.print(str);

    LCD.setCursor(string_length(str), row);
    LCD.block(l);

    LCD.clear_until(max - l);
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

void check_sound(){
    int lvl = 0;
    lvl += gpio_check(SOUND_1);
    lvl += gpio_check(SOUND_2);
    lvl += gpio_check(SOUND_3);
    lvl += gpio_check(SOUND_4);
    lvl += gpio_check(SOUND_5);

    if(lvl > show_lvl || SOUND_flag){
        SOUND_flag = 0;
        set_lvl(lvl*mult, 0, (char *)"lvl: ", MAX_LVL);
        show_lvl = lvl;
    }

}

void clear_sound(){
    SOUND_flag = 1;
    show_lvl = 0;
}

int main(){
    char rot_clk, rot_dt, rot_clk_str, rot_dt_str;
    pwr_ind = 1;
    THREAD.start(callback(&EQ, &EventQueue::dispatch_forever));
    pwr.rise(EQ.event(BUTTON_rise_handler));
    DEBOUNCE.attach(EQ.event(BUTTON_debounce), 50ms);
    NOISE_CHECK.attach(EQ.event(check_sound), 10ms);
    NOISE_RESET.attach(EQ.event(clear_sound), 500ms);

    gpio_enable((char *)"BDEF");
    gpio_moder(ROTARY_CLK, GPIO_INPUT);       // rotary CLK
    gpio_moder(ROTARY_DT, GPIO_INPUT);       // rotary DT

    gpio_moder(SOUND_1, GPIO_INPUT);
    gpio_moder(SOUND_2, GPIO_INPUT);
    gpio_moder(SOUND_3, GPIO_INPUT);
    gpio_moder(SOUND_4, GPIO_INPUT);
    gpio_moder(SOUND_5, GPIO_INPUT);

    LCD.begin();
    set_lvl(3, 0, (char *)"lvl: ", MAX_LVL);
    set_lvl(sens, 1, (char *)"Intensity: ", MAX_SEN);

    while (true){
        if(ON_flag){
            if(!LCD.displayCheck()){
                LCD.displayON();
            }
            /* #region ROTARY */
            rot_clk = gpio_check(ROTARY_CLK);
            rot_dt = gpio_check(ROTARY_DT);

            if(ROTARY_flag && !rot_clk){
                rot_clk_str = rot_clk;
                rot_dt_str = rot_dt;
                ROTARY_flag = 0;

                if(rot_clk == rot_dt && sens>0){
                    sens--;
                }
                else if(rot_clk != rot_dt && sens<MAX_SEN){
                    sens++;
                }
                set_lvl(sens, 1, (char *)"Intensity: ", MAX_SEN);
                mult = sens * SOUND_MULT;
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