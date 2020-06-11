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

/*declaration of structure linked queue node*/
typedef struct DeQueueNode{
    /*each node has a value*/
    void* value;
    /*each node has address of its next node*/
    struct DeQueueNode* next;
    /*each node has address of its previous node*/
    struct DeQueueNode* prev;
}DeQueueNode;

/*declaration of structure linked queue*/
typedef struct DeQueue{
    /*each queue has an address of its front node*/
    DeQueueNode* front;
    /*each queue has an address of its rear node*/
    DeQueueNode* rear;
    /*each queue has a size*/
    int size;
}DeQueue;

/*declaration of structure linked queue iterator*/
typedef struct DeQueueIterator{
    /*each linked queue iterator has an associated queue*/
    DeQueue* forQueue;
    /*each linked queue iterator has address of current node*/
    DeQueueNode* currentNode;
    /*each linked queue iterator has its type*/
    bool is_reverse_iterator;
}DeQueueIterator;





/*inserts data at appropriate position in de-queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*sine release@2020.1*/
static bool dqueue_insert(DeQueue* queue, void* value, bool insert_back){
    /*make an assertion on linked queue*/
    assert (queue != NULL);
    /*allocate memory for new node*/
    DeQueueNode* node = (DeQueueNode*)malloc(sizeof(DeQueueNode));
    /*validate memory allocation*/
    if (node != NULL){
        /*update fields of node*/
        node->value = value; node->next = node->prev = NULL;

        /*take decision based on queue status*/
        if (queue->front == NULL){
            /*update both front and rear of queue*/
            queue->front = queue->rear = node;
        } else if(insert_back) {
            /*update next of last node*/
            queue->rear->next = node;
            /*update previous of node*/
            node->prev = queue->rear;
            /*update rear of queue*/
            queue->rear = node;
        } else {
            /*update next of new node*/
            node->next = queue->front;
            /*update previous of queue's front*/
            queue->front->prev = node;
            /*update front of queue*/
            queue->front = node;
        }
        /*increase size of queue by 1*/
        queue->size++;
        /*return true as insertion succeeded*/
        return true;
    } else {
        /*failed to allocate memory for new node and hence failed to insert*/
        return false;
    }
}

/*returns and remove the specific node from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
static void* dqueue_deQueue(DeQueue* queue, bool delete_back){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*check if queue is empty*/
    if (queue->front != NULL){

        /*get the node to be dequeued*/
        DeQueueNode* deletedNode = delete_back ? queue->rear : queue->front;

        /*check if there is one node to be deleted*/
        if (queue->front == queue->rear) {
            /*update both front and rear to NULL*/
            queue->front = queue->rear = NULL;
        } else if (delete_back){
            /*update next of 2nd last node*/
            queue->rear->prev->next = NULL;
            /*update rear of de-queue*/
            queue->rear = queue->rear->prev;
        } else {
            /*update previous of 2nd node*/
            queue->front->next->prev = NULL;
            /*update next of de-queue*/
            queue->front = queue->front->next;
        }
        /*decrease the size of the queue by 1*/
        queue->size--;
        /*take a copy of value to be returned*/
        void* returnValue = deletedNode->value;
        /*free memory allocated to deletedNode*/
        free (deletedNode);
        /*return the value of deletedNode*/
        return returnValue;
    } else {
        /*nothing to delete in queue*/
        return NULL;
    }
}









/*creates a new empty linked dequeue and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
DeQueue* new_dqueue(void){
    /*allocate memory for new linked queue*/
    DeQueue* queue = (DeQueue*)malloc(sizeof(DeQueue));
    /*validate memory allocation*/
    if (queue != NULL){
        /*update fields of queue*/
        queue->front = queue->rear = NULL;
        queue->size= 0;
    }

    /*return newly created queue*/
    return queue;
}




/*enQueues data to front of queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
bool dqueue_enQueue_front(DeQueue* queue, void* value){
    /*insert at front*/
    return dqueue_insert(queue, value, false);
}


/*enQueues data to back of queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
bool dqueue_enQueue_rear(DeQueue* queue, void* value){
    /*insert at end*/
    return dqueue_insert(queue, value, true);
}





/*dequeues the front node from the dequeue and returns its value if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* dqueue_deQueue_front(DeQueue* queue){
    /*delete front node*/
    return dqueue_deQueue(queue, false);
}
/*dequeues the rear node from the dequeue and returns its value if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* dqueue_deQueue_rear(DeQueue* queue){
    /*delete front node*/
    return dqueue_deQueue(queue, true);
}




/*returns but NOT remove the front element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* dqueue_front(DeQueue* queue){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*return the value of top element of queue if exist*/
    return (queue->front != NULL ? queue->front->value : NULL);
}

/*returns but NOT remove the last element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* dqueue_rear(DeQueue* queue){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*return the value of top element of queue if exist*/
    return (queue->rear != NULL ? queue->rear->value : NULL);
}


/*returns true if queue is empty otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
bool dqueue_is_empty(DeQueue* queue){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*return result appropriately*/
    return (queue->front == NULL);
}

/*returns the size of the queue*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
int dqueue_size(DeQueue* queue){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*return result appropriately*/
    return queue->size;
}


/*returns the index of key from front of the queue if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
int dqueue_indexOf(DeQueue* queue, void* key, Comparator comparator, bool freeKeyAyEnd){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*stores the index of key in queue*/
    int index = 0;
    /*iterate through queue and search for key*/
    DeQueueNode* temp = queue->front;
    while (temp != NULL){
        /*compare current node's value with key*/
        if ( (*comparator)(temp->value, key) == 0){
            /*key found - now check if user opted for free key*/
            if (freeKeyAyEnd && key != NULL)
                free (key);
            /*return the index*/
            return index;
        }
        /*fetch next node*/
        temp = temp->next;
        /*increase the index by 1*/
        index++;
    }
    /*key not found - now check if user opted for free key*/
    if (freeKeyAyEnd && key != NULL)
        free (key);
    /*couldn't find key in queue*/
    return -1;
}

/*returns true if queue contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
bool dqueue_contains(DeQueue* queue, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*check if index is not -1*/
    return dqueue_indexOf(queue, key, comparator, freeKeyAtEnd) != -1;
}



/*returns true if content of both queue are same otherwise returns false*/
/*asserts that neither of the queue is NULL and callback is not NULL*/
/*since release@2020.1*/
bool dqueue_equals(DeQueue* queue1, DeQueue* queue2, Comparator comparator){
    /*make an assertion on both queues*/
    assert (queue1 != NULL && queue2 != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*first compare the size of the queue*/
    if (queue1->size != queue2->size)
        return false;
    /*iterate through both queue and compare data*/
    DeQueueNode *temp1 = queue1->front, *temp2 = queue2->front;
    while (temp1 != NULL && temp2 != NULL){
        /*compare values of current nodes*/
        if ( (*comparator)(temp1->value, temp2->value) != 0)
            /*mismatch*/
            return false;
        /*fetch next nodes*/
        temp1 = temp1->next; temp2 = temp2->next;
    }
    /*everything matched we return true*/
    return true;
}

/*resets the content of queue i.e. empty queue*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void reset_dqueue(DeQueue* queue, bool freeKeys){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*iterate through all nodes in queue and free memory*/
    DeQueueNode *temp = queue->front, *ptr = NULL;
    while (temp != NULL){
        /*check if value to be freed*/
        if (freeKeys && temp->value != NULL)
            free (temp->value);
        /*take a copy of current node*/
        ptr = temp;
        /*fetch next node*/
        temp = temp->next;
        /*free memory allocated to current node*/
        free (ptr);
    }
    /*update the fields of the queue*/
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

/*frees the memory allocated to queue*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void free_dqueue(DeQueue* queue, bool freeKeys){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*reset the content of queue*/
    reset_dqueue(queue, freeKeys);
    /*free memory allocated to queue*/
    free (queue);
}



/*creates a new linked dequeue iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
static DeQueueIterator* actual_new_dqueue_iterator(DeQueue* queue, bool is_reverse_iterator){
    /*make an assertion on linked queue*/
    assert (queue != NULL);
    /*allocate memory for new linked queue iterator*/
    DeQueueIterator* iterator = (DeQueueIterator*)malloc(sizeof(DeQueueIterator));
    /*validate memory allocation*/
    if (iterator != NULL){
        /*update fields of queue*/
        iterator->forQueue = queue;
        iterator->is_reverse_iterator = is_reverse_iterator;
        iterator->currentNode = is_reverse_iterator ? queue->rear : queue->front;
    }
    /*return newly created queue iterator*/
    return iterator;
}


/*creates a new linked queue iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that queue is not NULL*/
/*since release@2020.1*/
DeQueueIterator* new_dqueue_iterator(DeQueue* queue){
    /*create a new normal iterator*/
    return actual_new_dqueue_iterator(queue, false);
}

/*creates a new linked queue reverse iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that queue is not NULL*/
/*since release@2020.1*/
DeQueueIterator* new_dqueue_reverse_iterator(DeQueue* queue){
    /*create a new normal iterator*/
    return actual_new_dqueue_iterator(queue, true);
}



/*checks if linked queue iterator has a next node*/
/*assert that queue iterator is not NULL*/
/*since release@2020.1*/
bool dqueue_iterator_has_next(DeQueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL);
    /*return an appropriate result*/
    return (iterator->currentNode != NULL);
}

/*checks if linked queue iterator has a previous node*/
/*assert that queue iterator is not NULL*/
/*since release@2020.1*/
bool dqueue_iterator_has_previous(DeQueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL);
    /*return an appropriate result*/
    return (iterator->currentNode != NULL);
}

/*point queue iterator to its next node and returns the value contained in current node*/
/*assert that queue iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
void* dqueue_iterator_next(DeQueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL && iterator->currentNode != NULL);
    /*take a copy of value to be returned*/
    void* returnValue = iterator->currentNode->value;
    /*point iterator to next node*/
    iterator->currentNode = iterator->currentNode->next;
    /*return an appropriate result*/
    return returnValue;
}

/*point queue iterator to its previous node and returns the value contained in current node*/
/*assert that queue iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
void* dqueue_iterator_previous(DeQueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL && iterator->currentNode != NULL);
    /*take a copy of value to be returned*/
    void* returnValue = iterator->currentNode->value;
    /*point iterator to next node*/
    iterator->currentNode = iterator->currentNode->prev;
    /*return an appropriate result*/
    return returnValue;
}


/*resets the queue iterator to point to 1st node*/
/*asserts that queue iterator and its associated queue are not NULL*/
/*since release@2020.1*/
void reset_dqueue_iterator(DeQueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL);
    /*make an assertion on queue*/
    assert (iterator->forQueue != NULL);
    /*update the fields of iterator*/
    iterator->currentNode = iterator->forQueue->front;
}

/*frees the memory allocated to iterator*/
/*asserts that queue iterator is not NULL*/
/*since release@2020.1*/
void free_dqueue_iterator(DeQueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL);
    /*free memory allocated to iterator*/
    free (iterator);
}