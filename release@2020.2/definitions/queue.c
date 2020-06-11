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
typedef struct QueueNode{
    /*each node has a value*/
    void* value;
    /*each node has address of its next node*/
    struct QueueNode* next;
}QueueNode;

/*declaration of structure linked queue*/
typedef struct Queue{
    /*each queue has an address of its front node*/
    QueueNode* front;
    /*each queue has an address of its rear node*/
    QueueNode* rear;
    /*each queue has a size*/
    int size;
}Queue;

/*declaration of structure linked queue iterator*/
typedef struct QueueIterator{
    /*each linked queue iterator has an associated queue*/
    Queue* forQueue;
    /*each linked queue iterator has address of current node*/
    QueueNode* currentNode;
}QueueIterator;


/*creates a new empty queue and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
Queue* new_queue(void){
    /*allocate memory for new queue*/
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    /*validate memory allocation*/
    if (queue != NULL){
        /*update fields of queue*/
        queue->front = NULL; queue->rear = NULL;
        queue->size= 0;
    }

    /*return newly created queue*/
    return queue;
}


/*enQueues data to queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
bool queue_enQueue(Queue* queue, void* value){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*allocate memory for new node*/
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    /*validate memory allocation*/
    if (node != NULL){
        /*update fields of node*/
        node->value = value; node->next = NULL;
        /*take decision based on queue status*/
        if (queue->front == NULL){
            /*update both front and rear of queue*/
            queue->front = queue->rear = node;
        } else {
            /*update next of last node*/
            queue->rear->next = node;
            /*update rear of queue*/
            queue->rear = node;
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


/*returns and remove the first element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* queue_deQueue(Queue* queue){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*check if queue is empty*/
    if (queue->front != NULL){
        /*get the top of the queue*/
        QueueNode* topNode = queue->front;
        /*update queue's front*/
        queue->front = queue->front->next;
        /*decrease the size of the queue by 1*/
        queue->size--;
        /*check the size of the queue*/
        if (queue->size == 0)
            /*update both head and tail*/
            queue->front = queue->rear = NULL;
        /*take a copy of value to be returned*/
        void* returnValue = topNode->value;
        /*free memory allocated to topNode*/
        free (topNode);
        /*return the value of topNode*/
        return returnValue;
    } else {
        /*nothing to delete in queue*/
        return NULL;
    }
}


/*returns but NOT remove the front element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* queue_front(Queue* queue){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*return the value of top element of queue if exist*/
    return (queue->front != NULL ? queue->front->value : NULL);
}

/*returns but NOT remove the last element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
void* queue_rear(Queue* queue){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*return the value of top element of queue if exist*/
    return (queue->rear != NULL ? queue->rear->value : NULL);
}


/*returns true if queue is empty otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
bool queue_is_empty(Queue* queue){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*return result appropriately*/
    return (queue->front == NULL);
}

/*returns the size of the queue*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
int queue_size(Queue* queue){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*return result appropriately*/
    return queue->size;
}


/*returns the index of key from front of the queue if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
int queue_indexOf(Queue* queue, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on queue*/
    assert (queue != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*stores the index of key in queue*/
    int index = 0;
    /*iterate through queue and search for key*/
    QueueNode* temp = queue->front;
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
        temp = temp->next;
        /*increase the index by 1*/
        index++;
    }
    /*couldn't find key in queue*/
    return -1;
}

/*returns true if queue contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
bool queue_contains(Queue* queue, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*check if index is not -1*/
    return queue_indexOf(queue, key, comparator, freeKeyAtEnd) != -1;
}



/*returns true if content of both queue are same otherwise returns false*/
/*asserts that neither of the queue is NULL and callback is not NULL*/
/*since release@2020.1*/
bool queue_equals(Queue* queue1, Queue* queue2, Comparator comparator){
    /*make an assertion on both queues*/
    assert (queue1 != NULL && queue2 != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*first compare the size of the queue*/
    if (queue1->size != queue2->size)
        return false;
    /*iterate through both queue and compare data*/
    QueueNode *temp1 = queue1->front, *temp2 = queue2->front;
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
void reset_queue(Queue* queue, bool free_keys){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*iterate through all nodes in queue and free memory*/
    QueueNode *temp = queue->front, *ptr = NULL;
    while (temp != NULL){
        /*check if value to be freed*/
        if (free_keys && temp->value != NULL)
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
void free_queue(Queue* queue, bool free_keys){
    /*make an assertion on input queue*/
    assert (queue != NULL);
    /*reset the content of queue*/
    reset_queue(queue, free_keys);
    /*free memory allocated to queue*/
    free (queue);
}






/*creates a new linked queue iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that queue is not NULL*/
/*since release@2020.1*/
QueueIterator* new_queue_iterator(Queue* queue){
    /*make an assertion on linked queue*/
    assert (queue != NULL);
    /*allocate memory for new linked queue iterator*/
    QueueIterator* iterator = (QueueIterator*)malloc(sizeof(QueueIterator));
    /*validate memory allocation*/
    if (iterator != NULL){
        /*update fields of queue*/
        iterator->forQueue = queue;
        iterator->currentNode = queue->front;
    }
    /*return newly created queue iterator*/
    return iterator;
}


/*checks if linked queue iterator has a next node*/
/*assert that queue iterator is not NULL*/
/*since release@2020.1*/
bool queue_iterator_has_next(QueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL);
    /*return an appropriate result*/
    return (iterator->currentNode != NULL);
}

/*point queue iterator to its next node and returns the value contained in current node*/
/*assert that queue iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
void* queue_iterator_next(QueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL && iterator->currentNode != NULL);
    /*take a copy of value to be returned*/
    void* returnValue = iterator->currentNode->value;
    /*point iterator to next node*/
    iterator->currentNode = iterator->currentNode->next;
    /*return an appropriate result*/
    return returnValue;
}

/*resets the queue iterator to point to 1st node*/
/*asserts that queue iterator and its associated queue are not NULL*/
/*since release@2020.1*/
void reset_queue_iterator(QueueIterator* iterator){
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
void free_queue_iterator(QueueIterator* iterator){
    /*make an assertion on queue iterator*/
    assert (iterator != NULL);
    /*free memory allocated to iterator*/
    free (iterator);
}