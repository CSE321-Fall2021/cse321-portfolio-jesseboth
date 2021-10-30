-------------------
About
-------------------

Project Description: 
* Bare-Metal alarm system. Allows for user input via a keypad and displays the 
time via an LCD. The user will input a time under 10 minutes with the keypad and 
the time will be displayed on the LCD along with various prompts.  
When time is up, a series of LEDs will light up.  

Contribitor List: Jesse Both


--------------------
Features
--------------------

* LCD
    * Displays Prompts and time remaining.

* 4x4 Keypad
    * Allows for inputs in the system.

* LEDs
    * Provides a visual queue to the user that the input was accepted
    * Blinks when time is up.

--------------------
Required Materials
--------------------
- Nucleo L4R5ZI
- LCD
- 4x4 Keypad
- Breadboard
- Wires
- LEDs

--------------------
Resources and References
--------------------
* [STM32 Nucleo-144 boards](https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf)
* [RM0432](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
* [Ticker](https://os.mbed.com/docs/mbed-os/v6.15/apis/ticker.html)

--------------------
Getting Started
--------------------
1. Build the Circuit
<img src="Project 2/CSE321_project2_schematic.svg">
2. Build a new project in Mbed Studio
3. Select the Nucleo L4R5ZI as the target
4. Move files into Program
5. Build the program.
6. Use the keypad for user input.

<br/>

--------------------
CSE321_project2_jessebot_main.cpp:
--------------------
 This is the main file of the program.  This is where the interrupt handlers are located.  The main function handles what state the program is currently in and what to do with each state.

----------
Things Declared
----------


* Ticker TIME
* CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8)
* InterruptIn Column0(PF_14)
* InterruptIn Column1(PE_11)
* InterruptIn Column2(PE_9)
* InterruptIn Column3(PF_13)
* timer_flag - flag to update LCD 
* press_flag - flag to allow a press
* press_pause - int to delapy input
* row - current active row 
* new_state - flag that indicate state change
* inc_by - increment or decrement
* blinky - used for alarm LEDs
* c_flag - set when 'C' is pressed
* state - current state
    * 0 - do nothing wait for 'D' - 'B' turns off alarm
    * 1 - input digits m:ss, wait for A or C
    * 2 - paused 'A' starts timer, 'B' resets
    * 3 - count down - check for 'B'
    * 4 - make LEDs blink;

----------
API and Built In Elements Used
----------
* mbed.h
    * Ticker
    * InterruptIn

----------
Custom Functions
----------
* timer_isr()
    * The Ticker interrupt handler is triggered every second.
* column0_isr()
    * This is triggered when a button from Column 0 is pressed. 
* column1_isr()
    * This is triggered when a button from Column 1 is pressed. 
* column2_isr()
    * This is triggered when a button from Column 2 is pressed. 
* column3_isr()
    * This is triggered when a button from Column 3 is pressed. 



<br/>

--------------------
CSE321_project2_jessebot_timer.cpp:
--------------------
 This file handles all the timer aspects of the program.

----------
Things Declared
----------

<pre>
struct timer{
    int minutes
    int seconds
    int inc_by = 0
    char str[TIMER_SET_LEN+2]
    char min_goal = 0   
    char sec_goal = 0           
    char press[TIMER_SET_LEN+1]
    char press_i = 0
} timer
</pre>
* This struct contains all timer relavent variables.

----------
API and Built In Elements Used
----------
* mbed.h

----------
Custom Functions
----------

 * set_timer(int m, int s)
    * Sets the timer struct based on the inputs.
 * timer get_timer()
    * Returns the timer struct.
 * inc_timer(int by)
    * Increments the timer based on the input.  This is so the timer can be incremented or decremented.
 * goal_timer(int m, int s)
    * This is the time that the timer needs to reach. This will be 0 if decrementing time or the time the user set if incrementing.
 * string_timer()
    * Returns the timer value if the format m:ss.  This also sets the str value in the timer struct.
 * int_timer()
    * This function takes the press string from the struct and processes it to convert into 2 integers of mininutes and seconds.
 * set_inc_by_timer(int by)
    * This sets the value for incrementation inside the struct.
 * set_press_timer(char c)
    * Sets the next index as c in the press timer utilizing press_i.
 * reset_press_timer()
    * This sets the press timer to null characters.
 * output_press_timer() 
    * Converts the press string into the proper format to be diplayed on the LCD.
 * swap_timer()
    * Swaps the current time and the goal time.  This is done when 'C' is press approprietly. 
 * reset_timer()
    * Resets the timer struct to all the default values.

 <br/>
 
--------------------
CSE321_project2_jessebot_keypad.cpp:
--------------------

This file handles most of the keypad functionality.  Once an interrupt is triggered
this file is used to make sense of what key was pressed.

----------
Things Declared
----------

<pre>
keys[4][4] = { {'1', '2', '3', 'A'},
               {'4', '5', '6', 'B'}, 
               {'7', '8', '9', 'C'}, 
               {'*', '0', '#', 'D'} };
</pre>
* Array to determin which key was pressed 

<pre>
key[2];
</pre>
* Used to store what key was recently pressed.

----------
API and Built In Elements Used
----------
* mbed.h

----------
Custom Functions
----------

* get_char_keypad(char row, char col)
    * Returns the char that was pressed based on the input and using the keys array.

* set_row_keypad(char * row)
    * Sets which pin is currently active for the keypad.

* delay_keypad(char *pause, char *flag)
    * Delays the keypad from being pressed without sleeping.

* set_key(char c)
    * This function sets the key that was just pressed into key.

* get_key()
    * This function returns that value stored in key.

 <br/>

--------------------
CSE321_project2_jessebot_gpio.cpp:
--------------------
This file controls gpio manipulation.


----------
Things Declared
----------

<pre>
#define GPIO_INPUT      0x0
#define GPIO_OUTPUT     0x1
#define GPIO_ALTERNATE  0x2
#define GPIO_ANALOG     0x3
</pre>

----------
API and Built In Elements Used
----------
* mbed.h

----------
Custom Functions
----------

* gpio_on(GPIO_TypeDef *GPIO, int pin)
    * Turns gpio pin on based on the input. Manipulates ODR.
* gpio_off(GPIO_TypeDef *GPIO, int pin)
    * Turns gpio pin off based on the input. Manipulates ODR.
* gpio_enable(char *ports)
    * Enables ports based on string input.  'AB' enables ports A and B.
* gpio_moder(GPIO_TypeDef *GPIO, char pin, char set)
    * Enables MODER based on the input.
* gpio_sequential(int blink)
    * Makes LEDs blink Sequentailly.
* gpio_sequential_off()
    * Turns sequential LEDs off.

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
* string_to_int(char *str)
    * Converts a string to an integer.
* string_length(char *str)
    * Gets the string length.
* string_to_int_wlen(char *str, int len)
    * Converts a string to an integer with a known length.