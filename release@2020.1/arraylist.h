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




/*allocates memory for new ArrayList with initial capacity*/
/*returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that initial capacity is a positive integer*/
/*since release@2020.1*/
extern ArrayList* new_array_list(int initial_capacity);

/*inserts the value at given index in ArrayList shifting the values to right*/
/*resize the array if needed (to double size - if possible)*/
/*asserts that list, list's array aren't NULL and index is in bound [0...N]*/
/*insertion at index N => append operation*/
/*returns true if operation succeeds otherwise returns false*/
/*since release@2020.1*/
extern bool array_list_insert_at(ArrayList* list, void* value, int index);

/*inserts the value at front of the ArrayList and returns true if succeeds otherwise returns false*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
extern bool array_list_insert_front(ArrayList* list, void* value);

/*inserts the value at back of the ArrayList and returns true if succeeds otherwise returns false*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
extern bool array_list_insert_back(ArrayList* list, void* value);

/*deletes the value at given index and returns value contained if succeeds otherwise returns NULL*/
/*asserts that list, list's array are not NULL and index is in bound [0...N-1]*/
/*since release@2020.1*/
extern void* array_list_delete_at(ArrayList* list, int index);

/*returns and deletes the value at front if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
extern void* array_list_delete_front(ArrayList* list);

/*returns and deletes the value at end if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
extern void* array_list_delete_back(ArrayList* list);

/*deletes the 1st occurrence of key in ArrayList, returns true if deletion succeeds otherwise returns false*/
/*optionally frees the memory for deleted element*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
extern bool array_list_delete(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKey);

/*deletes all occurrences of key in ArrayList, returns count of deleted items*/
/*optionally frees the memory for deleted element*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
extern int array_list_delete_all(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKeys);

/*returns true if key exist in ArrayList otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
extern bool array_list_contains(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the index of 1st occurrence of key in ArrayList if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
extern int array_list_indexOf(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd);


/*returns the value at given index in ArrayList*/
/*asserts that list, list's array are not NULL and index is in bound [0...N - 1]*/
/*since release@2020.1*/
extern void* array_list_value_at(ArrayList* list, int index);

/*returns the front item of the array list if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
extern void* array_list_front(ArrayList* list);

/*returns the last item of the array list if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
extern void* array_list_back(ArrayList* list);

/*returns true if ArrayList is empty otherwise returns false*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
extern bool array_list_is_empty(ArrayList* list);

/*returns the size of the ArrayList*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
extern int array_list_size(ArrayList* list);

/*returns the capacity of the array list*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
extern int array_list_capacity(ArrayList* list);


/*returns true if both array list contains same elements - ignores difference in capacity (if any)*/
/*asserts that lists, lists's arrays and callback aren't NULL*/
/*since release@2020.1*/
extern bool array_list_equals(ArrayList* list1, ArrayList* list2, Comparator comparator);

/*reverses the content of array list*/
/*asserts that list, list's array aren't NULL*/
/*since release@2020.1*/
extern void array_list_reverse(ArrayList* list);

/*sorts the array list using merge sort algorithm*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
extern bool array_list_sort(ArrayList* list, Comparator comparator);

/*clear the content of array list and optionally frees the memory allocated to keys*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
extern void clear_array_list(ArrayList*  list, bool free_key);

/*frees the memory allocate to array list and optionally frees the memory allocated to keys*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
extern void free_array_list(ArrayList*  list, bool free_key);

/*returns an iterator for array list pointing to 1st node if succeeds otherwise returns NULL*/
/*asserts that array list is not NULL*/
/*since release@2020.1*/
extern ArrayListIterator* new_array_list_iterator(ArrayList* list);

/*returns a pointer to an iterator for ArrayList pointing to last node if succeeds otherwise returns NULL*/
/*assert that array list is not NULL*/
/*since release@2020.1*/
extern ArrayListIterator* new_array_list_reverse_iterator(ArrayList* list);

/*checks if array list iterator has a value*/
/*assert that iterator and iterator's list are not NULL*/
/*since release@2020.1*/
extern bool array_list_iterator_has_next(ArrayListIterator* iterator);

/*checks if array list iterator has a value*/
/*assert that iterator and iterator's list are not NULL*/
/*since release@2020.1*/
extern bool array_list_iterator_has_previous(ArrayListIterator* iterator);

/*returns the value of current node and update iterator to previous node*/
/*asserts that iterator, iterator's list, iterator's list's array are not NULL and iterator's current current node is not  NULL*/
/*since release@2020.1*/
extern void* array_list_iterator_next(ArrayListIterator* iterator);

/*returns the value of current node and update iterator to previous node*/
/*asserts that iterator, iterator's list, iterator's list's array are not NULL and iterator's current current node is not  NULL*/
/*since release@2020.1*/
extern void* array_list_iterator_previous(ArrayListIterator* iterator);

/*resets the iterator to appropriate node*/
/*asserts that iterator, iterator's list are not NULL*/
/*since release@2020.1*/
extern void reset_array_list_iterator(ArrayListIterator* iterator);

/*frees the memory allocated to iterator*/
/*asserts that input iterator is not NULL*/
/*since release@2020.1*/
extern void free_array_list_iterator(ArrayListIterator* iterator);




#endif
