/*
    This file is a part of utility library.
    https://github.com/PanchalShubham/c-utility-library/index.html
    Copyright (C) 2020  Shubham Panchal(shubhampanchal9773@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * */

/*include necessary headers*/
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <assert.h>

/*declaration of structure Timer*/
typedef struct Timer{
    /*each stop watch instance has a starting time*/
    struct timeval start_time;
    /*each stop watch instance has an ending time*/
    struct timeval end_time;
    /*stores the state of Timer*/
    bool timer_running;
}Timer;


/*creates a new Timer and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
Timer* new_timer(void) {
    /*allocate memory for new Timer*/
    Timer* watch = (Timer*)malloc(sizeof(Timer));
    /*validate memory allocation*/
    if (watch != NULL){
        /*update fields of Timer*/
        watch->start_time.tv_sec = watch->start_time.tv_usec = 0;
        watch->end_time.tv_sec = watch->end_time.tv_usec = 0;
        /*update state to false*/
        watch->timer_running = false;
    }
    /*return newly created watch*/
    return watch;
}

/*starts the Timer*/
/*asserts that input Timer is not NULL and isn't already started*/
/*since release@2020.1*/
void timer_start(Timer *watch){
    /*make an assertion on input watch*/
    assert (watch != NULL && !watch->timer_running);
    /*call get time of day to store current time*/
    gettimeofday(&(watch->start_time), NULL);
    /*update the state of Timer*/
    watch->timer_running = true;
}

/*stops the Timer*/
/*asserts that the input Timer is not NULL and is running*/
/*since release@2020.1*/
void timer_stop(Timer *watch){
    /*make an assertion on input watch*/
    assert (watch != NULL && watch->timer_running);
    /*call get time of day to store current time*/
    gettimeofday(&(watch->end_time), NULL);
    /*update the state of watch*/
    watch->timer_running = false;
}


/*returns the time elapsed*/
/*asserts that input Timer is not NULL and is not running*/
/*since release@2020.1*/
long long int timer_time_elapsed(Timer* watch){
    /*make an assertion on input watch*/
    assert (watch != NULL && !watch->timer_running);
    /*compute the time in microseconds for start and end*/
    long long int start_time = watch->start_time.tv_sec*((long long int)1000000) + watch->start_time.tv_usec;
    long long int end_time = watch->end_time.tv_sec*((long long int)1000000) + watch->end_time.tv_usec;
    /*return the difference in start and end time*/
    return (end_time - start_time);
}

/*resets the Timer*/
/*asserts that the input Timer is not NULL*/
/*since release@2020.1*/
void reset_timer(Timer* watch){
    /*make an assertion on input watch*/
    assert (watch != NULL);
    /*update fields of Timer*/
    watch->start_time.tv_sec = watch->start_time.tv_usec = 0;
    watch->end_time.tv_sec = watch->end_time.tv_usec = 0;
    /*update state to false*/
    watch->timer_running = false;
}

/*frees the memory allocated to Timer*/
/*asserts that the input Timer is not NULL*/
/*since release@2020.1*/
void free_timer(Timer* watch){
    /*make an assertion on input watch*/
    assert (watch != NULL);
    /*free memory allocated to Timer*/
    free (watch);
}