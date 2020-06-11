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

#ifndef UTILITY_TREESET_H
#define UTILITY_TREESET_H

/*include source file*/
#include "definitions/treeset.c"
#include <stdbool.h>


/*creates a new TreeSet and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.2*/
extern TreeSet* new_tree_set(void);

/*add/overwrites the given data to set*/
/*asserts that tree-set, comparator are not NULL*/
/*since release@2020.2*/
extern void tree_set_add(TreeSet* treeSet, void* data, Comparator comparator);

/*add the given data to set if not already present*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
extern void tree_set_add_if_not_present(TreeSet* treeSet, void* data, Comparator comparator);

/*returns and removes the minimum data in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern void* tree_set_remove_min(TreeSet* treeSet);

/*returns and removes the maximum data in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern void* tree_set_remove_max(TreeSet* treeSet);

/*returns and removes the given data from set if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
extern void* tree_set_remove(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd);


/*returns the size of tree set i.e. number of elements in tree set*/
/*asserts that tree set is not NULL*/
/*since release@2020.2*/
extern int tree_set_size(TreeSet* treeSet);

/*returns true if tree-set is empty otherwise returns false*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern bool tree_set_is_empty(TreeSet* treeSet);

/*returns true if set contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
extern bool tree_set_contains(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the node containing given key if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
extern void* tree_set_get(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the data containing given key if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*since release@2020.2*/
/*asserts that tree set and comparator are not NULL*/
void* tree_set_search(TreeSet* treeSet, void* searchKey, Comparator comparator, bool freeKeyAtEnd);

/*returns the floor of given key in set if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
extern void* tree_set_floor(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the ceil of given key in set if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
extern void* tree_set_ceil(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the minimum element in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern void* tree_set_min(TreeSet* treeSet);

/*returns the maximum element in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern void* tree_set_max(TreeSet* treeSet);

/*returns the content of set as a linked list if succeeds otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern LinkedList* tree_set_keys(TreeSet* treeSet);


/*returns the content of set in sorted order as linked list if succeeds otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
LinkedList* tree_set_sorted_keys(TreeSet* treeSet);

/*frees the memory allocated to tree-set*/
/*optionally free the memory allocated to keys in set*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
extern void free_tree_set(TreeSet* treeSet, bool freeKeys);

#endif