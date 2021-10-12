struct timer{
    int minutes;
    int seconds;
    char str[6];
} timer;

void set_timer(int m, int s){
    timer.minutes = m;
    timer.seconds = s;
}

struct timer get_timer(){
    return timer;
}

void inc_timer(int by){
    timer.seconds += by;
    if(timer.seconds == 60){
        timer.minutes += by;
        timer.seconds = 0;
    }
    else if(timer.seconds == 0){
        timer.minutes += by;
        timer.seconds = 59;
    }
    
}

int goal_timer(int m, int s){
    if(timer.minutes == m && timer.seconds == s){
        return true;
    }
    return false;
}

char *string_timer(){
    int x = 0;
    if(timer.minutes < 10){
        timer.str[x++] = timer.minutes + '0';
    }
    else{
        // get 10's place by itself and convert to a char
        timer.str[x++] = ((timer.minutes - (timer.minutes % 10)) / 10) + '0';
        timer.str[x++] = (timer.minutes % 10) + '0';
    }

    timer.str[x++] = ':';
    if(timer.seconds < 10){
        timer.str[x++] = '0';
        timer.str[x] = timer.seconds + '0';
    }
    else{
        // get 10's place by itself and convert to a char
        timer.str[x++] = ((timer.seconds - (timer.seconds % 10)) / 10) + '0';
        timer.str[x] = (timer.seconds % 10) + '0';
    }
    
    return timer.str;
}

