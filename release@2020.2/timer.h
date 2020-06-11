/*
    This file is a part of utility library.
    https://github.com/PanchalShubham/UtilityLibrary
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
#ifndef UTILITY_TIMER_H
#define UTILITY_TIMER_H

/*include source file*/
#include "definitions/timer.c"

/*creates a new Timer and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
extern Timer* new_timer(void);

/*starts the Timer*/
/*asserts that input Timer is not NULL and isn't already started*/
/*since release@2020.1*/
extern void timer_start(Timer *watch);

/*stops the Timer*/
/*asserts that the input Timer is not NULL and is running*/
/*since release@2020.1*/
extern void timer_stop(Timer *watch);


/*returns the time elapsed*/
/*asserts that input Timer is not NULL and is not running*/
/*since release@2020.1*/
extern long long int timer_time_elapsed(Timer* watch);

/*resets the Timer*/
/*asserts that the input Timer is not NULL*/
/*since release@2020.1*/
extern void reset_timer(Timer* watch);

/*frees the memory allocated to Timer*/
/*asserts that the input Timer is not NULL*/
/*since release@2020.1*/
extern void free_timer(Timer* watch);

#endif