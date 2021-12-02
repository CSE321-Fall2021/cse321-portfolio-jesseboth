/**
 * Author: Jesse Both
 * Date: 11/30/2021
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
 * TODO: move to main:
 *          sens   
 *          ROTARY_flag
 * TODO: prevent output when !ON_flag
 */
#include "mbed.h"
#include "PinNames.h"
#include "mbed_events.h"
#include "1802.h"
#include "CSE321_project3_jessebot_gpio.h"

#define LCD_COLS 16
#define LCD_ROWS 2
#define MAX_LVL 10          // 10 bars for lvl
#define MAX_SEN 4           // 4 bars for intensity
#define BUTTON_DELAY 5      // *50ms
#define SOUND_MULT .5       // sound multipler value
#define ROTARY_CLK GPIOD, 5 // Rotary CLK 
#define ROTARY_DT GPIOD, 6  // Rotary DT
#define ROTARY_SW PD_7      // Rotary SW

#define SOUND_1 GPIOE, 3    // pin for 1st sound transducer
#define SOUND_2 GPIOF, 8    // pin for 2nd sound transducer
#define SOUND_3 GPIOF, 7    // pin for 3rd sound transducer
#define SOUND_4 GPIOF, 9    // pin for 4th sound transducer
#define SOUND_5 GPIOG, 1    // pin for 5th sound transducer

#define VIB_OFFSET 0x3000   // lowest value for vibration
#define VIB_MULT 0x14CC     // (0xFFFF - VIB_OFFSET)/MAX_LVL

CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x10DOTS, PB_9, PB_8);
EventQueue EQ(32 * EVENTS_EVENT_SIZE);  // queue for interrupts
Thread THREAD;                          // thread for queue
Ticker DEBOUNCE;                        // ticker to debounce rotary switch
Ticker NOISE_CHECK;                     // ticker to check periodically for sound
Ticker NOISE_RESET;                     // ticker to reset sound values
InterruptIn pwr(ROTARY_SW, PullUp);     // pwr button for device
DigitalOut pwr_ind(LED1);               // on/off indicator
AnalogOut vib1(PA_4);                   // vibration motor 1
AnalogOut vib2(PA_5);                   // vibration motor 2

char BUTTON_flag = 1;       // flag to debounce user button
char but_delay = 0;         // set to BUTTON_DELAY and decremented
char ON_flag = 1;           // flag determine if the system is reading audio
char ROTARY_flag = 1;       // flag to debounce rotary encoder
int show_lvl = 0;           // current lvl, used to reduce lcd set calls 
char SOUND_flag = 0;        // extra flag for the case of lvl & show_lvl == 0
int sens = 2;               // default intensity for vibration motors/lcd
double mult = 1;            // multiplier sens*SOUND_MULT

/* Shows a 'progress' bar in lcd based on inputs
input:
        l - number of blocks to be displayed
        row - row on lcd (0 or 1)
        str - string before bar
        max - max number of blocks possible
output: 
        displayed on LCD
*/
void set_lvl(int l, int row, char *str, int max){
    LCD.setCursor(0, row);
    LCD.print(str);

    LCD.setCursor(string_length(str), row);
    LCD.block(l);

    LCD.clear_until(max - l);
}

/* Periodically called, debounces button*/
void BUTTON_debounce(){
    if(!BUTTON_flag && !but_delay){
        BUTTON_flag = 1;
    }
    else if(but_delay > 0){
        but_delay--;
    }
}

/* "turns off" the system to the user */
void BUTTON_rise_handler(){  
    if(BUTTON_flag){
        ON_flag ^= 1;
        pwr_ind = !pwr_ind;
        but_delay = BUTTON_DELAY;
        BUTTON_flag = 0;
    }
}

/* periodically checks which sound transuducers are currently on */
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

        int sample = VIB_MULT * lvl + (lvl>0)*VIB_OFFSET;
        vib1.write_u16(sample);
        vib2.write_u16(sample); 
        show_lvl = lvl;
    }

}

/* periodically sets sound values to 0 */
void clear_sound(){
    SOUND_flag = 1;
    show_lvl = 0;
}

int main(){    
    /* rotary variables */
    char rot_clk, rot_dt, rot_clk_str, rot_dt_str;

    pwr_ind = 1; // set system to 'on'

    /* start the EventQueue on an another thread */
    THREAD.start(callback(&EQ, &EventQueue::dispatch_forever));
    pwr.rise(EQ.event(BUTTON_rise_handler));            // button rise handler

    DEBOUNCE.attach(EQ.event(BUTTON_debounce), 50ms);   // ticker to debounce
    NOISE_CHECK.attach(EQ.event(check_sound), 10ms);    // ticker to check for sound
    NOISE_RESET.attach(EQ.event(clear_sound), 500ms);   // ticker to reset noise count

    gpio_enable((char *)"BDEF");            // enable ports BDEF
    gpio_moder(ROTARY_CLK, GPIO_INPUT);     // rotary CLK
    gpio_moder(ROTARY_DT, GPIO_INPUT);      // rotary DT

    /* set moder for each sound transducer */
    gpio_moder(SOUND_1, GPIO_INPUT);        
    gpio_moder(SOUND_2, GPIO_INPUT);
    gpio_moder(SOUND_3, GPIO_INPUT);
    gpio_moder(SOUND_4, GPIO_INPUT);
    gpio_moder(SOUND_5, GPIO_INPUT);

    /* initialize LCD */
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

            /* rotation starts when clk is low */
            if(ROTARY_flag && !rot_clk){
                rot_clk_str = rot_clk;
                rot_dt_str = rot_dt;
                ROTARY_flag = 0;

                /** TODO: check */
                /* if clk and dt low -> rotate left */
                if(rot_clk == rot_dt && sens>0){
                    sens--;
                }
                /* if clk low, dt high -> rotate right */
                else if(rot_clk != rot_dt && sens<MAX_SEN){
                    sens++;
                }

                EQ.call(set_lvl, sens, 1,  (char *)"Intensity: ", MAX_SEN);
                mult = sens * SOUND_MULT;       // set multiplier value for lvl*mult
            }
            /* done rotating when clk and dt are low */
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