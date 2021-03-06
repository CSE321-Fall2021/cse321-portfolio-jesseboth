-------------------
About
-------------------

Project Description: 
* This device is an alternative hearing device that can 
help the hearing impaired be more are of their environmental
surroundings. 

Contributor List: Jesse Both


--------------------
Features
--------------------
* The system converts sound into a physical and visual representation by vibrating with a vibration motor and displaying the sound level on an LCD.  A rotary encoder is used to adjust the intensity rating of the vibration and the level displayed on the LCD and .

--------------------
Required Materials
--------------------
- 16x2 LCD
- Vibration Motor [x2]
- Rotary Encoder
- Audio Transducer [x5]
- 1K Resistor

--------------------
Resources and References
--------------------
* [STM32 Nucleo-144 boards](https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf)
* [RM0432](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
* [EventQueue](https://os.mbed.com/docs/mbed-os/v6.15/apis/eventqueue.html)
* [Watchdog](https://os.mbed.com/docs/mbed-os/v6.15/apis/watchdog.html)
* [AnalogOut](https://os.mbed.com/docs/mbed-os/v6.15/apis/analogout.html)
* [Rotary Encoder](https://www.rcscomponents.kiev.ua/datasheets/ky-040-datasheet.pdf)

--------------------
Getting Started
--------------------
1. Build the Circuit
![Schematic](graphics/schematic.png)
1. Set the potentiometers on the corresponding audio transducers.
    There settings can be seen in the schematic.
1. Build a new project in Mbed Studio
1. Select the Nucleo L4R5ZI as the target
1. Move files into Program
1. Build the program.

<br/>

--------------------
User Instructions
--------------------
1. Speak/make noise into the audio transducer.
1. Vibration motors will vibrate and LCD will display sound level.
1. To increase the intensity rating, twist the rotary encoder right or left for up or down.
1. Press the rotary encoder switch to turn the system 'off' and 'on'.


<br/>

--------------------
CSE321_project3_jessebot_main.cpp:
--------------------
 

----------
Things Declared
----------

```
#define LCD_COLS 16
#define LCD_ROWS 2
```
* Width and height of the LCD
```
#define MAX_LVL 10
```
* Maximum sound level that can be displayed

```
#define MAX_SEN 4
```
* Maximum intensity level

```
#define BUTTON_DELAY 5
```
* Value*50ms to debounce the button.
```
#define SOUND_MULT .5
```
* Multiplier increment.

```
#define POWER_INDICATOR LED1
```
* Pin name for onboard LED.

```
#define ROTARY_CLK GPIOD, 5 
#define ROTARY_DT GPIOD, 6  
#define ROTARY_SW PD_7      
```
* Pin names for rotary encoder.

```
#define SOUND_1 GPIOE, 3    
#define SOUND_2 GPIOF, 8    
#define SOUND_3 GPIOF, 7    
#define SOUND_4 GPIOF, 9    
#define SOUND_5 GPIOG, 1
```
* Pin names for sound transducers - helps code readability. 

```
#define VIBRATE_1 PA_4      
#define VIBRATE_2 PA_5      
#define VIB_OFFSET 0x3000   
#define VIB_MULT 0x14CC     // (0xFFFF - VIB_OFFSET)/MAX_LVL
```
* Values pertaining to the vibration motors.

```
#define TIMEOUT_MS 5000     
#define feed kick           
```
* Watch dog values.

```
CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x10DOTS, PB_9, PB_8)
```
* Initialize LCD
```
EventQueue EQ(32 * EVENTS_EVENT_SIZE)
```
* Queue that is used for critical section protection and interrupts. 

```
Thread THREAD                          
Thread ROTARY                          
```
* Threads used for EventQueue and rotary encoder polling.

```
Ticker DEBOUNCE
Ticker NOISE_CHECK                    
Ticker NOISE_RESET                    
```
* Tickers to periodically perform specific actions.

```
InterruptIn pwr(ROTARY_SW)
```
* Interrupt for switch

```
DigitalOut pwr_ind(POWER_INDICATOR);    
```
* Power indicator LED manipulation

```
AnalogOut vib1(VIBRATE_1);              
AnalogOut vib2(VIBRATE_2);              
```
* Vibration motors need analog functionality to support variable vibration levels.


```
ON_flag
MUTE_flag       
BUTTON_flag       
ROTARY_flag       
SOUND_flag  
```      
* Flags for synchronization

```
but_delay    
```
* Delay set to debounce switch 

```
show_lvl
```
* lvl that is displayed on LCD.

```
sens
```
* Intensity level - default 2

```
mult
```
* Multiplier relative to sens - default 1.0

----------
API and Built In Elements Used
----------
* mbed.h
    * Watchdog
    * EventQueue
    * Ticker
    * InterruptIn
    * DigitalOut
    * AnalogOut

----------
Custom Functions
----------
```
set_lvl(int l, int row, char *str, int max)
```
* Sets the lvl bar and intensity bar.

```
BUTTON_debounce()
```
* Periodically called to debounce the button.
```
BUTTON_rise_handler()
```
* Turns on or off the system.
```
check_sound()
```
* Periodically check if the sound transducers are sensing sound.
```
clear_sound()
```
* Resets the sound value to resample.
```
rotary_polling()
```
* Runs on a separate thread to poll for rotary encoder input.
```
main()
```
* Main function that initializes everything, loops to check ON_flag.


--------------------
CSE321_project2_jessebot_gpio.cpp:
--------------------
This file controls bitwise GPIO manipulation.


----------
Things Declared
----------

```
#define GPIO_INPUT      0x0
#define GPIO_OUTPUT     0x1
#define GPIO_ALTERNATE  0x2
#define GPIO_ANALOG     0x3
```

----------
API and Built In Elements Used
----------
* mbed.h

----------
Custom Functions
----------

```
gpio_on(GPIO_TypeDef *GPIO, int pin)
```
* Turns gpio pin on based on the input. Manipulates ODR.
```
gpio_off(GPIO_TypeDef *GPIO, int pin)
```
* Turns gpio pin off based on the input. Manipulates ODR.
```
gpio_toggle(GPIO_TypeDef *GPIO, int pin)
```
* Turns gpio pin on/off based on the input and current state. Manipulates ODR.

```
gpio_check(GPIO_TypeDef *GPIO, int pin)
```
* Checks whether or not the IDR is high or not - returns 1 is yes, 0 if no.

```
gpio_enable(char *ports)
```
* Enables ports based on string input.  'AB' enables ports A and B.

```
gpio_moder(GPIO_TypeDef *GPIO, char pin, char set)
```
* Enables MODER based on the input.

 <br/>


--------------------
CSE321_project2_jessebot_lib.cpp:
--------------------

----------
Things Declared
----------

N/A

----------
API and Built In Elements Used
----------
* mbed.h

----------
Custom Functions
----------
```
string_to_int(char *str)
```
Converts a string to an integer.
```
string_length(char *str)
```
Gets the string length.
```
string_to_int_wlen(char *str, int len)
```
Converts a string to an integer with a known length.


--------------------
edited_1802.cpp:
--------------------

* Modified original 1802.h/cpp

----------
Things Declared
----------

N/A

----------
API and Built In Elements Used
----------
* mbed.h

----------
Custom Functions
----------
```
int block(char i)
```
* Function to place full blocks (0xFF) in each position relative to i.
```
int clear_until(char i);
```
* Starts at current cursor and clears (places space) at each position relative to i
```
void displayOFF()
```
* turns the display off
```
int displayCheck()
```
* Checks if display is on or off.