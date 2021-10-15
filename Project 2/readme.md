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
    * Displays time remaining.

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
1. Build the Circuit (place schematic here)
2. Build a new project in Mbed Studio
3. Select the Nucleo L4R5ZI as the target
4. Move files into Program
5. Build the program.
6. Use the keypad for user input.

<br/>

--------------------
CSE321_project2_jessebot_main.cpp:
--------------------
 

----------
Things Declared
----------

* Ticker TIME
* CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8)
* InterruptIn Column0(PF_14)
* InterruptIn Column1(PE_11)
* InterruptIn Column2(PE_9)
* InterruptIn Column3(PF_13)

* char timer_flag    
    - Used to indicate when to modify the timer. 
This is set in the interrupt handler for the Ticker.
* char row 
    - Used to indicate which row is currently active to determine which button was pressed.

----------
API and Built In Elements Used
----------
mbed.h

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
 

----------
Things Declared
----------
* struct timer{  
&nbsp;      int minutes;  
&nbsp;      int seconds;  
&nbsp;      char str[6]; // mm:ss  
} timer;  

----------
Custom Functions
----------
 * void set_timer(int m, int s)
    * Sets the timer struct based on the inputs.
 * struct timer get_timer()
    * Returns the timer struct.
 * void inc_timer(int by)
    * Increments the timer based on the input.  This is so the timer can be incremented or decremented.
 * int goal_timer(int m, int s)
    * This is the time that the timer needs to reach. This will be 0 if decrementing time or the time the user set if incrementing.
 * char *string_timer()
    * Returns the timer value if the format m:ss.  This also sets the str value in the timer struct.

 <br/>
 
--------------------
CSE321_project2_jessebot_keypad.cpp:
--------------------
- Currently does nothing.
TODO