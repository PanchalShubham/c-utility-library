#ifndef UTILITY_WRAPPER_H
#define UTILITY_WRAPPER_H

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


/*include source file*/
#include "definitions/wrapper.c"


/*wraps the integer under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
extern void* wrap_int(int value);

/*get the integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
extern int wrapped_int_value(void* wrapped_int);

/*unwraps the integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
extern int unwrap_int(void* wrapped_int);




/*wraps the unsigned long long integer under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
extern void* wrap_ull_int(unsigned long long int value);

/*get the unsigned long long integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
extern unsigned long long int wrapped_ull_int_value(void* wrapped_ull_int);

/*unwraps the unsigned long long integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
extern unsigned long long int unwrap_ull_int(void* wrapped_ull_int);


/*wraps the float under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
extern void* wrap_float(float value);


/*get the float under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
extern float wrapped_float_value(void* wrapped_float);

/*unwraps the float under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
extern float unwrap_float(void* wrapped_float);



/*wraps the double under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
extern void* wrap_double(double value);


/*get the double under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
extern double wrapped_double_value(void* wrapped_double);


/*unwraps the double under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
extern double unwrap_double(void* wrapped_double);

#endif
