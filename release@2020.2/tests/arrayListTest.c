/**
 * @note This code demonstrates the use ArrayList type offered by utility-library
 * @note This doesn't demonstrates all methods
 * @see https://github.com/PanchalShubham/c-utility-library/arraylist.html for more details
 * @see arraylist.h for ArrayListMethods methods summary
 * @author Shubham Panchal
 * @date June 9th, 2020
 * */

// include wrapper.h for using Wrapper
#include "../wrapper.h"
// include arraylist.h for using ArrayList
#include "../arraylist.h"


// comparator for array-list
int arrayListComparator(const void* o1, const void* o2){
    /*we know that o1 and o2 are actually int-pointers so we perform a cast*/
    int val1 = *((int*)o1);
    int val2 = *((int*)o2);
    /*return the comparison result*/
    return (val1 - val2);
}

// prints the content of array list using array list iterator
void printArrayList(ArrayList* list){
    // create a new array list iterator
    ArrayListIterator* iterator = ArrayListMethods.iterator(list);

    // iterate as long as we have value in list
    while (ArrayListMethods.hasNext(iterator)){
        // get the value and set iterator to next node
        void* value = ArrayListMethods.next(iterator);
        // we know that it is array-list of integer so we use casting
        // not that we do not unwrap data because it is not removed
        // and exist in list- if we unwrap then it will be removed
        // from list as well
        printf ("%d ", Wrapper.intValue(value));
    } printf ("\n");

    // free memory allocation to list iterator
    ArrayListMethods.freeIterator(iterator);
}

// performs a test on array list
void arrayListTest(){
    // ArrayListMethods object provide all available
    // methods for working with ArrayList

    // create a new ArrayList with initial capacity of 10
    ArrayList* list = ArrayListMethods.newList(10);

    // insert data to array-list using wrappers
    ArrayListMethods.insertBack(list, Wrapper.wrapInt(20));
    ArrayListMethods.insertBack(list, Wrapper.wrapInt(40));
    ArrayListMethods.insertFront(list, Wrapper.wrapInt(10));
    ArrayListMethods.insertAt(list, Wrapper.wrapInt(30), 2);

    // print the content of list using iterators
    printArrayList(list);

    // check if array-list contains the value 20
    // we use Wrapper to wrap int 20
    // we set freeKeyAtEnd to true so that memory allocated to int 20 frees
    // we pass comparator to define how to compare list values
    printf ("contains 20: %d\n", ArrayListMethods.contains(list, Wrapper.wrapInt(20), arrayListComparator, true));
    // check if array list contains the value 50
    printf ("contains 50: %d\n", ArrayListMethods.contains(list, Wrapper.wrapInt(50), arrayListComparator, true));
    // get the index of key 20
    printf ("indexOf 20: %d\n", ArrayListMethods.indexOf(list, Wrapper.wrapInt(20), arrayListComparator, true));
    // get the index of key 50
    printf ("indexOf 50: %d\n", ArrayListMethods.indexOf(list, Wrapper.wrapInt(50), arrayListComparator, true));
    // one can perform a manual search on list->array


    // get the value at specific index of array-list
    // once can alternatively use (list->index[i]) to get void* value
    // which can then be cast to appropriate type
    void* value = ArrayListMethods.get(list, 0);
    printf ("value at index 0: %d\n", *((int*)value));
    // update the value at index 0
    void* oldIndexZeroValue = ArrayListMethods.set(list, 0, Wrapper.wrapInt(0));
    // delete oldIndexZeroValue
    printf("replaced %d with %d\n", Wrapper.unwrapInt(oldIndexZeroValue), 0);

    // get the front element of list
    void* front = ArrayListMethods.front(list);
    printf ("front: %d\n", *((int*)front));
    // get the back element of list
    void* back = ArrayListMethods.back(list);
    printf ("back: %d\n", *((int*)back));


    // get the size and capacity of list
    printf ("size: %d and capacity: %d\n", ArrayListMethods.size(list), ArrayListMethods.capacity(list));

    // check if array-list is empty
    printf ("isEmpty? %d\n", ArrayListMethods.isEmpty(list));

    // reverse the content of array-list
    ArrayListMethods.reverse(list);
    printf ("reversed: "); printArrayList(list);

    // sort the content of array-list
    ArrayListMethods.sort(list, arrayListComparator);
    printf ("sorted: "); printArrayList(list);

    // remove value 20 from list
    // we set freeKeyAtEnd to true so that we free memory allocated to 20 on heap
    // we set freeKeyAtEnd to true to remove memory allocated to 20 in list on heap (if exist)
    ArrayListMethods.remove(list, Wrapper.wrapInt(20), arrayListComparator, true, true);
    printf ("removed 20: "); printArrayList(list);


    // free memory allocated to array-list
    // we set freeKey to true because we want to free memory allocated
    // to all keys - memory allocated to integers on heap
    ArrayListMethods.free(list, true);
    printf ("Freed array-list :-)\n");
}