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

#ifndef UTILITY_LINKEDHEAP_H
#define UTILITY_LINKEDHEAP_H

/*include source file*/
#include "definitions/linkedheap.c"

/*creates a new linked heap and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that type is valid*/
/*since release@2020.2*/
extern LinkedHeap* new_linked_heap(enum LinkedHeapType type);


/*adds given data to linked heap and returns true if succeeds otherwise returns false*/
/*asserts that heap and callback aren't NULL*/
/*since release@2020.2*/
extern bool linked_heap_add(LinkedHeap* heap, void* data, Comparator comparator);


/*returns and removes the max/min data in heap if exist otherwise returns NULL*/
/*asserts that heap and callback aren't NULL*/
/*since release@2020.2*/
extern void* linked_heap_extract(LinkedHeap* heap, Comparator comparator);


/*replace the 1st occurrence of key with newKey in heap if exist; returns true if succeeds otherwise returns false*/
/*optionally frees the memory allocated to key and keyInQueue*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
extern bool linked_heap_replace(LinkedHeap* heap, void* oldKey, void* newKey, Comparator comparator, bool freeOldKey, bool freeKeyInQueue);


/*returns the size of the linked heap*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
extern int linked_heap_size(LinkedHeap* heap);


/*returns true if heap is empty otherwise returns false*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
extern bool linked_heap_is_empty(LinkedHeap* heap);


/*returns the root of the heap if exist otherwise returns NULL*/
/*asserts that heap isn't NULL*/
/*since release@2020.2*/
extern void* linked_heap_root(LinkedHeap* heap);

/*returns true if heap contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that heap and callback aren't NULL*/
/*since release@2020.2*/
extern bool linked_heap_contains(LinkedHeap* heap, void* key, Comparator comparator, bool freeKeyAtEnd);


/*frees the memory allocated to heap*/
/*optionally frees the memory  allocated to nodes*/
/*asserts that heap is not empty*/
extern void free_linked_heap(LinkedHeap* heap, bool freeKeys);

#endif