#include "mbed.h"
#include "CSE321_project2_jessebot_lib.h"

#define TIMER_MAX_LEN 4
#define TIMER_LOC 6
struct timer;

void set_timer(int m, int s);
struct timer get_timer();
void inc_timer();
int goal_timer();
char *string_timer();
void int_timer();
void set_inc_by_timer(int by);
void set_press_timer(char c);
void reset_press_timer();
char *output_press_timer();
void swap_timer();
void reset_timer();
