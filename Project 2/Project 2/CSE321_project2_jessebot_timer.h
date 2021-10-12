struct timer;

void set_timer(int m, int s);
struct timer get_timer();
void inc_timer(int by);
int goal_timer(int m, int s);
char *string_timer();

