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

#ifndef UTILITY_ARRAYS_H
#define UTILITY_ARRAYS_H


/*include source header*/
#include "types.h"
#include "definitions/arrays.c"


/*creates an integer array on heap of size N*/
/*do not populate array - returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
extern int* new_int_array(int N);

/*creates an integer array on heap of size N and populates it with value*/
/*returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
extern int* new_int_array_with(int N, int value);

/*creates a randomly populated integer array of size N in range [0...100]*/
/*and returns a pointer to it if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
extern int* new_random_int_array(int N);







/*creates a double array on heap of size N*/
/*do not populate array - returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
extern double* new_double_array(int N);

/*creates a double array on heap of size N and populates with value*/
/*returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
extern double* new_double_array_with(int N, double value);

/*creates a randomly populated double array of size N with values in range [0,1]*/
/*returns a pointer to 1st element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
extern double* new_random_double_array(int N);







/*shuffles the content of array uniformly in given range*/
/*asserts that input array and callback not NULL and bounds are valid*/
/*since release@2020.1*/
extern void shuffle_array(void* array, int low, int high, ArrayIndicesSwapper swap_callback);

/*reverses the content of array*/
/*asserts that array and callback aren't NULL and indices are in bound*/
/*since release@2020.1*/
extern void reverse_array(void* array, int low,int high, ArrayIndicesSwapper indicesSwapper);




/*returns the index of first occurrence of key in array if exist otherwise returns -1*/
/*asserts that input array and callback aren't NULL and indices are in bound*/
/*since release@2020.1*/
extern int linear_search(const void* array, int low, int high, const void* key, ArrayKeyComparator keyComparator);

/*returns the index of key which is closest to middle of array if exist otherwise returns -1*/
/*asserts that array, callback aren't NULL and indices are in bound*/
/*since release@2020.1*/
extern int binary_search(const void* array, int low, int high, const void* key, ArrayKeyComparator keyComparator);







/*sorts the input array using insertion sort algorithm*/
/*asserts that array, auxiliary array and callbacks aren't NULL and indices are in bound*/
/*since release@2020.1*/
extern void insertion_sort(void* array, int low, int high, ArrayIndicesComparator indicesComparator, ArrayIndicesSwapper indicesSwapper);

/*sorts the given input array using quick sort algorithm*/
/*asserts that array, auxiliary array and callbacks aren't NULL and indices are in bound*/
/*since release@2020.1*/
extern void quick_sort(void* array, int low, int high, ArrayIndicesComparator indicesComparator, ArrayIndicesSwapper indicesSwapper);

/*sorts the given input array using merge sort algorithm*/
/*asserts that array, auxiliary array and callbacks aren't NULL and indices are in bound*/
/*since release@2020.1*/
extern void merge_sort(void* array, void* auxiliary_array, int low, int high, ArrayIndicesComparator indicesComparator, ArrayIndicesCopier indicesCopier);



/*frees the memory allocated to array*/
/*asserts that input array is not NULL*/
/*since release@2020.1*/
extern void free_array(void* array);

#endif



