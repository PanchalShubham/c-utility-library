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

/*define enumeration of types of heap*/
enum ArrayHeapType{ARRAY_MAX_HEAP, ARRAY_MIN_HEAP};

/*declaration of type ArrayHeap*/
typedef struct ArrayHeap{
    /*each heap has an array*/
    void** array;
    /*each heap has its size and capacity*/
    int size, capacity;
    /*each heap has its own type*/
    enum ArrayHeapType type;
}ArrayHeap;




/* ------------------------- ARRAY HEAP INTERNAL PROCESSING --------------- */

/*returns true if index is valid otherwise returns false*/
/*since release@2020.2*/
static bool is_valid_index_arrayHeap(int index, int size){
    /*return an appropriate value*/
    return ( 0 <= index && index < size);
}

/*swaps the value at index i and j in given heap*/
/*asserts that arrayHeap and arrayHeap's array aren't NULL and indices are in bound*/
/*since release@2020.2*/
static void swap_arrayHeap(ArrayHeap* arrayHeap, int i, int j){
    /*make an assertion on heap*/
    assert (arrayHeap != NULL);
    /*make an assertion on array of heap*/
    assert (arrayHeap->array != NULL);
    /*make an assertion on indices*/
    assert ( is_valid_index_arrayHeap(i, arrayHeap->size) && is_valid_index_arrayHeap(j, arrayHeap->size));
    /*swap the content*/
    void* temp = arrayHeap->array[i];
    arrayHeap->array[i] = arrayHeap->array[j];
    arrayHeap->array[j] = temp;
}

/*heapify in upward direction at index i based on type of heap*/
/*asserts that heap, heap's array and callback array aren't NULL*/
/*since release@2020.2*/
static void heapifyUP_APQ(ArrayHeap* arrayHeap, int i, Comparator comparator){
    /*make an assertion on heap*/
    assert (arrayHeap != NULL);
    /*make an assertion on array of heap*/
    assert (arrayHeap->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get the index of parent*/
    int p = (i - 1) / 2;
    /*get the sie of heap*/
    int size = arrayHeap->size;
    /*get the array of heap*/
    void** array = arrayHeap->array;
    /*get the type of heap*/
    enum ArrayHeapType type = arrayHeap->type;
    /*is both indices are valid then proceed*/
    if (is_valid_index_arrayHeap(i, size) && is_valid_index_arrayHeap(p, size)){
        /*compare priorities of parent and child*/
        int cmp = (*comparator)(array[i], array[p]);
        /*take decision based on type of heap*/
        if ((type == ARRAY_MIN_HEAP && cmp > 0) || (type == ARRAY_MAX_HEAP && cmp < 0) ){
            /*swap the value of parent and child*/
            swap_arrayHeap(arrayHeap, i, p);
            /*call heapify up on parent index recursively*/
            heapifyUP_APQ(arrayHeap, p, comparator);
        }
    }
}

/*heapify in downward direction at index i*/
/*asserts that arrayHeap, arrayHeap's array, callback aren't NULL*/
/*since release@2020.2*/
static void heapifyDOWN_APQ(ArrayHeap* arrayHeap, int i, Comparator comparator){
    /*make an assertion on array heap*/
    assert (arrayHeap != NULL);
    /*make an assertion on array of array heap*/
    assert (arrayHeap -> array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*check if index is in bound*/
    if (is_valid_index_arrayHeap(i, arrayHeap->size)){
        /*get the type of heap*/
        enum ArrayHeapType type = arrayHeap->type;
        /*get the size of the heap*/
        int size = arrayHeap->size;
        /*get the array of the array heap*/
        void** array = arrayHeap->array;
        /*assume that max/min is the i*/
        int index = i, cmp, left = 2*i + 1, right = 2*i + 2;
        /*check if left child exist*/
        if (is_valid_index_arrayHeap(left, size)){
            /*compare i with its left child*/
            cmp = (*comparator)(array[left], array[index]);
            /*update index based on comparison result and type*/
            if ((type == ARRAY_MIN_HEAP && cmp > 0) || (type == ARRAY_MAX_HEAP && cmp < 0))
                index = left;
        }
        /*check if right child exist*/
        if (is_valid_index_arrayHeap(right, size)){
            /*compare i with its right child*/
            cmp = (*comparator)(array[right], array[index]);
            /*update index based on comparison result and type*/
            if ((type == ARRAY_MIN_HEAP && cmp > 0) || (type == ARRAY_MAX_HEAP && cmp < 0))
                index = right;
        }

        /*check if heap property is violated*/
        if (index != i){
            /*swap values at index and i*/
            swap_arrayHeap(arrayHeap, i, index);
            /*call heapify down at index recursively*/
            heapifyDOWN_APQ(arrayHeap, index, comparator);
        }
    }
}


/*updates the capacity of array of heap - doubles capacity if possible*/
/*asserts that heap, heap's array aren't NULL*/
/*since release@2020.2*/
static bool expand_arrayHeap(ArrayHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*check if old size is already*/
    if (heap->capacity == INT_MAX)
        return false;
    /*get the old capacity of the heap*/
    int old_size = heap->capacity;
    /*get the size for new array*/
    int new_size = 2*old_size <= INT_MAX ? 2*old_size : INT_MAX;
    /*allocate memory for new size*/
    void** array = (void**)malloc(sizeof(void*)*new_size);
    /*validate memory allocation*/
    if (array != NULL) {
        /*copy original array content to new array*/
        for (int i = 0; i < old_size; ++i)
            array[i] = heap->array[i];
        /*free memory allocated to previous array*/
        free(heap->array);
        /*update array to new array*/
        heap->array = array;
        /*update capacity of list*/
        heap->capacity = new_size;
        /*return true as process succeeded*/
        return true;
    } else {
        /*failed to allocate memory*/
        return false;
    }
}

/*updates the capacity of heap - shrinks size if needed*/
/*assert that heap and heap's array aren't NULL*/
/*since release@2020.2*/
static void shrink_arrayHeap(ArrayHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*get the capacity of the heap*/
    int capacity = heap->capacity ;
    /*get the size of the heap*/
    int size = heap->size;
    /*check what percent of heap is filled*/
    double percent_filled = ( (double)size/ capacity)*100.0;
    /*if list is at most 25% filled - we can shrink*/
    if (percent_filled <= 25.0 && (capacity / 2 > 0)){
        /*we can shrink the capacity*/
        /*allocate memory for half of the capacity of heap*/
        void** array = (void**)malloc(sizeof(void*)*(capacity / 2));
        /*validate memory allocation*/
        if (array != NULL){
            /*get copy of array of heap*/
            void** old_array = heap->array;
            /*copy original list's content to new array*/
            for (int i = 0; i < size; ++i)
                array[i] = old_array[i];
            /*free memory allocated to old array*/
            free (old_array);
            /*update array of heap*/
            heap->array = array;
            /*update capacity of heap*/
            heap->capacity = capacity / 2;
        }
    }
}



/* ------------------------- ARRAY HEAP OPERATIONS --------------- */


/*creates a new array heap for on heap and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that initial capacity is a positive integer and type is valid*/
/*since release@2020.2*/
ArrayHeap* new_array_heap(int initial_capacity, enum ArrayHeapType type){
    /*make an assertion on initial capacity*/
    assert (initial_capacity > 0);
    /*make an assertion on type*/
    assert (type == ARRAY_MAX_HEAP || type == ARRAY_MIN_HEAP);
    /*allocate memory for new array heap*/
    ArrayHeap* arrayHeap = (ArrayHeap*)malloc(sizeof(ArrayHeap));
    /*validate memory allocation*/
    if (arrayHeap != NULL){
        /*allocate memory for initial_capacity integers on heap*/
        void** array = (void**)malloc(sizeof(void*)*initial_capacity);
        /*validate memory allocation*/
        if (array != NULL){
            /*update fields of array heap*/
            arrayHeap->size = 0;arrayHeap->array = array;
            arrayHeap->type = type;arrayHeap->capacity = initial_capacity;
        }
    }
    /*return newly created array heap*/
    return arrayHeap;
}


/*adds given data to array heap and returns true if succeeds otherwise returns false*/
/*asserts that heap, heap's array and callback aren't NULL*/
/*since release@2020.2*/
bool array_heap_add(ArrayHeap* heap, void* data, Comparator comparator){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*check if heap is completely filled*/
    if (heap->size == heap->capacity){
        /*update heap's capacity*/
        bool result = expand_arrayHeap(heap);
        /*if failed to expand heap then insertion failed*/
        if (!result)
            return false;
    }
    /*get the size of the heap*/
    int size = heap->size;
    /*insert data at the end*/
    heap->array[size] = data;
    /*increase the size of heap by 1*/
    heap->size++;
    /*call heapify up at last index to maintain heap property*/
    heapifyUP_APQ(heap, size - 1, comparator);
    /*return true as insertion process succeeded*/
    return true;
}

/*returns and removes the data with max/min in heap if exist otherwise returns NULL*/
/*asserts that heap, heap's array and callback aren't NULL*/
/*since release@2020.2*/
void* array_heap_extract(ArrayHeap* heap, Comparator comparator){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*check if heap contains data*/
    if (heap->size > 0){
        /*take a copy of value to be returned*/
        void* returnValue = heap->array[0];
        /*copy last element at root*/
        heap->array[0] = heap->array[heap->size - 1];
        /*decrease the size of the heap by 1*/
        heap->size--;
        /*call heapify down at root to maintain heap property*/
        heapifyDOWN_APQ(heap, 0, comparator);
        /*shrink the capacity of heap if needed*/
        shrink_arrayHeap(heap);
        /*return the value back to caller*/
        return returnValue;
    } else {
        /*heap is empty - cannot extract key*/
        return NULL;
    }
}

/*replace the 1st occurrence of key with newKey in if exist; returns true if succeeds otherwise returns false*/
/*optionally frees the memory allocated to key and keyInQueue*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
bool array_heap_replace(ArrayHeap* heap, void* oldKey, void* newKey, Comparator comparator, bool freeOldKey, bool freeKeyInQueue){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get the size and array of the heap*/
    int size = heap->size; void** array = heap->array;
    /*get the index of 1st occurrence of oldKey in heap*/
    int index = -1;
    /*iterate through heap and search for index of key*/
    for (int i = 0 ; i < size; ++i)
        /*compare array[i] with key*/
        if ( (*comparator)(array[i], oldKey) == 0){
            /*update the index*/
            index = i;
            break;
        }
    /*check if old key exist in heap*/
    if (index != -1){
        /*get the type of the heap*/
        enum ArrayHeapType type = heap->type;
        /*compare new key with old key*/
        int cmp = (*comparator)(newKey, oldKey);
        /*check if user opted to free key in heap*/
        if (freeKeyInQueue && array[index] != NULL)
            free (array[index]);
        /*replace old key with new key*/
        array[index] = newKey;
        /*check if user opted to delete old key*/
        if (freeOldKey && oldKey != NULL)
            free (oldKey);
        /*take decision based on type and comparison result*/
        if ((type == ARRAY_MIN_HEAP && cmp > 0) || (type == ARRAY_MAX_HEAP && cmp < 0) ){
            heapifyUP_APQ(heap, index, comparator);
        } else if ((type == ARRAY_MIN_HEAP && cmp < 0) || (type == ARRAY_MAX_HEAP && cmp > 0) ){
            heapifyDOWN_APQ(heap, index, comparator);
        }
        /*returns true as process succeeds*/
        return true;
    } else {
        /*old key do not exist in */
        return false;
    }
}


/*returns the size of the heap*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
int array_heap_size(ArrayHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*return the size of the heap*/
    return heap->size;
}

/*returns the capacity of the heap*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
int array_heap_capacity(ArrayHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*return the capacity of the heap*/
    return heap->capacity;
}

/*returns true if heap is empty otherwise returns false*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
bool array_heap_is_empty(ArrayHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*return appropriate result*/
    return heap->size == 0;
}

/*returns the root of the heap if exist otherwise returns NULL*/
/*asserts that heap and heap's array aren't NULL*/
/*since release@2020.2*/
void* array_heap_root(ArrayHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*return appropriate result*/
    return (heap->size > 0 ? heap->array[0] : NULL);
}

/*returns the index of 1st occurrence of key in heap if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
int array_heap_indexOf(ArrayHeap* heap, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on array of heap*/
    assert (heap->array != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get a copy of array of heap*/
    void** array = heap->array;
    /*get the size of the heap*/
    int size = heap->size;
    /*stores the index of key in array*/
    int index = -1;
    /*iterate through heap and search for index of key*/
    for (int i = 0 ; i < size; ++i)
        /*compare array[i] with key*/
        if ( (*comparator)(array[i], key) == 0){
            /*update the index*/
            index = i;
            break;
        }
    /*free memory allocated to key if user opted*/
    if (freeKeyAtEnd && key != NULL)
        free (key);
    /*return the computed index*/
    return index;
}

/*returns true if heap contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
bool array_heap_contains(ArrayHeap* heap, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*search for index of key in heap*/
    return (array_heap_indexOf(heap, key, comparator, freeKeyAtEnd) != -1);
}


/*frees the memory allocated to heap*/
/*optionally frees the memory allocated to keys in heap*/
/*asserts that heap and heap's arrays aren't NULL*/
/*since release@2020.2*/
void free_array_heap(ArrayHeap* heap, bool freeKeys){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on heap's array*/
    assert (heap->array != NULL);
    /*get the size of the heap*/
    int size = heap->size;
    /*get a copy of array of heap*/
    void** array = heap->array;
    /*check if user opted for freeing keys*/
    if (freeKeys)
        /*iterate through each and every node and free memory allocated to them*/
        for (int i = 0 ; i < size; ++i)
            /*check if ith value is not NULL*/
            if (array[i] != NULL)
                free (array[i]);
    /*free memory allocated to array of heap*/
    free (array);
    /*free memory allocated to heap*/
    free (heap);
}
