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
#ifndef UTILITY_ARRAYLIST_H
#define UTILITY_ARRAYLIST_H


/*include source file*/
#include "definitions/arraylist.c"
/*include stdbool*/
#include <stdbool.h>

/**
 *
 * arraylist.h
 * @since release@2020.1
 * Resizable-array implementation of the list data structure.
 * Implements all list operations, and permits all elements, including NULL.
 * ArrayList and ArrayListIterator are types defined by the header
 * ArrayListMethods instance provides the methods for creating and manipulating list
 * ArrayList is not synchronized
 * insertion/deletion takes constant amortized time
 * search/reverse/free/clear takes linear time
 * sorting takes linearthimic time
 * all other operations takes constant time
 *
 *
 *
 * @since release@2020.1
 * ArrayList and ArrayListIterator
 *
 * @since release@2020.2
 * ArrayListMethods
 *
 * ArrayListMethods.newList()
 * ArrayList* newList(int initialCapacity)
 * creates a new array-list with given initial-capacity
 * @param initialCapacity is the initial size of the array
 * @return a pointer to newly created array-list if succeed otherwise null
 * @assert {@code initialCapacity} is a positive integer
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.insertAt()
 * bool insertAt(ArrayList* list, void* value, int index)
 * inserts the data at given index in array-list
 * @param list is a pointer to the list for insertion
 * @param value is the value to be inserted
 * @param index is the the index for insertion (0...N)
 * index-0 indicates insertion at front
 * index-n indicates insertion at back
 * @assert that list and list's array are not NULL and index is in range [0,N]
 * @return true if insertion succeeds, false otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.insertFront()
 * bool insertFront(ArrayList* list, void* value)
 * inserts the data at front of array-list
 * @param list is a pointer to the list for insertion
 * @param value is the value to be inserted
 * @assert that list and list's array are not NULL
 * @return true if insertion succeeds, false otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.insertBack()
 * bool insertBack(ArrayList* list, void* value)
 * inserts the data at the end of array-list
 * @param list is a pointer to the list for insertion
 * @param value is the value to be inserted
 * @assert that list and list's array are not NULL
 * @return true if insertion succeeds, false otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.removeAt()
 * void* removeAt(ArrayList* list, int index)
 * removes the data at given index in array-list
 * @param list is a pointer to the list for deletion
 * @param index is the index for deletion
 * @assert that list, list's array are not NULL and index is in bound [0...N-1]
 * @return value at given index in array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.removeFront()
 * void* removeFront(ArrayList* list)
 * removes the data at front of array-list
 * @param list is a pointer to the list for deletion
 * @assert that list, list's array are not NULL
 * @return value the front value of array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.removeBack()
 * void* removeBack(ArrayList* list)
 * removes the data at end of array-list
 * @param list is a pointer to the list for deletion
 * @assert that list, list's array are not NULL
 * @return value the end value of array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.remove()
 * bool remove(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKey)
 * removes the 1st occurrence of key in array-list (if any)
 * @param list is a pointer to the list for deletion
 * @param key is the search key for deletion
 * @param comparator defined in types.h - defines how the values in array-list are to be compared
 * @param freeKeyAtEnd if set to true frees the memory allocated to key after performing search
 * @param freeListKey if set to true frees the memory allocated to item in array-list for item matching key
 * @assert that list, list's array and comparator are not NULL
 * @return true if deletion succeeds; false otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.removeAll()
 * int removeAll(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKey)
 * removes all occurrence(s) of key in array-list (if any)
 * @param list is a pointer to the list for deletion
 * @param key is the search key for deletion
 * @param comparator defined in types.h - defines how the values in array-list are to be compared
 * @param freeKeyAtEnd if set to true frees the memory allocated to key after performing search
 * @param freeListKey if set to true frees the memory allocated to item in array-list for item matching key
 * @assert that list, list's array and comparator are not NULL
 * @return count of items deleted from array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.contains()
 * bool contains(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd)
 * search for key in array-list where search pattern is defined by comparator
 * @param list is a pointer to the list for searching
 * @param key is the search key
 * @param comparator defined in types.h - defines how the values in array-list are to be compared
 * @param freeKeyAtEnd if set to true frees the memory allocated to key after performing search
 * @assert list, list's array and comparator are not NULL
 * @return true if key exist in array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.indexOf()
 * int indexOf(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd)
 * search for key in array-list where search pattern is defined by comparator
 * @param list is a pointer to the list for searching
 * @param key is the search key
 * @param comparator defined in types.h - defines how the values in array-list are to be compared
 * @param freeKeyAtEnd if set to true frees the memory allocated to key after performing search
 * @assert list, list's array and comparator are not NULL
 * @return index of 1st occurrence of key in array-list if exist; -1 otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.get()
 * void* get(ArrayList* list, int index)
 * fetches the value at given index in array-list
 * @param list is a pointer to the list
 * @param index to get the value from
 * @assert that list, list's array are not NULL and index is in range [0...N-1]
 * @return value at given index in array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.set()
 * void* set(ArrayList* list, int index, void* value)
 * update the value at given index in array-list
 * @param list is a pointer to the list
 * @param index to set the value for
 * @param value is the new value for given index
 * @assert that list, list's array are not NULL and index is in range [0...N-1]
 * @return old value at given index in array-list
 * @added in release@2020.2
 *
 *
 * ArrayListMethods.front()
 * void* front(ArrayList* list)
 * fetches the first value in array-list
 * @param list is a pointer to the list
 * @assert that list, list's array are not NULL
 * @return first value in array-list if exist; NULL otherwise
 * @deprecated in release@2020.2
 *
 *
 *
 * ArrayListMethods.back()
 * void* back(ArrayList* list)
 * fetches the last value in array-list
 * @param list is a pointer to the list
 * @assert that list, list's array are not NULL
 * @return last value in array-list if exist; NULL otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.isEmpty()
 * bool isEmpty(ArrayList* list)
 * checks if list is empty
 * @param list is a pointer to the list
 * @assert that list and list's array are not NULL
 * @return true if list is empty; false otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.size()
 * int size(ArrayList* list)
 * fetches the size of the list
 * @param list is a pointer to the list
 * @assert that list and list's array are not NULL
 * @return size of the array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.capacity()
 * int capacity(ArrayList* list)
 * fetches the capacity of the list
 * @param list is a pointer to the list
 * @assert that list and list's array are not NULL
 * @return capacity of the array-list
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.equals()
 * bool equals(ArrayList* list1, ArrayList* list2, Comparator comparator)
 * compares the content of two array-list where comparison is defined by comparator
 * @param list1 is a pointer to the first list
 * @param list2 is a pointer to the second list
 * @param comparator defined in types.h - defines how the content of two array list is to be compared
 * @assert list1, list2, list1's, list2's array and comparator are not NULL
 * @return true if both array-list has same content; false otherwise
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.reverse()
 * void reverse(ArrayList* list)
 * reverses the content of array-list
 * @param list is a pointer to the list
 * @assert list and list's array are not NULL
 * @return nothing
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.sort()
 * bool sort(ArrayList* list, Comparator comparator)
 * sorts the content of list using MERGE-SORT based on comparison defined by comparator
 * @param list is a pointer to the list
 * @param comparator defined in types.h - defines how the content of list to be compared for sorting
 * @return true if sort succeeds; false otherwise
 * @assert that list, list's array and comparator are not NULL
 * @deprecated in release@2020.2
 *
 *
 *
 * ArrayListMethods.clear()
 * void clear(ArrayList* list, bool freeKeys)
 * clears the content of array-list
 * @param list is a pointer to the list
 * @param freeKeys if set to true frees the memory allocated to keys in array-list
 * @assert that list and list's array are not NULL
 * @return nothing
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.free()
 * void free(ArrayList* list, bool freeKeys)
 * clears the content of array-list and frees list
 * @param list is a pointer to the list
 * @param freeKeys if set to true frees the memory allocated to keys in array-list
 * @assert that list and list's array are not NULL
 * @return nothing
 * @deprecated in release@2020.2
 *
 *
 *
 * ArrayListMethods.iterator()
 * ArrayListIterator* iterator(ArrayList* list)
 * creates a new iterator for traversing array-list
 * @param list is a pointer to the list
 * @assert that list and list's array are not NULL
 * @return a pointer to newly created iterator associated with given list if succeeds; NULL otherwise
 * @added in release@2020.2
 *
 *
 * ArrayListMethods.begin()
 * void begin(ArrayListIterator* iterator)
 * resets the iterator to point to the 1st node in list
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL
 * @return nothing
 * @added in release@2020.2
 *
 *
 * ArrayListMethods.end()
 * void end(ArrayListIterator* iterator)
 * resets the iterator to point to the last node in list
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL
 * @return nothing
 * @added in release@2020.2
 *
 *
 * ArrayListMethods.hasNext()
 * bool hasNext(ArrayListIterator* iterator)
 * checks if iterator can move to next node w.r.t current node
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL
 * @return true if iterator can moe to next node w.r.t current node
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.hasPrev()
 * bool hasPrev(ArrayListIterator* iterator)
 * checks if iterator can move to previous node w.r.t current node
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL
 * @return true if iterator can moe to previous node w.r.t current node
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.next()
 * void* next(ArrayListIterator* iterator)
 * moves the iterator to next node w.r.t current node
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL and iterator has next node
 * @return value of current node
 * @deprecated in release@2020.2
 *
 *
 *
 * ArrayListMethods.prev()
 * void* prev(ArrayListIterator* iterator)
 * moves the iterator to previous node w.r.t current node
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL and iterator has previous node
 * @return value of current node
 * @deprecated in release@2020.2
 *
 *
 * ArrayListMethods.freeIterator()
 * void freeIterator(ArrayListIterator* iterator)
 * moves the iterator to previous node w.r.t current node
 * @param iterator is a pointer to iterator
 * @assert that iterator, iterator's list and iterator's list's array are not NULL
 * @return nothing
 * @deprecated in release@2020.2
 *
 * */

#endif
