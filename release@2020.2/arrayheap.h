
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


#ifndef UTILITY_ARRAYHEAP_H
#define UTILITY_ARRAYHEAP_H

/*include source file*/
#include "definitions/arrayheap.c"
#include <stdbool.h>


/*creates a new array heap for on heap and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that initial capacity is a positive integer and type is valid*/
/*since release@2020.2*/
extern ArrayHeap* new_array_heap(int initial_capacity, enum ArrayHeapType type);


/*adds given data to array heap and returns true if succeeds otherwise returns false*/
/*asserts that heap, heap's array and callback aren't NULL*/
/*since release@2020.2*/
extern bool array_heap_add(ArrayHeap* heap, void* data, Comparator comparator);

/*returns and removes the data with max/min in heap if exist otherwise returns NULL*/
/*asserts that heap, heap's array and callback aren't NULL*/
/*since release@2020.2*/
extern void* array_heap_extract(ArrayHeap* heap, Comparator comparator);

/*replace the 1st occurrence of key with newKey in if exist; returns true if succeeds otherwise returns false*/
/*optionally frees the memory allocated to key and keyInQueue*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
extern bool array_heap_replace(ArrayHeap* heap, void* oldKey, void* newKey, Comparator comparator, bool freeOldKey, bool freeKeyInQueue);

/*returns the size of the heap*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
extern int array_heap_size(ArrayHeap* heap);

/*returns the capacity of the heap*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
extern int array_heap_capacity(ArrayHeap* heap);

/*returns true if heap is empty otherwise returns false*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
extern bool array_heap_is_empty(ArrayHeap* heap);

/*returns the root of the heap if exist otherwise returns NULL*/
/*asserts that heap and heap's array aren't NULL*/
/*since release@2020.2*/
extern void* array_heap_root(ArrayHeap* heap);

/*returns the index of 1st occurrence of key in heap if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
extern int array_heap_indexOf(ArrayHeap* heap, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns true if heap contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
extern bool array_heap_contains(ArrayHeap* heap, void* key, Comparator comparator, bool freeKeyAtEnd);


/*frees the memory allocated to heap*/
/*optionally frees the memory allocated to keys in heap*/
/*asserts that heap and heap's arrays aren't NULL*/
/*since release@2020.2*/
extern void free_array_heap(ArrayHeap* heap, bool freeKeys);

#endif