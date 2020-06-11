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

/*declaration of structure LinkedListNode*/
typedef struct LinkedListNode{
    /*each LinkedList node has a value*/
    void* value;
    /*each LinkedList node address of its next node*/
    struct LinkedListNode* next;
    /*each LinkedList node address of its previous node*/
    struct LinkedListNode* previous;
}LinkedListNode;

/*declaration of structure LinkedList*/
typedef struct LinkedList{
    /*each LinkedList has a starting point*/
    struct LinkedListNode* head;
    /*each LinkedList has an ending point*/
    struct LinkedListNode* tail;
    /*each LinkedList has a size*/
    int size;
}LinkedList;

/*declaration of LinkedList iterator*/
typedef struct LinkedListIterator{
    /*each list iterator has its associated list*/
    LinkedList* for_list;
    /*each list iterator has current node*/
    LinkedListNode* current_node;
    /*each list iterator has a type i.e. normal or reverse iterator*/
    bool is_reverse_iterator;
}LinkedListIterator;


/*deletes the given node in the LinkedList*/
/*do not assert anything - assumes that node is taken from list*/
/*and hence makes list non-empty*/
/*optionally frees the memory allocated to key*/
/*since release@2020.1*/
static void linked_list_delete_node(LinkedList* list, LinkedListNode* node, bool freeKey){
    if (list->head == list->tail){
        /*only one node in LinkedList*/
        list->head = list->tail = NULL;
    } else if (list->head == node){
        /*deletion from front*/
        /*update previous of 2nd node*/
        list->head->next->previous = NULL;
        /*update head of LinkedList*/
        list->head = list->head->next;
    } else if (list->tail == node){
        /*deletion from end*/
        /*update next of second last node*/
        list->tail->previous->next = NULL;
        /*update tail of LinkedList*/
        list->tail = list->tail->previous;
    } else {
        /*deletion in between*/
        /*update next of previous node*/
        node->previous->next = node->next;
        /*update previous of next node*/
        node->next->previous = node->previous;
    }
    /*decrease the size of the list by 1*/
    list->size--;
    /*check if memory allocated to key is to be deleted*/
    if (freeKey && node->value)
        /*free memory allocated to key*/
        free (node->value);
    /*free memory allocated to node*/
    free (node);
}


/*deletes single/multiple occurrences of key in LinkedList and returns the count of items being deleted*/
/*optionally frees the memory allocated to key and value in list*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
static int actual_linked_list_delete(LinkedList* list, void* key, Comparator comparator, bool deleteMany, bool freeKey, bool freeListKey){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*assert that callback is not NULL*/
    assert (comparator != NULL);
    /*stores the count of number of nodes deleted*/
    int count = 0;
    /*traverse the LinkedList to search for key*/
    LinkedListNode *temp = list->head, *ptr = NULL;
    while (temp != NULL){
        /*take a copy of next node*/
        ptr = temp->next;
        /*compare current node's key with key*/
        if ((*comparator)(temp->value, key) == 0){
            /*check if we have to deleted*/
            if (count == 0 || (count > 0 && deleteMany)){
                /*delete temp*/
                linked_list_delete_node(list, temp, freeListKey);
                /*increase count by 1*/
                count++;
                /*check if multiple instances to be deleted*/
            } else {
                /*we need not to delete anything - we break*/
                break;
            }
        }
        /*go to next node*/
        temp = ptr;
    }
    /*check if memory allocated to key has to be freed*/
    if (freeKey && key)
        /*free memory allocated to key*/
        free (key);
    /*deletion failed return false*/
    return count;
}

/*returns the index of 1st occurrence of key in LinkedList*/
/*asserts that input list is not NULL and callback is not NULL*/
static int actual_linked_list_contains(LinkedList* list, void* key, Comparator comparator, bool free_key){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*assert that callback is not NULL*/
    assert (comparator != NULL);
    /*check if list is empty*/
    if (list->head != NULL){
        /*used to store the index of element*/
        int index = 0;
        /*iterate through LinkedList sequentially*/
        LinkedListNode* temp = list->head;
        while (temp != NULL){
            /*compare values of current node and key*/
            if ( (*comparator)(temp->value, key) == 0){
                /*check if user wants to free the memory allocated to key*/
                if (free_key && key != NULL)
                    /*free memory allocated to key*/
                    free (key);
                /*key exist in LinkedList*/
                return index;
            }
            /*go to next node*/
            temp = temp->next;
            /*increase the index by 1*/
            index++;
        }
    }

    /*check if user wants to free the memory allocated to key*/
    if (free_key && key != NULL)
        /*free memory allocated to key*/
        free (key);

    /*key do not exist in LinkedList*/
    return -1;
}

















/*creates an empty LinkedList and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
LinkedList* new_linked_list(void){
    /*allocate memory for new LinkedList*/
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    /*validate memory allocation and update fields*/
    if (linkedList != NULL){
        /*update head and tail for LinkedList*/
        linkedList->head = linkedList->tail = NULL;
        /*update size of LinkedList*/
        linkedList->size = 0;
    }
    /*return newly created LinkedList*/
    return linkedList;
}




/*inserts value at given index in LinkedList and returns true if succeeds otherwise returns false*/
/*indexing begins from zero so available indices are [0...N] where index N marks insert at end*/
/*asserts that list is not NULL and index is in bound*/
/*since release@2020.1*/
bool linked_list_insert_at(LinkedList* list, void* value, int index){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on index*/
    assert (0 <= index && index <= list->size);
    /*allocate memory for new node*/
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    /*validate memory allocation*/
    if (node != NULL) {
        /*update fields of node*/
        node->next = node->previous = NULL;
        node->value = value;

        /*check if list is empty*/
        if (list->head == NULL){
            /*update both head and tail*/
            list->head = list->tail = node;
        } else if (index == 0){
            /*insert at front*/
            /*update node's next*/
            node->next = list->head;
            /*update previous of head*/
            list->head->previous = node;
            /*update head of list*/
            list->head = node;
        } else if (index == list->size){
            /*insert at end*/
            /*update node's previous*/
            node->previous = list->tail;
            /*update next of list's tail*/
            list->tail->next = node;
            /*update tail of list*/
            list->tail = node;
        } else {
            /*insertion in between*/
            LinkedListNode* temp = list->head;
            /*iterate to particular index*/
            for (int i = 0 ; i < index; ++i)
                temp = temp->next;
            /*insertion before temp*/
            /*update next of node*/
            node->next = temp;
            /*update previous of node*/
            node->previous = temp->previous;
            /*update previous node's next*/
            temp->previous->next = node;
            /*update temp's previous*/
            temp->previous = node;
        }
        /*increase the size of the list by 1*/
        list->size++;
        /*insertion succeeded - return true*/
        return true;
    } else {
        /*memory allocation failed and so insertion process*/
        return false;
    }
}

/*inserts data at the front of LinkedList and returns true if succeeds otherwise returns false*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
bool linked_list_insert_front(LinkedList* list, void* value){
    /*insert at index 0*/
    return linked_list_insert_at(list, value, 0);
}

/*inserts data at the back of LinkedList and returns true if succeeds otherwise returns false*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
bool linked_list_insert_back(LinkedList* list, void* value){
    /*insert at index list->size*/
    return linked_list_insert_at(list, value, list->size);
}







/*deletes the data at given index in LinkedList and returns the value at that index if succeds otherwise returns NULL*/
/*asserts that LinkedList is not NULL and index is in bound [0...N-1]*/
/*since release@2020.1*/
void* linked_list_delete_at(LinkedList* list, int index){
    /*make assertion on input list*/
    assert (list != NULL );
    /*make an assertion on index*/
    assert (0 <= index && index < list->size);

    /*used to take a copy of object being deleted*/
    LinkedListNode* node = NULL;

    /*check if there is only one element to delete*/
    if (list->head == list->tail){
        /*only one object is list we delete it*/
        node = list->head;
        /*update both head and tail*/
        list->head = list->tail = NULL;
    } else if (index == 0){
        /*deletion from front end*/
        node = list->head;
        /*update previous of 2nd node in list*/
        list->head->next->previous = NULL;
        /*update head of list to 2nd node*/
        list->head = list->head->next;
    } else if (index == list->size - 1){
        /*deletion from rear end*/
        node = list->tail;
        /*update next of second last node*/
        list->tail->previous->next = NULL;
        /*update tail to second last node*/
        list->tail = list->tail->previous;
    } else {
        /*deletion in between two nodes*/
        LinkedListNode* temp = list->head;
        /*iterate to required node*/
        for (long long int i = 0; i < index; ++i)
            temp = temp->next;
        /*node to be deleted is temp*/
        node = temp;
        /*update next of its previous node*/
        temp->previous->next = temp->next;
        /*update previous of its next node*/
        temp->next->previous = temp->previous;
    }

    /*take a copy of data to be returned*/
    void* return_result = node->value;

    /*free memory allocated to node being deleted*/
    free (node);

    /*decrease the length of list by 1*/
    list->size--;

    /*return data of node just deleted*/
    return return_result;
}

/*deletes the front element of the list and returns the value in it; if list is empty returns NULL*/
/*assert that LinkedList is not NULL*/
/*since release@2020.1*/
void* linked_list_delete_front(LinkedList* list){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*take decision based on list's length*/
    return (list->head == NULL ? NULL : linked_list_delete_at(list, 0));
}


/*deletes the last element of the list and returns the value in it; if list is empty returns NULL*/
/*assert that LinkedList is not NULL*/
/*since release@2020.1*/
void* linked_list_delete_back(LinkedList* list){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*take decision based on list's length*/
    return (list->head == NULL ? NULL : linked_list_delete_at(list, list->size - 1));
}




/*deletes the 1st occurrence of key in LinkedList if exist and returns true otherwise returns false*/
/*optionally frees the memory allocated to key and value in node*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
bool linked_list_delete(LinkedList* list, void* key, Comparator comparator, bool freeKeyAtEnd, bool freeListKey){
    /*delete only single occurrence of key in list*/
    return (actual_linked_list_delete(list, key, comparator, false, freeKeyAtEnd, freeListKey) == 1);
}


/*deletes all occurrence of key in LinkedList and returns the count of items being deleted*/
/*optionally frees the memory allocated to key and value in nodes*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
int linked_list_delete_all(LinkedList* list, void* key, Comparator comparator, bool freeKey, bool freeListKeys){
    /*delete multiple occurrence of key in list*/
    return actual_linked_list_delete(list, key, comparator, true, freeKey, freeListKeys);
}








/*returns true if key exist in LinkedList otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
bool linked_list_contains(LinkedList* list, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*search for key but do not free memory allocated to key*/
    return (actual_linked_list_contains(list, key, comparator, freeKeyAtEnd) != -1);
}

/*returns the index of 1st occurrence of key in list if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that input list is not NULL and callback is not NULL*/
/*since release@2020.1*/
int linked_list_indexOf(LinkedList* list, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*search for key and do not free memory allocated to key*/
    return actual_linked_list_contains(list, key, comparator, freeKeyAtEnd);
}


/*returns the value at given index in LinkedList*/
/*asserts that LinkedList is not NULL and  index is in range [0...N-1] where N is size of list*/
/*since release@2020.1*/
void* linked_list_value_at(LinkedList* list, int index){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*make an assertion on index*/
    assert (0 <= index && index < list->size);
    /*iterate through LinkedList*/
    LinkedListNode* temp = list->head;
    for (int i = 0; i < index; ++i)
        temp = temp->next;
    /*return value at particular index*/
    return temp->value;
}

/*returns the value at front end of LinkedList if exist otherwise returns NULL*/
/*asserts that input LinkedList is not NULL and is not empty*/
/*since release@2020.1*/
void* linked_list_front(LinkedList* list){
    /*make an assertion on list*/
    assert (list != NULL);
    /*return appropriate result*/
    return (list->head == NULL ? NULL : list->head->value);
}

/*returns the value at back end of LinkedList if exist otherwise returns NULL*/
/*asserts that input LinkedList is not NULL and is not empty*/
/*since release@2020.1*/
void* linked_list_back(LinkedList* list){
    /*make an assertion on list*/
    assert (list != NULL);
    /*return appropriate result*/
    return (list->tail == NULL ? NULL : list->tail->value);
}




/*returns true if LinkedList is empty otherwise returns false*/
/*asserts that input LinkedList is not NULL*/
/*since release@2020.1*/
bool linked_list_is_empty(LinkedList* list){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*return appropriate value*/
    return (list->head == NULL);
}


/*returns the size of the LinkedList*/
/*asserts that input LinkedList is not NULL*/
/*since release@2020.1*/
int linked_list_size(LinkedList* list){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*return appropriate value*/
    return (list->size);
}

/*returns true if value contained in both LinkedLists are equal otherwise returns false*/
/*asserts the list and callback aren't NULL*/
/*since release@2020.1*/
bool linked_list_equals(LinkedList* list1, LinkedList* list2, Comparator comparator){
    /*make an assertion on list*/
    assert (list1 != NULL && list2 != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*first we compare the size of the list*/
    if (list1->size == list2->size){
        /*use two pointers to traverse both lists*/
        LinkedListNode *temp1 = list1->head, *temp2 = list2->head;
        /*iterate as long as we do not reach to end of list*/
        while (temp1 != NULL && temp2 != NULL) {
            /*compare values of current nodes*/
            if ( (*comparator)(temp1->value, temp2->value) != 0)
                /*mismatch we return false*/
                return false;
            /*fetch next node*/
            temp1 = temp1->next; temp2 = temp2->next;
        }
        /*all nodes matched and hence list are equal*/
        return true;
    } else {
        /*since size's aren't equal and so list*/
        return false;
    }
}


/*reverses the content of list*/
/*asserts that input list is not NULL*/
/*since release@2020.1*/
void linked_list_reverse(LinkedList* list){
    /*make assertion on input list*/
    assert (list != NULL);
    /*iterate through whole list and swap prev and next*/
    LinkedListNode*temp = list->head;
    /*temporary pointers for processing*/
    LinkedListNode*ptr = NULL, *swap = NULL;
    while (temp != NULL){
        /*take a copy of current node*/
        ptr = temp;
        /*go to next node*/
        temp = temp->next;
        /*swap previous and next of current node*/
        swap = ptr->next;
        ptr->next = ptr->previous;
        ptr->previous = swap;
    }
    /*swap head and tail of list*/
    swap = list->head;
    list->head = list->tail;
    list->tail = swap;
}




/*inserts the given node at the end of LinkedList by manipulating pointer*/
/*asserts that input list is not NULL and input node is not NULL*/
/*since release@2020.1*/
static void linked_list_append_node(LinkedList* list, LinkedListNode* node){
    /*make an assertion on input list*/
    assert (list != NULL);
    /*make an assertion on node*/
    assert (node != NULL);
    /*disable links of current node*/
    node->next = node->previous = NULL;
    /*check if list is empty*/
    if (list->head == NULL){
        /*update both head and tail*/
        list->head = list->tail = node;
    } else {
        /*first update previous of node*/
        node->previous = list->tail;
        /*next update next of last node*/
        list->tail->next = node;
        /*update tail of LinkedList*/
        list->tail = node;
    }
    /*increase the size of the list by 1*/
    list->size++;
}

/*merges two sorted LinkedLists and returns merged list*/
/*returns null if fails to merge*/
/*assert that both of the list are not NULL*/
/*asserts that compare callback is not NULL*/
/*since release @2020.1*/
static LinkedList* linked_list_merge(const LinkedList* list1, const LinkedList* list2, Comparator comparator){
    /*make an assertion on input list*/
    assert (list1 != NULL && list2 != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*allocate memory for empty LinkedList*/
    LinkedList* list = new_linked_list();
    /*validate memory allocation*/
    if (list == NULL)
        /*memory allocation failed - cannot merge lists*/
        return NULL;

    /*memory allocated successfully*/
    /*iterate through both lists and copy data to new list*/
    LinkedListNode *temp1 = list1->head, *temp2 = list2->head, *ptr = NULL;
    while (temp1 != NULL && temp2 != NULL)
        /*compare data of list1 and list2*/
        if ((*comparator)(temp1->value, temp2->value) <= 0){
            /*insert data from list1 - take a copy of next node*/
            ptr = temp1->next;
            /*insert temp1 in new list*/
            linked_list_append_node(list, temp1);
            /*update temp1 to next node of current node*/
            temp1 = ptr;
        } else {
            /*insert data from list2 - take a copy of next node*/
            ptr = temp2->next;
            /*insert temp2 in new list*/
            linked_list_append_node(list, temp2);
            /*update temp2 to next node of current node*/
            temp2 = ptr;
        }

    /*check if list1 has exhausted*/
    if (temp1 == NULL)
        /*copy list2 completely*/
        while (temp2 != NULL){
            /*insert data from list2 - take a copy of next node*/
            ptr = temp2->next;
            /*insert temp2 in new list*/
            linked_list_append_node(list, temp2);
            /*update temp2 to next node of current node*/
            temp2 = ptr;
        }

    /*check if list2 has exhausted*/
    if (temp2 == NULL)
        /*copy list1 completely*/
        while (temp1 != NULL){
            /*insert data from list1 - take a copy of next node*/
            ptr = temp1->next;
            /*insert temp1 in new list*/
            linked_list_append_node(list, temp1);
            /*update temp1 to next node of current node*/
            temp1 = ptr;
        }

    /*return newly created list*/
    return list;
}

/*splits the LinkedList into two parts*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
static LinkedListNode* linked_list_split(LinkedList* list){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*get the size of the LinkedList*/
    unsigned long long int length = list->size;
    /*get the head of the LinkedList*/
    LinkedListNode* temp = list->head;
    /*get the half of length*/
    unsigned long long int half_length = length / 2;
    /*iterate to half LinkedList i.e. middle node*/
    for (unsigned long long int i = 0; i < half_length; ++i)
        temp = temp->next;
    /*return the middle node of LinkedList*/
    return temp;
}

/*sorts the input LinkedList*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
static bool linked_list_merge_sort(LinkedList* list, Comparator comparator){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*expect at least two elements in list*/
    if (list->head != NULL && list->head != list->tail){
        /*create two empty LinkedLists*/
        LinkedList* left = new_linked_list();
        LinkedList* right = new_linked_list();
        /*validate memory allocation*/
        if (left != NULL && right != NULL){
            /*get the middle node of the LinkedList*/
            LinkedListNode* mid = linked_list_split(list);
            /*update fields of left list*/
            left->head = list->head;
            left->tail = mid->previous;
            left->size = list->size / 2;
            /*update fields of right list*/
            right->head = mid;
            right->tail = list->tail;
            right->size = list->size - left->size;
            /*break links between two sub lists*/
            mid->previous->next = NULL;
            mid->previous = NULL;
            /*sort left and right sub lists*/
            linked_list_merge_sort(left, comparator);
            linked_list_merge_sort(right, comparator);
            /*merge two sorted LinkedLists*/
            LinkedList* merged_list = linked_list_merge(left, right, comparator);
            /*validate merged list*/
            if (merged_list != NULL){
                /*copy the content of sorted ist to original list*/
                list->head = merged_list->head;
                list->tail = merged_list->tail;
                list->size = merged_list->size;
                /*free memory allocated auxiliary to lists*/
                free (merged_list); free (left); free (right);
                /*return true as operation succeeded*/
                return true;
            } else {
                /*failed to merge sub lists - operation failed*/
                return false;
            }
        } else {
            /*we couldn't allocate memory and hence couldn't sort the list*/
            return false;
        }
    } else {
        /*LinkedList contains fewer than 2 two elements*/
        return true;
    }
}

/*sorts the content of LinkedList using merge_sort and returns true if succeeds otherwise returns false*/
/*asserts that list and callback aren't NULL*/
/*since release@2020.1*/
bool linked_list_sort(LinkedList* list, Comparator comparator){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*call merge sort algorithm to sort content of LinkedList*/
    return linked_list_merge_sort(list, comparator);
}






/*clears the list i.e. delete all element in list*/
/*optionally delete the values in LinkedList*/
/*asserts that list is not NULL*/
/*since release@2020.1*/
static void actual_linked_list_clear(LinkedList* list, bool freeListKeys){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*iterate through LinkedList and frees all nodes*/
    LinkedListNode* temp = list->head;
    while (temp != NULL){
        /*take a copy of current node*/
        LinkedListNode* ptr = temp;
        /*check if memory is to be freed for keys*/
        if (freeListKeys && temp->value != NULL)
            /*free memory allocated to keys*/
            free (temp->value);
        /*go to next node*/
        temp  = temp->next;
        /*free memory allocated to current node*/
        free (ptr);
    }
    /*updates the fields of the list*/
    list->head = list->tail = NULL;
    list->size = 0;
}



/*clear the list i.e. deletes all nodes in list*/
/*optionally frees the memory allocated to value in nodes*/
/*asserts that input list is not NULL*/
/*since release@2020.1*/
void clear_linked_list(LinkedList* list, bool freeListKeys){
    /*clear list but do not clear nodes*/
    actual_linked_list_clear(list, freeListKeys);
}

/*frees the memory allocated to all nodes in list and list*/
/*optionally frees the memory allocated to value in nodes*/
/*asserts that input list is not NULL*/
/*since release@2020.1*/
void free_linked_list(LinkedList* list, bool freeListKeys){
    /*clear list but do not clear nodes*/
    actual_linked_list_clear(list, freeListKeys);
    /*free memory allocated to LinkedList*/
    free (list);
}










/*creates a new LinkedList iterator associated with given LinkedList*/
/*returns a pointer to LinkedList iterator if succeeds otherwise returns false*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
static LinkedListIterator* actual_create_linked_list_iterator(LinkedList* list, bool is_reverse_iterator){
    /*make an assertion on LinkedList*/
    assert (list != NULL);
    /*allocate memory for new LinkedList iterator*/
    LinkedListIterator* iterator = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));
    /*validate memory allocation*/
    if (iterator != NULL){
        /*update list of iterator*/
        iterator->for_list = list;
        /*update type of iterator*/
        iterator->is_reverse_iterator = is_reverse_iterator;
        /*update current node based on iterator type*/
        if (is_reverse_iterator)
            /*reverse iterator starts from tail*/
            iterator->current_node = list->tail;
        else
            /*normal iterator starts from head*/
            iterator->current_node = list->head;
    }
    /*return the newly created iterator*/
    return iterator;
}

/*creates an iterator for LinkedList pointing to 1st node*/
/*returns a pointer to LinkedList iterator if succeeds otherwise returns a NULL pointer*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
LinkedListIterator* new_linked_list_iterator(LinkedList* list){
    /*create a normal LinkedList iterator*/
    return actual_create_linked_list_iterator(list, false);
}

/*creates an iterator for LinkedList pointing to last node*/
/*returns a pointer to LinkedList iterator if succeeds otherwise returns a NULL pointer*/
/*asserts that LinkedList is not NULL*/
/*since release@2020.1*/
LinkedListIterator* new_linked_list_reverse_iterator(LinkedList* list){
    /*create a normal LinkedList iterator*/
    return actual_create_linked_list_iterator(list, true);
}


/*returns true if LinkedList iterator has a next node otherwise returns false*/
/*assert that input iterator is not NULL*/
/*since release@2020.1*/
bool linked_list_iterator_has_next(LinkedListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*check if iterator is currently pointing to some node*/
    return (iterator->current_node != NULL);
}

/*returns true if LinkedList iterator has a previous node otherwise returns false*/
/*assert that input iterator is not NULL*/
/*since release@2020.1*/
bool linked_list_iterator_has_previous(LinkedListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*check if iterator is currently pointing to some node*/
    return (iterator->current_node != NULL);
}

/*sets the iterator to point to next node and returns the value of  the current node*/
/*asserts that iterator is not NULL and has a next node*/
/*since release@2020.1*/
void* linked_list_iterator_next(LinkedListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*make an assertion on next node*/
    assert (iterator->current_node != NULL);
    /*takes a copy of value to be returned*/
    void* returnValue = iterator->current_node->value;
    /*point current node to its next node*/
    iterator->current_node = iterator->current_node->next;
    /*return the value of the current node*/
    return returnValue;
}

/*sets the iterator to point to previous node and returns the value of the current node*/
/*asserts that iterator is not NULL and has a next node*/
/*since release@2020.1*/
void* linked_list_iterator_previous(LinkedListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*make an assertion on previous node*/
    assert (iterator->current_node != NULL);
    /*takes a copy of value to be returned*/
    void* returnValue = iterator->current_node->value;
    /*point current node to its next node*/
    iterator->current_node = iterator->current_node->previous;
    /*return the value of the current node*/
    return returnValue;
}


/*resets the iterator to appropriate node*/
/*asserts that input iterator is not NULL*/
/*since release@2020.1*/
void reset_linked_list_iterator(LinkedListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*asserts that list for which iterator has been created exist*/
    assert (iterator->for_list != NULL);
    /*reset the iterator to appropriate*/
    if (iterator->is_reverse_iterator)
        iterator->current_node = iterator->for_list->tail;
    else
        iterator->current_node = iterator->for_list->head;
}


/*frees the memory allocated to iterator*/
/*asserts that input iterator is not NULL*/
/*since release@2020.1*/
void free_linked_list_iterator(LinkedListIterator* iterator){
    /*make an assertion on input iterator*/
    assert (iterator != NULL);
    /*free the memory allocated to iterator*/
    free (iterator);
}