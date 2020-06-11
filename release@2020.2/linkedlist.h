
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



#ifndef UTILITY_LINKEDLIST_H
#define UTILITY_LINKEDLIST_H

/*include types for lists from utility types*/
#include "types.h"
/*include source file*/
#include "definitions/linkedlist.c"
/*include stdbool for boolean types*/
#include <stdbool.h>

/*creates an empty LinkedList and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
extern LinkedList* new_linked_list(void);

/*inserts value at given index in LinkedList and returns true if succeeds otherwise returns false*/
/*indexing begins from zero so available indices are [0...N] where index N marks insert at end*/
/*asserts that list is not NULL and index is in bound*/
/*since release@2020.1*/
extern bool linked_list_insert_at(LinkedList* list, void* value, int index);

/*inserts data at the front of LinkedList and returns true if succeeds otherwise returns false*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
extern bool linked_list_insert_front(LinkedList* list, void* value);

/*inserts data at the back of LinkedList and returns true if succeeds otherwise returns false*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
extern bool linked_list_insert_back(LinkedList* list, void* value);







/*deletes the data at given index in LinkedList and returns the value at that index if succeds otherwise returns NULL*/
/*asserts that LinkedList is not NULL and index is in bound [0...N-1]*/
/*since release@2020.1*/
extern void* linked_list_delete_at(LinkedList* list, int index);

/*deletes the front element of the list and returns the value in it; if list is empty returns NULL*/
/*assert that LinkedList is not NULL*/
/*since release@2020.1*/
extern void* linked_list_delete_front(LinkedList* list);

/*deletes the last element of the list and returns the value in it; if list is empty returns NULL*/
/*assert that LinkedList is not NULL*/
/*since release@2020.1*/
extern void* linked_list_delete_back(LinkedList* list);

/*deletes the 1st occurrence of key in LinkedList if exist and returns true otherwise returns false*/
/*optionally frees the memory allocated to key and value in node*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
extern bool linked_list_delete(LinkedList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKey);

/*deletes all occurrence of key in LinkedList and returns the count of items being deleted*/
/*optionally frees the memory allocated to key and value in nodes*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
extern int linked_list_delete_all(LinkedList* list, void* key, Comparator comparator, bool freeKey, bool freeListKeys);







/*returns true if key exist in LinkedList otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
extern bool linked_list_contains(LinkedList* list, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the index of 1st occurrence of key in list if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
extern int linked_list_indexOf(LinkedList* list, void* key, Comparator comparator, bool freeKeyAtEnd);


/*returns the value at given index in LinkedList*/
/*asserts that LinkedList is not NULL and  index is in range [0...N-1] where N is size of list*/
/*since release@2020.1*/
extern void* linked_list_value_at(LinkedList* list, int index);

/*returns the value at front end of LinkedList if exist otherwise returns NULL*/
/*asserts that input LinkedList is not NULL and is not empty*/
/*since release@2020.1*/
extern void* linked_list_front(LinkedList* list);

/*returns the value at back end of LinkedList if exist otherwise returns NULL*/
/*asserts that input LinkedList is not NULL and is not empty*/
/*since release@2020.1*/
extern void* linked_list_back(LinkedList* list);

/*returns true if LinkedList is empty otherwise returns false*/
/*asserts that input LinkedList is not NULL*/
/*since release@2020.1*/
extern bool linked_list_is_empty(LinkedList* list);


/*returns the size of the LinkedList*/
/*asserts that input LinkedList is not NULL*/
/*since release@2020.1*/
extern int linked_list_size(LinkedList* list);

/*returns true if value contained in both LinkedLists are equal otherwise returns false*/
/*asserts the list and callback aren't NULL*/
/*since release@2020.1*/
extern bool linked_list_equals(LinkedList* list1, LinkedList* list2, Comparator comparator);

/*reverses the content of list*/
/*asserts that input list is not NULL*/
/*since release@2020.1*/
extern void linked_list_reverse(LinkedList* list);

/*sorts the content of LinkedList using merge_sort and returns true if succeeds otherwise returns false*/
/*asserts that list and callback aren't NULL*/
/*since release@2020.1*/
extern bool linked_list_sort(LinkedList* list, Comparator comparator);






/*clear the list i.e. deletes all nodes in list*/
/*optionally frees the memory allocated to value in nodes*/
/*asserts that input list is not NULL*/
/*since release@2020.1*/
extern void clear_linked_list(LinkedList* list, bool freeListKeys);

/*frees the memory allocated to all nodes in list and list*/
/*optionally frees the memory allocated to value in nodes*/
/*asserts that input list is not NULL*/
/*since release@2020.1*/
extern void free_linked_list(LinkedList* list, bool freeListKeys);






/*creates an iterator for LinkedList pointing to 1st node*/
/*returns a pointer to LinkedList iterator if succeeds otherwise returns a NULL pointer*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
extern LinkedListIterator* new_linked_list_iterator(LinkedList* list);

/*creates an iterator for LinkedList pointing to last node*/
/*returns a pointer to LinkedList iterator if succeeds otherwise returns a NULL pointer*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
extern LinkedListIterator* new_linked_list_reverse_iterator(LinkedList* list);


/*returns true if LinkedList iterator has a next node otherwise returns false*/
/*assert that input iterator is not NULL*/
/*since release@2020.1*/
extern bool linked_list_iterator_has_next(LinkedListIterator* iterator);

/*returns true if LinkedList iterator has a previous node otherwise returns false*/
/*assert that input iterator is not NULL*/
/*since release@2020.1*/
extern bool linked_list_iterator_has_previous(LinkedListIterator* iterator);

/*sets the iterator to point to next node and returns the value of  the current node*/
/*asserts that iterator is not NULL and has a next node*/
/*since release@2020.1*/
extern void* linked_list_iterator_next(LinkedListIterator* iterator);

/*sets the iterator to point to previous node and returns the value of the current node*/
/*asserts that iterator is not NULL and has a next node*/
/*since release@2020.1*/
extern void* linked_list_iterator_previous(LinkedListIterator* iterator);

/*resets the iterator to appropriate node*/
/*asserts that input iterator is not NULL*/
/*since release@2020.1*/
extern void reset_linked_list_iterator(LinkedListIterator* iterator);

/*frees the memory allocated to iterator*/
/*asserts that input iterator is not NULL*/
/*since release@2020.1*/
extern void free_linked_list_iterator(LinkedListIterator* iterator);

#endif