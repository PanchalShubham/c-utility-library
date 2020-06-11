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

#ifndef UTILITY_STACK_H
#define UTILITY_STACK_H

/*include source file*/
#include "definitions/stack.c"
#include <stdbool.h>

/*creates a new empty stack and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
extern Stack* new_stack(void);


/*pushes data to stack and returns true if succeeds otherwise returns false*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern bool stack_push(Stack* stack, void* value);


/*returns and remove the top element from stack if exist otherwise returns NULL*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern void* stack_pop(Stack* stack);

/*returns but NOT remove the top element from stack if exist otherwise returns NULL*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern void* stack_peek(Stack* stack);


/*returns true if stack is empty otherwise returns false*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern bool stack_is_empty(Stack* stack);

/*returns the size of the stack*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern int stack_size(Stack* stack);


/*returns the index of key from top of the stack if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that stack and callback aren't NULL*/
/*since release@2020.1*/
extern int stack_indexOf(Stack* stack, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns true if stack contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that stack and callback aren't NULL*/
/*since release@2020.1*/
extern bool stack_contains(Stack* stack, void* key, Comparator comparator, bool freeKeyAtEnd);


/*returns true if content of both stack are same otherwise returns false*/
/*asserts that neither of the stack is NULL and callback is not NULL*/
/*since release@2020.1*/
extern bool stack_equals(Stack* stack1, Stack* stack2, Comparator comparator);

/*resets the content of stack i.e. empty stack*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern void reset_stack(Stack* stack, bool freeKeysInStack);

/*frees the memory allocated to stack*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
extern void free_stack(Stack* stack, bool freeKeysInStack);





/*creates a new  stack iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that stack is not NULL*/
/*since release@2020.1*/
extern StackIterator* new_stack_iterator(Stack* stack);

/*checks if  stack iterator has a next node*/
/*assert that stack iterator is not NULL*/
/*since release@2020.1*/
extern bool stack_iterator_has_next(StackIterator* iterator);

/*point stack iterator to its next node and returns the value contained in current node*/
/*assert that stack iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
extern void* stack_iterator_next(StackIterator* iterator);

/*resets the stack iterator to point to 1st node*/
/*asserts that stack iterator and its associated stack are not NULL*/
/*since release@2020.1*/
extern void reset_stack_iterator(StackIterator* iterator);

/*frees the memory allocated to iterator*/
/*asserts that stack iterator is not NULL*/
/*since release@2020.1*/
extern void free_stack_iterator(StackIterator* iterator);


#endif