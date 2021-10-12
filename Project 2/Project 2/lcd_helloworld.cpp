// #include "mbed.h"
// #include "1802.h"

// #define LCD_COLS 16
// #define LCD_ROWS 2


// CSE321_LCD LCD(LCD_COLS, LCD_ROWS, LCD_5x8DOTS, PB_9, PB_8);

// int lcd_hello()
// {
//     int x, y, flag;
//     LCD.begin();

//     x = 0;
//     y = 0;
//     flag = 0;
//     while (true) {
        
//         LCD.setCursor(x, y);
//         LCD.print("Hello World");
//         thread_sleep_for(2000);
//         LCD.clear();

//         if(x==0){
//             flag = 1;
//         }
//         else if(x==5){
//             flag = 0;
//         }
//         if(flag){x++;}
//         else{x--;}
//     }
// }