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

#ifndef UTILITY_DQUEUE_H
#define UTILITY_DQUEUE_H

/*include source*/
#include "definitions/dqueue.c"
#include <stdbool.h>



/*creates a new empty linked dequeue and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
extern DeQueue* new_dqueue(void);



/*enQueues data to front of queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern bool dqueue_enQueue_front(DeQueue* queue, void* value);


/*enQueues data to back of queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern bool dqueue_enQueue_rear(DeQueue* queue, void* value);





/*dequeues the front node from the dequeue and returns its value if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* dqueue_deQueue_front(DeQueue* queue);

/*dequeues the rear node from the dequeue and returns its value if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* dqueue_deQueue_rear(DeQueue* queue);





/*returns but NOT remove the front element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* dqueue_front(DeQueue* queue);

/*returns but NOT remove the last element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* dqueue_rear(DeQueue* queue);

/*returns true if queue is empty otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern bool dqueue_is_empty(DeQueue* queue);

/*returns the size of the queue*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern int dqueue_size(DeQueue* queue);

/*returns the index of key from front of the queue if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
extern int dqueue_indexOf(DeQueue* queue, void* key, Comparator comparator, bool freeKeyAyEnd);

/*returns true if queue contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
extern bool dqueue_contains(DeQueue* queue, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns true if content of both queue are same otherwise returns false*/
/*asserts that neither of the queue is NULL and callback is not NULL*/
/*since release@2020.1*/
extern bool dqueue_equals(DeQueue* queue1, DeQueue* queue2, Comparator comparator);



/*resets the content of queue i.e. empty queue*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void reset_dqueue(DeQueue* queue, bool freeKeys);

/*frees the memory allocated to queue*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void free_dqueue(DeQueue* queue, bool freeKeys);






/*creates a new linked queue iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that queue is not NULL*/
/*since release@2020.1*/
extern DeQueueIterator* new_dqueue_iterator(DeQueue* queue);

/*creates a new linked queue reverse iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that queue is not NULL*/
/*since release@2020.1*/
extern DeQueueIterator* new_dqueue_reverse_iterator(DeQueue* queue);

/*checks if linked queue iterator has a next node*/
/*assert that queue iterator is not NULL*/
/*since release@2020.1*/
extern bool dqueue_iterator_has_next(DeQueueIterator* iterator);

/*checks if linked queue iterator has a previous node*/
/*assert that queue iterator is not NULL*/
/*since release@2020.1*/
extern bool dqueue_iterator_has_previous(DeQueueIterator* iterator);

/*point queue iterator to its next node and returns the value contained in current node*/
/*assert that queue iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
extern void* dqueue_iterator_next(DeQueueIterator* iterator);

/*point queue iterator to its previous node and returns the value contained in current node*/
/*assert that queue iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
extern void* dqueue_iterator_previous(DeQueueIterator* iterator);

/*resets the queue iterator to point to 1st node*/
/*asserts that queue iterator and its associated queue are not NULL*/
/*since release@2020.1*/
extern void reset_dqueue_iterator(DeQueueIterator* iterator);

/*frees the memory allocated to iterator*/
/*asserts that queue iterator is not NULL*/
/*since release@2020.1*/
extern void free_dqueue_iterator(DeQueueIterator* iterator);


#endif