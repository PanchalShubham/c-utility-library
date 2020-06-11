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

#ifndef UTILITY_RBT_H
#define UTILITY_RBT_H

/*include source file*/
#include "definitions/rbt.c"
#include <stdbool.h>

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
#include <stdbool.h>
#include <assert.h>
#include "linkedlist.h"

/*allocates memory for a new RBT and return a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.2*/
extern RBT* new_rbt(void);

/*adds data to rbt if doesn't exist; if exist then optionally overwrites the data*/
/*returns true if succeeds otherwise returns false*/
/*asserts that rbt and comparator aren't NULL*/
/*since release@2020.2*/
extern bool rbt_put(RBT* rbt, void* data, Comparator comparator, bool overwrite);


/*returns the keys in rbt in a linked list if succeeds otherwise returns NULL*/
/*assert that rbt is not NULL*/
/*since release@2020.2*/
extern LinkedList* rbt_keys(RBT* rbt);

/*returns the keys in the rbt in sorted order as linked list if succeeds otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern LinkedList* rbt_sorted_keys(RBT* rbt);


/*returns the size of the rbt*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern int rbt_size(RBT* rbt);

/*returns true if rbt is empty otherwise returns false*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern bool rbt_is_empty(RBT* rbt);

/*returns the height of the rbt*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern int rbt_height(RBT* rbt);

/*returns the minimum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern void* rbt_min(RBT* rbt);

/*returns the maximum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern void* rbt_max(RBT* rbt);

/*returns the floor of given key in rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of operation*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
extern void* rbt_floor(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the ceil of given key in rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of operation*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
extern void* rbt_ceil(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns the rank of given key in rbt if exist otherwise returns -1*/
/*rank := number of nodes in tree that less than given node*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
extern int rbt_rank(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd);




/*returns the data that matches key in rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of the search*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
extern void* rbt_value(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns true if rbt contains given key*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
extern bool rbt_contains(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd);




/*returns and removes the minimum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern void* rbt_remove_min(RBT* rbt);

/*returns and removes the maximum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern void* rbt_remove_max(RBT* rbt);

/*returns and removes the key from rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of the operation*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
extern void* rbt_remove(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd);



/*frees the memory allocated to rbt*/
/*optionally frees the memory allocated to its nodes*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
extern void free_rbt(RBT* rbt, bool freeKeys);

#endif