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

#ifndef UTILITY_RANDOM_H
#define UTILITY_RANDOM_H

/*source header*/
#include "definitions/random.c"

/*seeds the random number generator*/
/*since release@2020.1*/
extern void randomize(void);


/*generates a random integer*/
/*since release@2020.1*/
extern int random_int(void);

/*generates a random integer with given upper bound i.e. in range [0...upper_bound]*/
/*asserts that upper bound is a non-negative integer*/
/*since release@2020.1*/
extern int random_int_upper_bound(int upper_bound);

/*generates a random integer withing given bounds i.e. in range [lower_bound...upper_bound]*/
/*asserts that 0 <= lower_bound <= upper_bound*/
/*since release@2020.1*/
extern int random_int_range(int lower_bound, int upper_bound);

/*generates a random double in range [0,1]*/
/*since release@2020.1*/
double random_double(void);

/*generates a random double with given upper bound i.e. in range [0...upper_bound]*/
/*asserts that upper bound is a non-negative integer*/
/*since release@2020.1*/
extern double random_double_upper_bound(double upper_bound);


/*generates a random double within given bounds i.e. in range [lower_bound...upper_bound]*/
/*asserts that 0 <= lower_bound <= upper_bound*/
/*since release@2020.1*/
extern double random_double_range(double lower_bound, double upper_bound);

/*generates a random binary string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_binary_string(int length);

/*generates a random octal string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_octal_string(int length);

/*generates a random decimal string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_decimal_string(int length);

/*generates a random hexadecimal string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_hex_string(int length);


/*generates a random printable string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_printable_string(int length);


/*generates a random alphabetical string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_alphabetical_string(int length);

/*generates a random alphabetical string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_alphanumeric_string(int length);


/*generates a random special characters string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
extern char* random_special_string(int length);



#endif