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

/*include types for lists from utility types*/
#include "../types.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

/*declaration of structure LinkedList*/
typedef struct ArrayList{
    /*each array list has an array of objects*/
    void** array;
    /*each array list has a size*/
    int size;
    /*each array list has a capacity*/
    int capacity;
}ArrayList;

/*declaration of array list iterator*/
typedef struct ArrayListIterator{
    /*each list iterator has its associated list*/
    ArrayList* for_list;
    /*each list iterator has current node index*/
    int current_node_index;
    /*each list iterator has a type i.e. normal or reverse iterator*/
    bool is_reverse_iterator;
}ArrayListIterator;




/*updates the capacity of array list i.e. shrinks size if needed*/
/*assert that list and list's array aren't NULL*/
/*since release@2020.1*/
static void array_list_shrink(ArrayList* list){
    /*make an assertion on list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*get the capacity of the list*/
    int capacity = list->capacity ;
    /*get the size of the list*/
    int size = list->size;
    /*check what percent of list is filled*/
    double percent_filled = ( (double)size/ capacity)*100.0;
    /*if list is at most 25% filled - we can shrink*/
    if (percent_filled <= 25.0){
        /*we can shrink the capacity*/
        /*allocate memory for half of the capacity of list*/
        void** array = (void**)malloc(sizeof(void*)*(capacity / 2));
        /*validate memory allocation*/
        if (array != NULL){
            /*get copy of array of list*/
            void** old_array = list->array;
            /*copy original list's content to new array*/
            for (int i = 0; i < size; ++i)
                array[i] = old_array[i];
            /*free memory allocated to all arrays*/
            free (old_array);
            /*update array of list*/
            list->array = array;
            /*update capacity of list*/
            list->capacity = capacity / 2;
        }
    }
}



/*deletes the occurrence of key in array list and returns the count of deleted elements*/
/*optionally frees the memory for deleted element*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
static int actual_array_list_delete(ArrayList* list, void* key, Comparator comparator, bool delete_multiple, bool free_key, bool free_list_keys){
    /*make an assertion on list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*stores the count of number of keys deleted*/
    int count = 0;
    /*take a copy of list's array*/
    void** array = list->array;
    /*take a copy of size of list*/
    int size = list->size;
    /*iterate through list and delete elements*/
    /*using list's size because*/
    for (int i = 0; i < size; ++i){
        /*compare ith element of list with key*/
        if ((*comparator)(array[i], key) == 0){
            /*check if multiple instances to be deleted*/
            if (count == 0 || (count > 0 && delete_multiple)){
                /*free memory allocated to keys if needed*/
                if (free_list_keys && array[i] != NULL)
                    free (array[i]);
                /*start from given index and pull elements to left*/
                for (int j = i; j < size - 1; ++j)
                    array[j] = array[j + 1];
                /*decrease the size of the list by 1*/
                size--;
                /*decrease value of i by 1*/
                --i;
                /*increase the count of deleted items by 1*/
                count++;
            } else {
                /*we do not want to delete and hence we break loop*/
                break;
            }
        }
    }
    /*update the size of the list*/
    list->size = size;
    /*shrink the capacity of list*/
    array_list_shrink(list);
    /*check if user opted for deleting key*/
    if (free_key && key != NULL)
        free (key);
    /*return the count of number of elements deleted*/
    return count;
}


/*returns the index of 1st occurrence of key in list if exist otherwise returns -1*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
static int actual_array_list_contains(ArrayList* list, void* key, Comparator compare_callback, bool free_key){
    /*make an assertion on array list*/
    assert (list != NULL);
    /*make an assertion on array of array list*/
    assert (list->array != NULL);
    /*make an assertion on compare callback*/
    assert (compare_callback != NULL);
    /*get the size of the list*/
    int size = list->size;
    /*get the array of the list*/
    void** array = list->array;
    /*iterate through list and search for key*/
    for (int i = 0; i < size; ++i)
        if ( (*compare_callback)(array[i], key) == 0) {
            /*check if memory allocated to key is to be freed*/
            if (free_key && key != NULL)
                free (key);
            /*key found return its index*/
            return i;
        }
    /*check if memory allocated to key is to be freed*/
    if (free_key && key != NULL)
        free (key);
    /*key does not exist return -1*/
    return -1;
}



/*merges two sorted sub arrays*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
static void array_list_merge(ArrayList* list, int low, int mid, int high, Comparator compare_callback, void** aux_array){
    /*make an assertion on list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*make an assertion on callback*/
    assert (compare_callback != NULL);
    /*copy content to auxiliary array*/
    for (int i = low; i <= high; ++i)
        aux_array[i] = list->array[i];

    /*merge two sorted parts*/
    int i = low, j = mid + 1;
    for (int k = low; k <= high; ++k)
        if (i > mid)        list->array[k] = aux_array[j++];
        else if (j > high)  list->array[k] = aux_array[i++];
        else if ( (*compare_callback)(aux_array[i], aux_array[j]) <= 0) list->array[k] = aux_array[i++];
        else                list->array[k] = aux_array[j++];

}

/*sorts the array list using merge sort algorithm*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
static void array_list_merge_sort(ArrayList* list, int low, int high, Comparator compare_callback, void** aux_array){
    /*check the bounds on array*/
    if (low < high){
        /*split the array into two halves*/
        int mid = (low + high) / 2;
        /*sort left and right sub arrays*/
        array_list_merge_sort(list, low, mid, compare_callback, aux_array);
        array_list_merge_sort(list, mid + 1, high, compare_callback, aux_array);
        /*merge sorted arrays*/
        array_list_merge(list, low, mid, high, compare_callback, aux_array);
    }
}


/*returns a pointer to an iterator for given ArrayList if succeeds otherwise returns NULL*/
/*asserts that array list is not NULL*/
/*since release@2020.1*/
static ArrayListIterator* actual_create_array_list_iterator(ArrayList* list, bool is_reverse_iterator){
    /*make an assertion on linked list*/
    assert (list != NULL);
    /*allocate memory for new array list iterator*/
    ArrayListIterator* iterator = (ArrayListIterator*)malloc(sizeof(ArrayListIterator));
    /*validate memory allocation*/
    if (iterator != NULL){
        /*update list of iterator*/
        iterator->for_list = list;
        /*update type of iterator*/
        iterator->is_reverse_iterator = is_reverse_iterator;
        /*update current node based on iterator type*/
        if (is_reverse_iterator)
            /*reverse iterator starts from tail*/
            iterator->current_node_index = list->size - 1;
        else
            /*normal iterator starts from head*/
            iterator->current_node_index = list->size > 0 ? 0 : -1;
    }
    /*return the newly created iterator*/
    return iterator;
}


/*returns the value of current node and sets the iterator to point to next/previous node*/
/*asserts that iterator, iterator's list, iterator's list's array are not NULL and iterator's current current node is not  NULL*/
/*since release@2020.1*/
static void* array_list_update_iterator(ArrayListIterator* iterator, bool is_reverse_iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*make an assertion on list of input iterator*/
    assert (iterator->for_list != NULL);
    /*make an assertion on array of list iterator*/
    assert (iterator->for_list->array != NULL);
    /*make an assertion on index*/
    assert (0 <= iterator->current_node_index && iterator->current_node_index < iterator->for_list->size);
    /*takes a copy of value to be returned*/
    void* returnValue = iterator->for_list->array[iterator->current_node_index];
    /*point current node to its next/previous node*/
    iterator->current_node_index += is_reverse_iterator ? -1 : 1;
    /*return the value of the current node*/
    return returnValue;
}


















/*allocates memory for new ArrayList with initial capacity*/
/*returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that initial capacity is a positive integer*/
/*since release@2020.1*/
ArrayList* new_array_list(int initial_capacity){
    /*make an assertion on initial capacity*/
    assert (initial_capacity > 0);
    /*allocate memory for new array list*/
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    /*validate memory allocation*/
    if (list != NULL){
        /*allocate memory for initial_capacity integers on heap*/
        void** array = (void**)malloc(sizeof(void*)*initial_capacity);
        /*validate memory allocation*/
        if (array != NULL){
            /*update fields of list*/
            list->size = 0;
            list->array = array;
            list->capacity = initial_capacity;
        }
    }
    /*return newly created list*/
    return list;
}





/*inserts the value at given index in ArrayList shifting the values to right*/
/*resize the array if needed (to double size - if possible)*/
/*asserts that list, list's array aren't NULL and index is in bound [0...N]*/
/*insertion at index N => append operation*/
/*returns true if operation succeeds otherwise returns false*/
/*since release@2020.1*/
bool array_list_insert_at(ArrayList* list, void* value, int index){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on index*/
    assert (0 <= index && index <= list->size);
    /*make an assertion on array of input list*/
    assert (list->array != NULL);
    /*get the old size of the list*/
    int old_size = list->size;
    /*check if list is completely filled*/
    if (old_size == list->capacity){
        /*get the size for new array*/
        int new_size = 2*old_size <= INT_MAX ? 2*old_size : INT_MAX;
        /*allocate memory for new size*/
        void** array = (void**)malloc(sizeof(void*)*new_size);
        /*validate memory allocation*/
        if (array != NULL){
            /*copy original array content to new array*/
            for (int i = 0 ; i < old_size; ++i)
                array[i] = list->array[i];
            /*free memory allocated to previous array*/
            free (list->array);
            /*update array to new array*/
            list->array = array;
            /*update capacity of list*/
            list->capacity = new_size;
        } else {
            /*memory allocation failed - return false*/
            return false;
        }
    }

    /*check if we have to insert at last index*/
    if (index == old_size){
        /*copy value at the end*/
        list->array[old_size] = value;
    } else {
        /*shift values towards right by one index*/
        for (int i = old_size; i > index; --i)
            list->array[i] = list->array[i - 1];
        /*keep value at appropriate index*/
        list->array[index] = value;
    }

    /*increase the size of the list by 1*/
    list->size++;
    /*return true as insertion succeeded*/
    return true;
}

/*inserts the value at front of the ArrayList and returns true if succeeds otherwise returns false*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
bool array_list_insert_front(ArrayList* list, void* value){
    /*insert value at index 0*/
    return array_list_insert_at(list, value, 0);
}

/*inserts the value at back of the ArrayList and returns true if succeeds otherwise returns false*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
bool array_list_insert_back(ArrayList* list, void* value){
    /*make an assertion on array list*/
    assert (list != NULL);
    /*insert value at index list->size*/
    return array_list_insert_at(list, value, list->size);
}









/*deletes the value at given index and returns value contained if succeeds otherwise returns NULL*/
/*asserts that list, list's array are not NULL and index is in bound*/
/*since release@2020.1*/
void* array_list_delete_at(ArrayList* list, int index){
    /*make assertion on input array list*/
    assert (list != NULL);
    /*make assertion on array of input list*/
    assert (list->array != NULL);
    /*make assertion on index*/
    assert ( 0<= index && index < list->size);
    /*get the old size of the list*/
    int size = list->size;
    /*get the array of the list*/
    void** array = list->array;
    /*get the value of the node to be deleted*/
    void* returnValue = list->array[index];
    /*start from given index and pull elements to left*/
    for (int i = 0; i < size - 1; ++i)
        array[i] = array[i + 1];
    /*decrease the size of the list by 1*/
    list->size--;

    /*shrink the capacity of list*/
    array_list_shrink(list);

    /*return the value contained in node*/
    return returnValue;
}


/*returns and deletes the value at front if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
void* array_list_delete_front(ArrayList* list){
    /*assertion on input list*/
    assert (list != NULL);
    /*return an appropriate value*/
    return (list->size == 0 ? NULL : array_list_delete_at(list, 0));
}

/*returns and deletes the value at end if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
void* array_list_delete_back(ArrayList* list){
    /*assertion on input list*/
    assert (list != NULL);
    /*return an appropriate value*/
    return (list->size == 0 ? NULL : array_list_delete_at(list, list->size - 1));
}



/*deletes the 1st occurrence of key in ArrayList, returns true if deletion succeeds otherwise returns false*/
/*optionally frees the memory for deleted element*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
bool array_list_delete(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKey){
    /*return appropriate result*/
    return (actual_array_list_delete(list, key, comparator, false, freeKeyAtEnd, freeListKey) == 1);
}

/*deletes all occurrences of key in ArrayList, returns count of deleted items*/
/*optionally frees the memory for deleted element*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
int array_list_delete_all(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKeys){
    /*return appropriate result*/
    return actual_array_list_delete(list, key, comparator, true, freeKeyAtEnd, freeListKeys);
}













/*returns true if key exist in ArrayList otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
bool array_list_contains(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*check if index != -1*/
    return (actual_array_list_contains(list, key, comparator, freeKeyAtEnd) != -1);
}



/*returns the index of 1st occurrence of key in ArrayList if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
int array_list_indexOf(ArrayList* list, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*return the index of key in array list*/
    return actual_array_list_contains(list, key, comparator, freeKeyAtEnd);
}


/*returns the value at given index in ArrayList*/
/*asserts that list, list's array are not NULL and index is in bound*/
/*since release@2020.1*/
void* array_list_value_at(ArrayList* list, int index){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on index*/
    assert ( 0 <= index && index < list->size);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*return value at given index*/
    return (list->array[index]);
}

/*returns the front item of the array list if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
void* array_list_front(ArrayList* list){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*return appropriate value*/
    return (list->size > 0 ? list->array[0] : NULL);
}

/*returns the last item of the array list if exist otherwise returns NULL*/
/*asserts that list, list's array are not NULL*/
/*since release@2020.1*/
void* array_list_back(ArrayList* list){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*return appropriate value*/
    return (list->size > 0 ? list->array[list->size - 1] : NULL);
}










/*returns true if ArrayList is empty otherwise returns false*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
bool array_list_is_empty(ArrayList* list){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*return appropriate value*/
    return (list->size == 0);
}


/*returns the size of the ArrayList*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
int array_list_size(ArrayList* list){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*return list's size*/
    return list->size;
}

/*returns the capacity of the array list*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
int array_list_capacity(ArrayList* list){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*return list's capacity*/
    return list->capacity;
}


/*returns true if both array list contains same elements - ignores difference in capacity (if any)*/
/*asserts that lists, lists's arrays and callback aren't NULL*/
/*since release@2020.1*/
bool array_list_equals(ArrayList* list1, ArrayList* list2, Comparator comparator){
    /*make an assertion on lists*/
    assert (list1 != NULL && list2 != NULL);
    /*make an assertion on arrays of list*/
    assert (list1->array != NULL && list2->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*check size of list*/
    if (list1->size != list2->size)
        return false;
    /*get the size of the list*/
    int size = list1->size;
    /*get arrays of both lists*/
    void** array1 = list1->array;
    void** array2 = list2->array;
    /*iterate through both lists*/
    for (int i = 0; i < size; ++i)
        /*make a comparison between ith element*/
        if ((*comparator)(array1[i], array2[i]) != 0)
            /*mismatch return false*/
            return false;
    /*all elements matched*/
    return true;
}


/*reverses the content of array list*/
/*asserts that list, list's array aren't NULL*/
/*since release@2020.1*/
void array_list_reverse(ArrayList* list){
    /*make an assertion on list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*get the size of the list*/
    int size = list->size;
    /*get the array of the list*/
    void** array = list->array;
    /*reverse the content of list by swapping*/
    for (int i = 0, j = size - 1; i <= j ; ++i, --j){
        /*swap values at array[i] and array[j]*/
        void* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}





/*sorts the array list using merge sort algorithm*/
/*asserts that list, list's array and callback aren't NULL*/
/*since release@2020.1*/
bool array_list_sort(ArrayList* list, Comparator comparator){
    /*make an assertion on list*/
    assert (list != NULL);
    /*allocate memory for auxiliary array*/
    void** aux_array = (void**)malloc(sizeof(void*)*(list->size));
    /*validate memory allocation*/
    if (aux_array != NULL){
        /*sort array*/
        array_list_merge_sort(list, 0, list->size - 1, comparator, aux_array);
        /*return true as array is sorted*/
        return true;
    } else {
        /*memory allocation failed*/
        return false;
    }
}







/*clear the content of array list and optionally frees the memory allocated to keys*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
void clear_array_list(ArrayList*  list, bool free_key){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*check if memory to be freed for keys*/
    if (free_key){
        /*get the size of the list*/
        int size = list->size;
        /*get the array corresponding to this list*/
        void** array = list->array;
        /*iterate through array list and free memory allocated to all keys*/
        for (int i = 0 ; i < size; ++i)
            if (array[i] != NULL)
                /*free memory allocated to this key*/
                free (array[i]);
    }
    /*reset the value of list*/
    list->size = 0;
}

/*frees the memory allocate to array list and optionally frees the memory allocated to keys*/
/*asserts that list and list's array are not NULL*/
/*since release@2020.1*/
void free_array_list(ArrayList*  list, bool free_key){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on list's array*/
    assert (list->array != NULL);
    /*check if memory to be freed for keys*/
    if (free_key){
        /*get the size of the list*/
        int size = list->size;
        /*get the array corresponding to this list*/
        void** array = list->array;
        /*iterate through array list and free memory allocated to all keys*/
        for (int i = 0 ; i < size; ++i)
            if (array[i] != NULL)
                /*free memory allocated to this key*/
                free (array[i]);
    }
    /*free memory allocated to array's list*/
    free (list->array);
    /*free memory allocated to list*/
    free (list);
}














/*returns an iterator for array list pointing to 1st node if succeeds otherwise returns NULL*/
/*asserts that array list is not NULL*/
/*since release@2020.1*/
ArrayListIterator* new_array_list_iterator(ArrayList* list){
    /*create a normal array list iterator*/
    return actual_create_array_list_iterator(list, false);
}

/*returns a pointer to an iterator for ArrayList pointing to last node if succeeds otherwise returns NULL*/
/*assert that array list is not NULL*/
/*since release@2020.1*/
ArrayListIterator* new_array_list_reverse_iterator(ArrayList* list){
    /*create a reverse array list iterator*/
    return actual_create_array_list_iterator(list, true);
}


/*checks if array list iterator has a value*/
/*assert that iterator and iterator's list are not NULL*/
/*since release@2020.1*/
bool array_list_iterator_has_next(ArrayListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*make an assertion on list of input iterator*/
    assert (iterator->for_list != NULL);
    /*check if iterator is currently pointing to some node*/
    return ( 0 <= iterator->current_node_index && iterator->current_node_index < iterator->for_list->size);
}

/*checks if array list iterator has a value*/
/*assert that iterator and iterator's list are not NULL*/
/*since release@2020.1*/
bool array_list_iterator_has_previous(ArrayListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*make an assertion on list of input iterator*/
    assert (iterator->for_list != NULL);
    /*check if iterator is currently pointing to some node*/
    return ( 0 <= iterator->current_node_index && iterator->current_node_index < iterator->for_list->size);
}




/*returns the value of current node and update iterator to previous node*/
/*asserts that iterator, iterator's list, iterator's list's array are not NULL and iterator's current current node is not  NULL*/
/*since release@2020.1*/
void* array_list_iterator_next(ArrayListIterator* iterator){
    return array_list_update_iterator(iterator, false);
}


/*returns the value of current node and update iterator to previous node*/
/*asserts that iterator, iterator's list, iterator's list's array are not NULL and iterator's current current node is not  NULL*/
/*since release@2020.1*/
void* array_list_iterator_previous(ArrayListIterator* iterator){
    return array_list_update_iterator(iterator, true);
}


/*resets the iterator to appropriate node*/
/*asserts that iterator, iterator's list are not NULL*/
/*since release@2020.1*/
void reset_array_list_iterator(ArrayListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*asserts that list for which iterator has been created exist*/
    assert (iterator->for_list != NULL);
    /*reset the iterator to appropriate*/
    if (iterator->is_reverse_iterator)
        iterator->current_node_index = iterator->for_list->size - 1;
    else
        iterator->current_node_index = iterator->for_list->size > 0 ? 0 : -1;
}


/*frees the memory allocated to iterator*/
/*asserts that input iterator is not NULL*/
/*since release@2020.1*/
void free_array_list_iterator(ArrayListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*free the memory allocated to iterator*/
    free (iterator);
}