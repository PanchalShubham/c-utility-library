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

/*declaration of structure  stack node*/
typedef struct stack_node{
    /*each node has a value*/
    void* value;
    /*each node has address of its next node*/
    struct stack_node* bottom;
}stack_node;

/*declaration of structure  stack*/
typedef struct Stack{
    /*each stack has an address of its top node*/
    stack_node* top;
    /*each stack has a size*/
    int size;
}Stack;

/*declaration of structure  stack iterator*/
typedef struct StackIterator{
    /*each  stack iterator has an associated stack*/
    Stack* forStack;
    /*each  stack iterator has address of current node*/
    stack_node* currentNode;
}StackIterator;


/*creates a new empty stack and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
Stack* new_stack(void){
    /*allocate memory for new  stack*/
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    /*validate memory allocation*/
    if (stack != NULL){
        /*update fields of stack*/
        stack->top = NULL;
        stack->size= 0;
    }
    /*return newly created stack*/
    return stack;
}


/*pushes data to stack and returns true if succeeds otherwise returns false*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
bool stack_push(Stack* stack, void* value){
    /*make an assertion on  stack*/
    assert (stack != NULL);
    /*allocate memory for new node*/
    stack_node* node = (stack_node*)malloc(sizeof(stack_node));
    /*validate memory allocation*/
    if (node != NULL){
        /*update fields of node*/
        node->value = value; node->bottom = NULL;
        /*update next of node*/
        node->bottom = stack->top;
        /*update top of stack*/
        stack->top = node;
        /*increase size of stack by 1*/
        stack->size++;
        /*return true as insertion succeeded*/
        return true;
    } else {
        /*failed to allocate memory for new node and hence failed to insert*/
        return false;
    }
}


/*returns and remove the top element from stack if exist otherwise returns NULL*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
void* stack_pop(Stack* stack){
    /*make an assertion on stack*/
    assert (stack != NULL);
    /*check if stack is empty*/
    if (stack->top != NULL){
        /*get the top of the stack*/
        stack_node* topNode = stack->top;
        /*update stack's top*/
        stack->top = stack->top->bottom;
        /*decrease the size of the stack by 1*/
        stack->size--;
        /*take a copy of value to be returned*/
        void* returnValue = topNode->value;
        /*free memory allocated to topNode*/
        free (topNode);
        /*return the value of topNode*/
        return returnValue;
    } else {
        /*nothing to delete in stack*/
        return NULL;
    }
}


/*returns but NOT remove the top element from stack if exist otherwise returns NULL*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
void* stack_peek(Stack* stack){
    /*make an assertion on stack*/
    assert (stack != NULL);
    /*return the value of top element of stack if exist*/
    return (stack->top != NULL ? stack->top->value : NULL);
}


/*returns true if stack is empty otherwise returns false*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
bool stack_is_empty(Stack* stack){
    /*make an assertion on input stack*/
    assert (stack != NULL);
    /*return result appropriately*/
    return (stack->top == NULL);
}

/*returns the size of the stack*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
int stack_size(Stack* stack){
    /*make an assertion on input stack*/
    assert (stack != NULL);
    /*return result appropriately*/
    return stack->size;
}


/*returns the index of key from top of the stack if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that stack and callback aren't NULL*/
/*since release@2020.1*/
int stack_indexOf(Stack* stack, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on stack*/
    assert (stack != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*stores the index of key in stack*/
    int index = 0;
    /*iterate through stack and search for key*/
    stack_node* temp = stack->top;
    while (temp != NULL){
        /*compare current node's value with key*/
        if ( (*comparator)(temp->value, key) == 0){
            /*key found - now check if user opted for free key*/
            if (freeKeyAtEnd && temp->value != NULL)
                free (key);
            /*return the index*/
            return index;
        }
        /*fetch next node*/
        temp = temp->bottom;
        /*increase the index by 1*/
        index++;
    }
    /*couldn't find key in stack*/
    return -1;
}

/*returns true if stack contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that stack and callback aren't NULL*/
/*since release@2020.1*/
bool stack_contains(Stack* stack, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*check if index is not -1*/
    return stack_indexOf(stack, key, comparator, freeKeyAtEnd) != -1;
}



/*returns true if content of both stack are same otherwise returns false*/
/*asserts that neither of the stack is NULL and callback is not NULL*/
/*since release@2020.1*/
bool stack_equals(Stack* stack1, Stack* stack2, Comparator comparator){
    /*make an assertion on both stacks*/
    assert (stack1 != NULL && stack2 != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*first compare the size of the stack*/
    if (stack1->size != stack2->size)
        return false;
    /*iterate through both stack and compare data*/
    stack_node *temp1 = stack1->top, *temp2 = stack2->top;
    while (temp1 != NULL && temp2 != NULL){
        /*compare values of current nodes*/
        if ( (*comparator)(temp1->value, temp2->value) != 0)
            /*mismatch*/
            return false;
        /*fetch next nodes*/
        temp1 = temp1->bottom; temp2 = temp2->bottom;
    }

    /*everything matched we return true*/
    return true;
}

/*resets the content of stack i.e. empty stack*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
void reset_stack(Stack* stack, bool freeKeysInStack){
    /*make an assertion on input stack*/
    assert (stack != NULL);
    /*iterate through all nodes in stack and free memory*/
    stack_node *temp = stack->top, *ptr = NULL;
    while (temp != NULL){
        /*check if value to be freed*/
        if (freeKeysInStack && temp->value != NULL)
            free (temp->value);
        /*take a copy of current node*/
        ptr = temp;
        /*fetch next node*/
        temp = temp->bottom;
        /*free memory allocated to current node*/
        free (ptr);
    }
    /*update the fields of the stack*/
    stack->top = NULL;
    stack->size = 0;
}

/*frees the memory allocated to stack*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that stack is not NULL*/
/*since release@2020.1*/
void free_stack(Stack* stack, bool freeKeysInStack){
    /*make an assertion on input stack*/
    assert (stack != NULL);
    /*reset the content of stack*/
    reset_stack(stack, freeKeysInStack);
    /*free memory allocated to stack*/
    free (stack);
}






/*creates a new  stack iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that stack is not NULL*/
/*since release@2020.1*/
StackIterator* new_stack_iterator(Stack* stack){
    /*make an assertion on  stack*/
    assert (stack != NULL);
    /*allocate memory for new  stack iterator*/
    StackIterator* iterator = (StackIterator*)malloc(sizeof(StackIterator));
    /*validate memory allocation*/
    if (iterator != NULL){
        /*update fields of stack*/
        iterator->forStack = stack;
        iterator->currentNode = stack->top;
    }
    /*return newly created stack iterator*/
    return iterator;
}


/*checks if  stack iterator has a next node*/
/*assert that stack iterator is not NULL*/
/*since release@2020.1*/
bool stack_iterator_has_next(StackIterator* iterator){
    /*make an assertion on stack iterator*/
    assert (iterator != NULL);
    /*return an appropriate result*/
    return (iterator->currentNode != NULL);
}

/*point stack iterator to its next node and returns the value contained in current node*/
/*assert that stack iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
void* stack_iterator_next(StackIterator* iterator){
    /*make an assertion on stack iterator*/
    assert (iterator != NULL && iterator->currentNode != NULL);
    /*take a copy of value to be returned*/
    void* returnValue = iterator->currentNode->value;
    /*point iterator to next node*/
    iterator->currentNode = iterator->currentNode->bottom;
    /*return an appropriate result*/
    return returnValue;
}

/*resets the stack iterator to point to 1st node*/
/*asserts that stack iterator and its associated stack are not NULL*/
/*since release@2020.1*/
void reset_stack_iterator(StackIterator* iterator){
    /*make an assertion on stack iterator*/
    assert (iterator != NULL);
    /*make an assertion on stack*/
    assert (iterator->forStack != NULL);
    /*update the fields of iterator*/
    iterator->currentNode = iterator->forStack->top;
}

/*frees the memory allocated to iterator*/
/*asserts that stack iterator is not NULL*/
/*since release@2020.1*/
void free_stack_iterator(StackIterator* iterator){
    /*make an assertion on stack iterator*/
    assert (iterator != NULL);
    /*free memory allocated to iterator*/
    free (iterator);
}