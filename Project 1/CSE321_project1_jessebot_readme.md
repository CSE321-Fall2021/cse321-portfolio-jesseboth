-------------------
About
-------------------
Project Description: 
* Toggles the onboard LED to either be off or blinking.
The onboard button is used to perform this toggle.  The button requires 
a double click in order to toggle the LED.  The first press down does nothing and on release it sets a flag that will allow the next press to toggle the LED.

Contribitor List: Jesse Both


--------------------
Features
--------------------
Utilizes the onboard LED and Button


--------------------
Required Materials
--------------------
-Nucleo L4R5ZI

--------------------
Resources and References
--------------------
* [STM32 Nucleo-144 boards](https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf)
* [RM0432](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

--------------------
Getting Started
--------------------
1. Build a new project in Mbed Studio
2. Select the Nucleo L4R5ZI as the target
3. Copy the code from CSE321_project1_jessebot_corrected_code.cpp into main.cpp
4. Build the program.
5. Use the onboard button to toggle the onboard LED blinking.

--------------------
CSE321_project1_jessebot_corrected_code.cpp:
--------------------
 
This file utilizes interrupts and threads inorder to make an LED
blink or not.  The onboard button triggers an interrupt on both its rise and fall.

The keywords DigitalIn and DigitalOut are used to set the button as input and led as output respectively.  There is also a funtion that runs on an alternate Thread called controller.


----------
Things Declared
----------
Variables, functions, objects, and APIs used:

* mbed.h - mbed header file.

* controller - Thread the polling is run on.

* DigitialOut led(LED2) - Controlls whether LED2 is on or off.

* DigitialIn button_handler(BUTTON1) - Sets BUTTON1 to input.

* polling( ) - Loops infinitly and makes the led blink when the conditon applies. 

* set_flag( ) - Interrupt handler when BUTTON1 rises. Sets "flag" to 1.

* toggle_blink( ) - Interrupt handler when BUTTON1 falls. Activates/Deactivates blinking LED if "flag" is set.

* blink - LED2 blinks when set to 0.

* flag - Allows "blink" to toggle when set to 1.



----------
API and Built In Elements Used
----------
mbed.h

* Thread

* DigitalOut

* DigitalIn


----------
Custom Functions
----------

polling( ):

* Loops infinitly and makes the led blink when the conditon applies. 
	
* Inputs:
 	* None
	
* Globally Referenced Variables Used:
	* blink
	* led
	* printf

set_flag( ):

* Interrupt Handler 

* When BUTTON1 rises sets "flag" to 1.
	
* Inputs:
 	* None
	
* Globally Referenced Variables Used:
	* flag

toggle_blink( ):

* Interrupt Handler 

* when BUTTON1 falls it activates/deactivates blinking LED if "flag" is set.
	
* Inputs:
 	* None
	
* Globally Referenced Variables Used:
	* flag
	* blink


