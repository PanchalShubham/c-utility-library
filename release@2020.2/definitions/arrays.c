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
#include "../random.h"

/*define types of array-comparator*/
/*compares array1[i] with array2[j] and returns -1, 0 or 1 accordingly*/
typedef int(*ArrayIndicesComparator)(const void* array1, const void* array2, int i, int j);
/*compares key with array at index i i.e. array[i] & key*/
typedef int(*ArrayKeyComparator)(const void* array, const void* key, int i) ;
/*swaps the elements in array at index i and j*/
typedef void(*ArrayIndicesSwapper)(void* array, int i, int j);
/*copies the value at index i from source array to destination array*/
typedef void(*ArrayIndicesCopier)(const void* source, void* destination, int sourceIndex, int destinationIndex);


/*creates an integer array on heap of size N*/
/*do not populate array - returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
int* new_int_array(int N){
    /*make an assertion on input size*/
    assert (N > 0);
    /*allocate memory for N integers on heap*/
    int* array = (int*)malloc(sizeof(int)*N);
    /*return newly created array*/
    return array;
}

/*creates an integer array on heap of size N and populates it with value*/
/*returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
int* new_int_array_with(int N, int value){
    /*make an assertion on input size*/
    assert (N > 0);
    /*allocate memory for N integers on heap*/
    int* array = (int*)malloc(sizeof(int)*N);
    /*validate memory allocation*/
    if (array != NULL){
        /*iterate through array and populate entries*/
        for (int i = 0; i < N; ++i)
            array[i] = value;
    }
    /*return newly created array*/
    return array;
}

/*creates a randomly populated integer array of size N in range[0...100]*/
/*and returns a pointer to it if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
int* new_random_int_array(int N){
    /*make an assertion on input size*/
    assert (N > 0);
    /*allocate memory for N integers on heap*/
    int* array = (int*)malloc(sizeof(int)*N);
    /*validate memory allocation*/
    if (array != NULL){
        /*seed random number generator*/
        randomize();
        /*iterate through array and populate entries*/
        for (int i = 0; i < N; ++i)
            array[i] = random_int_upper_bound(100);
    }
    /*return newly created array*/
    return array;
}










/*creates a double array on heap of size N*/
/*do not populate array - returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
double* new_double_array(int N){
    /*make an assertion on input size*/
    assert (N > 0);
    /*allocate memory for N doubles on heap*/
    double* array = (double*)malloc(sizeof(double)*N);
    /*return newly created array*/
    return array;
}

/*creates a double array on heap of size N and populates with value*/
/*returns a pointer to first element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
double* new_double_array_with(int N, double value){
    /*make an assertion on input size*/
    assert (N > 0);
    /*allocate memory for N doubles on heap*/
    double* array = (double*)malloc(sizeof(double)*N);
    /*validate memory allocation*/
    if (array != NULL){
        /*iterate through array and populate entries*/
        for (int i = 0; i < N; ++i)
            array[i] = value;
    }
    /*return newly created array*/
    return array;
}

/*creates a randomly populated double array of size N with values in range [0,1]*/
/*returns a pointer to 1st element of array if succeeds otherwise returns a NULL pointer*/
/*asserts that input size is greater than zero*/
/*since release@2020.1*/
double* new_random_double_array(int N){
    /*make an assertion on input size*/
    assert (N > 0);
    /*allocate memory for N doubles on heap*/
    double* array = (double*)malloc(sizeof(double)*N);
    /*validate memory allocation*/
    if (array != NULL){
        /*seed random number generator*/
        randomize();
        /*iterate through array and populate entries*/
        for (int i = 0; i < N; ++i)
            array[i] = random_double();
    }
    /*return newly created array*/
    return array;
}








/*shuffles the content of array uniformly in given range*/
/*asserts that input array and callback not NULL and bounds are valid*/
/*since release@2020.1*/
void shuffle_array(void* array, int low, int high, ArrayIndicesSwapper swap_callback){
    /*make an assertion on inputs*/
    assert (array != NULL);
    /*make an assertion on bounds*/
    assert ( 0 <= low && low <= high);
    /*make an assertion on callback*/
    assert (swap_callback != NULL);
    /*iterate through array and rearrange content*/
    for (int i = low + 1; i <= high; ++i){
        /*select a random element from array[0..i-1] and swap*/
        /*it with array[i] for rearrangement*/
        (*swap_callback)(array, random_int_range(low, i - 1), i);
    }
}

/*reverses the content of array*/
/*asserts that array and callback aren't NULL and indices are in bound*/
/*since release@2020.1*/
void reverse_array(void* array, int low,int high, ArrayIndicesSwapper indicesSwapper){
    /*make an assertion on array*/
    assert (array != NULL);
    /*make an assertion on callback*/
    assert (indicesSwapper != NULL);
    /*iterate to half of the array*/
    for (int i = low, j = high; i <= j; ++i, --j)
        /*swap values at indices i and j*/
        ((*indicesSwapper)(array, i, j));
}




/*returns the index of first occurrence of key in array if exist otherwise returns -1*/
/*asserts that input array and callback aren't NULL and indices are in bound*/
/*since release@2020.1*/
int linear_search(const void* array, int low, int high, const void* key, ArrayKeyComparator keyComparator){
    /*make an assertion on input array*/
    assert (array != NULL);
    /*make an assertion on array bonds*/
    assert ( 0 <= low && low <= high);
    /*assertion on callback*/
    assert (keyComparator != NULL);
    /*iterate through array*/
    for (int i = low; i <= high; ++i)
        /*make a  comparison*/
        if ((*keyComparator)(array, key, i) == 0)
            /*data found at index i*/
            return i;
    /*data do not exist in array*/
    return -1;
}


/*returns the index of key which is closest to middle of array if exist otherwise returns -1*/
/*asserts that array, callback aren't NULL and indices are in bound*/
/*since release@2020.1*/
int binary_search(const void* array, int low, int high, const void* key, ArrayKeyComparator keyComparator){
    /*make an assertion on input array*/
    assert (array != NULL);
    /*make an assertion on bounds*/
    assert ( 0 <= low && low <= high);
    /*assertion on callback*/
    assert (keyComparator != NULL);
    /*iterate as long as size of sub array is greater than zero*/
    while (low <= high){
        /*compute the mid*/
        int mid = low + (high - low)/2;
        /*compare key with middle element*/
        int comparison_result = (*keyComparator)(array, key, mid);
        /*take decision based on comparison result*/
        if ( comparison_result == 0)
            /*element found at index mid*/
            return mid;
        else if ( comparison_result  > 0)
            /*key cannot exist in right sub-array*/
            high = mid - 1;
        else
            /*key cannot exist in left sub-array*/
            low = mid + 1;
    }
    /*returns -1 since element do not exist*/
    return -1;
}




/*sorts the input array using insertion sort algorithm*/
/*asserts that array, auxiliary array and callbacks aren't NULL and indices are in bound*/
/*since release@2020.1*/
void insertion_sort(void* array, int low, int high, ArrayIndicesComparator indicesComparator, ArrayIndicesSwapper indicesSwapper){
    /*make an assertion on array*/
    assert (array != NULL);
    /*make an assertion on indices*/
    assert ( low >= 0);
    /*make an assertion on callback*/
    assert (indicesComparator != NULL && indicesSwapper != NULL);
    /*takes care of number of passes*/
    for (int i = low; i <= high; ++i)
        /*as long as elements are out of order swap*/
        for (int j = i; j > low; --j)
            if ((*indicesComparator)(array, array, j, j - 1) < 0)
                ((*indicesSwapper)(array, j , j - 1));
            else
                break;
}


/*chose one element as pivot and keep it at its correct position and returns the index of the pivot*/
/*since release@2020.1*/
static int partition(void* array, int low, int high, ArrayIndicesComparator compare_callback, ArrayIndicesSwapper arrayIndicesSwapper){
    /*choose a random element as pivot*/
    int pivotIndex = random_int_range(low, high);
    /*utility_swap last element with pivotIndex*/
    (*arrayIndicesSwapper)(array, pivotIndex, high);
    /*we start from one index less than low*/
    int i = low - 1;
    /*iterate through and search for correct position of pivot*/
    for (int j = low; j < high; ++j) {
        /*check if jth element is less than or equal to pivot*/
        if ((*compare_callback)(array, array, j, high) != 1) {
            /*increase i by 1*/
            i += 1;
            /*utility_swap array[j] with array[i]*/
            (*arrayIndicesSwapper)(array, i, j);
        }
    }
    /*increase the value of i by 1*/
    i += 1;
    /*utility_swap pivot with array[i]*/
    (*arrayIndicesSwapper)(array, i, high);
    /*return i*/
    return i;
}

/*sorts the given input array using quick sort algorithm*/
/*asserts that array, auxiliary array and callbacks aren't NULL and indices are in bound*/
/*since release@2020.1*/
void quick_sort(void* array, int low, int high, ArrayIndicesComparator indicesComparator, ArrayIndicesSwapper indicesSwapper){
    /*requires size of the array to be at least 2*/
    if (low < high){
        /*make an assertion on array*/
        assert (array != NULL);
        /*make an assertion on indices*/
        assert ( low >= 0);
        /*make an assertion on callback*/
        assert (indicesComparator != NULL && indicesSwapper != NULL);
        /*call partition function*/
        int pivotIndex = partition(array, low, high, indicesComparator, indicesSwapper);
        /*call quick sort on left and right sub arrays*/
        quick_sort(array, low, pivotIndex - 1, indicesComparator, indicesSwapper);
        quick_sort(array, pivotIndex + 1, high, indicesComparator, indicesSwapper);
    }
}



/*merges the two sub-parts of the array so that entire array is sorted*/
/*since release@2020.1*/
static void merge_sub_arrays(void* array, void* auxiliary_array, int low, int mid, int high, ArrayIndicesComparator compare_callback, ArrayIndicesCopier copy_callback){
    /*copy original array content to auxiliary array from [low...high]*/
    for (int i = low; i <= high; ++i)
        (*copy_callback)(array, auxiliary_array, i, i);

    /*temporary variables for processing*/
    int i = low, j = mid + 1;
    /*iterate through array and rearrange content*/
    for (int k = low; k <= high; ++k){
        if (i > mid)
            ((*copy_callback)(auxiliary_array, array, j++, k));
        else if (j > high)
            ((*copy_callback)(auxiliary_array, array, i++, k));
        else if ((*compare_callback)(auxiliary_array, auxiliary_array, j, i) < 0 || i > mid)
            ((*copy_callback)(auxiliary_array, array, j++, k));
        else
            ((*copy_callback)(auxiliary_array, array, i++, k));
    }
}

/*sorts the given input array using merge sort algorithm*/
/*asserts that array, auxiliary array and callbacks aren't NULL and indices are in bound*/
/*since release@2020.1*/
void merge_sort(void* array, void* auxiliary_array, int low, int high, ArrayIndicesComparator indicesComparator, ArrayIndicesCopier indicesCopier){
    /*requires the size of array to be at least two*/
    if (low < high){
        /*make an assertion on arrays*/
        assert (array != NULL && auxiliary_array != NULL);
        /*make an assertion on indices*/
        assert ( low >= 0);
        /*make an assertion on callback*/
        assert (indicesComparator != NULL && indicesCopier != NULL);
        /*partition the array into halves*/
        int mid = (low + high)/2;
        /*sort two parts of the array using merge sort*/
        merge_sort(array, auxiliary_array, low, mid, indicesComparator, indicesCopier);
        merge_sort(array, auxiliary_array, mid  + 1, high, indicesComparator, indicesCopier);
        /*merge these two parts of the array to get entire sorted array*/
        merge_sub_arrays(array, auxiliary_array, low, mid, high, indicesComparator, indicesCopier);
    }
}



/*frees the memory allocated to array*/
/*asserts that input array is not NULL*/
/*since release@2020.1*/
void free_array(void* array){
    /*make an assertion on input array*/
    assert (array != NULL);
    /*free memory allocated to array*/
    free (array);
}









