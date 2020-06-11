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


#ifndef UTILITY_QUEUE_H
#define UTILITY_QUEUE_H

/*include source file*/
#include "definitions/queue.c"

/*creates a new empty linked queue and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.1*/
extern Queue* new_queue(void);



/*enQueues data to queue and returns true if succeeds otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern bool queue_enQueue(Queue* queue, void* value);

/*returns and remove the first element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* queue_deQueue(Queue* queue);





/*returns but NOT remove the front element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* queue_front(Queue* queue);

/*returns but NOT remove the last element from queue if exist otherwise returns NULL*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void* queue_rear(Queue* queue);

/*returns true if queue is empty otherwise returns false*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern bool queue_is_empty(Queue* queue);

/*returns the size of the queue*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern int queue_size(Queue* queue);

/*returns the index of key from front of the queue if exist otherwise returns -1*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
extern int queue_indexOf(Queue* queue, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns true if queue contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that queue and callback aren't NULL*/
/*since release@2020.1*/
extern bool queue_contains(Queue* queue, void* key, Comparator comparator, bool freeKeyAtEnd);

/*returns true if content of both queue are same otherwise returns false*/
/*asserts that neither of the queue is NULL and callback is not NULL*/
/*since release@2020.1*/
extern bool queue_equals(Queue* queue1, Queue* queue2, Comparator comparator);




/*resets the content of queue i.e. empty queue*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void reset_queue(Queue* queue, bool free_keys);

/*frees the memory allocated to queue*/
/*optionally frees the memory allocated to values in nodes*/
/*asserts that queue is not NULL*/
/*since release@2020.1*/
extern void free_queue(Queue* queue, bool free_keys);






/*creates a new linked queue iterator and returns a pointer to it if succeeds otherwise returns NULL*/
/*assert that queue is not NULL*/
/*since release@2020.1*/
extern QueueIterator* new_queue_iterator(Queue* queue);

/*checks if linked queue iterator has a next node*/
/*assert that queue iterator is not NULL*/
/*since release@2020.1*/
extern bool queue_iterator_has_next(QueueIterator* iterator);

/*point queue iterator to its next node and returns the value contained in current node*/
/*assert that queue iterator is not NULL and points to a valid node*/
/*since release@2020.1*/
extern void* queue_iterator_next(QueueIterator* iterator);

/*resets the queue iterator to point to 1st node*/
/*asserts that queue iterator and its associated queue are not NULL*/
/*since release@2020.1*/
extern void reset_queue_iterator(QueueIterator* iterator);

/*frees the memory allocated to iterator*/
/*asserts that queue iterator is not NULL*/
/*since release@2020.1*/
extern void free_queue_iterator(QueueIterator* iterator);

#endif