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
#include <assert.h>


/*wraps the integer under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
/*since release@2020.1*/
static void* wrap_int(int value){
    /*allocate memory on heap for one integer*/
    int* wrapped_item = (int*)malloc(sizeof(int));
    /*validate memory allocation*/
    if (wrapped_item != NULL)
        *wrapped_item = value;
    /*return the wrapped item*/
    return (void*)wrapped_item;
}

/*get the integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
/*since release@2020.1*/
static int wrapped_int_value(void* wrapped_int){
    /*make an assertion on input pointer*/
    assert (wrapped_int != NULL);
    /*take a copy of value to be returned*/
    int returnValue = *((int*)wrapped_int);
    /*return the computed result*/
    return returnValue;
}

/*unwraps the integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
/*since release@2020.1*/
static int unwrap_int(void* wrapped_int){
    /*make an assertion on input pointer*/
    assert (wrapped_int != NULL);
    /*take a copy of value to be returned*/
    int returnValue = *((int*)wrapped_int);
    /*free memory allocated to pointer*/
    free (wrapped_int);
    /*return the computed result*/
    return returnValue;
}

/*wraps the unsigned long long integer under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
/*since release@2020.1*/
static void* wrap_ull_int(unsigned long long value){
    /*allocate memory on heap for one integer*/
    unsigned long long* wrapped_item = (unsigned long long*)malloc(sizeof(unsigned long long));
    /*validate memory allocation*/
    if (wrapped_item != NULL)
        *wrapped_item = value;
    /*return the wrapped item*/
    return (void*)wrapped_item;
}

/*get the unsigned long long integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
/*since release@2020.1*/
static unsigned long long wrapped_ull_int_value(void* wrapped_ull_int){
    /*make an assertion on input pointer*/
    assert (wrapped_ull_int != NULL);
    /*take a copy of value to be returned*/
    unsigned long long int returnValue = *((unsigned long long int*)wrapped_ull_int);
    /*return the computed result*/
    return returnValue;
}

/*unwraps the unsigned long long integer under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
/*since release@2020.1*/
static unsigned long long unwrap_ull_int(void* wrapped_ull_int){
    /*make an assertion on input pointer*/
    assert (wrapped_ull_int != NULL);
    /*take a copy of value to be returned*/
    unsigned long long int returnValue = *((unsigned long long int*)wrapped_ull_int);
    /*free memory allocated to pointer*/
    free (wrapped_ull_int);
    /*return the computed result*/
    return returnValue;
}



/*wraps the double under heap memory via pointer*/
/*returns the pointer to wrapped integer*/
/*returns NULL if operation fails*/
/*since release@2020.1*/
static void* wrap_double(double value){
    /*allocate memory on heap for one double*/
    double* wrapped_item = (double*)malloc(sizeof(double));
    /*validate memory allocation*/
    if (wrapped_item != NULL)
        *wrapped_item = value;
    /*return the wrapped item*/
    return (void*)wrapped_item;
}

/*get the double under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*asserts that input pointer is not NULL*/
/*since release@2020.1*/
static double wrapped_double_value(void* wrapped_double){
    /*make an assertion on input pointer*/
    assert (wrapped_double != NULL);
    /*take a copy of value to be returned*/
    double returnValue = *((double*)wrapped_double);
    /*return the computed result*/
    return returnValue;
}

/*unwraps the double under heap memory via pointer*/
/*return the value of wrapped pointer*/
/*frees the memory allocated to pointer*/
/*asserts that input pointer is not NULL*/
/*since release@2020.1*/
static double unwrap_double(void* wrapped_double){
    /*make an assertion on input pointer*/
    assert (wrapped_double != NULL);
    /*take a copy of value to be returned*/
    double returnValue = *((double*)wrapped_double);
    /*free memory allocated to pointer*/
    free (wrapped_double);
    /*return the computed result*/
    return returnValue;
}





/*declaration of structure Wrapper*/
struct {
    /*wrapInt method*/
    void*(*const wrapInt)(int);
    /*unwrapInt method*/
    int(*const unwrapInt)(void*);
    /*intValue method*/
    int(*const intValue)(void*);

    /*wrapULL method*/
    void*(*const wrapULL)(unsigned long long);
    /*unwrapInt method*/
    unsigned long long(*const unwrapULL)(void*);
    /*ullValue method*/
    unsigned long long(*const ullValue)(void*);

    /*wrapDouble method*/
    void*(*const wrapDouble)(double);
    /*unwrapDouble method*/
    double(*const unwrapDouble)(void*);
    /*doubleValue method*/
    double(*const doubleValue)(void*);
}Wrapper = {
    /*set wrapInt method*/
    .wrapInt = wrap_int,
    /*set unwrapInt method*/
    .unwrapInt = unwrap_int,
    /*set intValue method*/
    .intValue = wrapped_int_value,

    /*set wrapULL method*/
    .wrapULL = wrap_ull_int,
    /*set unwrapULL method*/
    .unwrapULL = unwrap_ull_int,
    /*set ullValue method*/
    .ullValue = wrapped_ull_int_value,

    /*set wrapDouble method*/
    .wrapDouble = wrap_double,
    /*set unwrapDouble method*/
    .unwrapDouble = unwrap_double,
    /*set doubleValue method*/
    .doubleValue = wrapped_double_value
};