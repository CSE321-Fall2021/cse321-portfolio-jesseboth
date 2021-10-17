#include "mbed.h"

struct timer;

void set_timer(int m, int s);
struct timer get_timer();
void inc_timer();
int goal_timer();
char *string_timer();
void set_inc_by_timer(int by);
void set_press_timer(char c);
void reset_press_timer();
void decode_timer();
int string_to_int(char *str);
int string_length(char *str);