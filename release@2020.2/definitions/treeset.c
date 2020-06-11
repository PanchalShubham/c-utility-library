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


/*include rbt header*/
#include "../rbt.h"
#include "../linkedlist.h"
#include <stdbool.h>
#include <assert.h>

/*declaration of structure TreeSet*/
/*since release@2020.2*/
typedef struct TreeSet{
    /*a tree is implement using RBT*/
    RBT* rbt;
}TreeSet;

/*creates a new TreeSet and returns a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.2*/
TreeSet* new_tree_set(void){
    /*allocate memory for new TreeSet*/
    TreeSet* treeSet = (TreeSet*)malloc(sizeof(TreeSet));
    /*validate memory allocation*/
    if (treeSet != NULL){
        /*create a new RBT for implementation of tree set*/
        treeSet->rbt = new_rbt();
    }
    /*return newly created tree set*/
    return treeSet;
}

/*add/overwrites the given data to set*/
/*asserts that tree-set, comparator are not NULL*/
/*since release@2020.2*/
void tree_set_add(TreeSet* treeSet, void* data, Comparator comparator){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*insert data in rbt - overwrite pre-existing data if any*/
    rbt_put(treeSet->rbt, data, comparator, true);
}

/*add the given data to set if not already present*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
void tree_set_add_if_not_present(TreeSet* treeSet, void* data, Comparator comparator){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*insert data in rbt - overwrite pre-existing data if any*/
    rbt_put(treeSet->rbt, data, comparator, false);
}


/*returns and removes the minimum data in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
void* tree_set_remove_min(TreeSet* treeSet){
    /*make an assertion on treeSet*/
    assert (treeSet != NULL);
    /*delete the minimum element in rbt*/
    return rbt_remove_min(treeSet->rbt);
}
/*returns and removes the maximum data in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
void* tree_set_remove_max(TreeSet* treeSet){
    /*make an assertion on tree Set*/
    assert (treeSet != NULL);
    /*delete the maximum element in rbt*/
    return rbt_remove_max(treeSet->rbt);
}
/*returns and removes the given data from set if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
void* tree_set_remove(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*delete the data from rbt*/
    return rbt_remove(treeSet->rbt, key, comparator, freeKeyAtEnd);
}



/*returns the size of tree set i.e. number of elements in tree set*/
/*asserts that tree set is not NULL*/
/*since release@2020.2*/
int tree_set_size(TreeSet* treeSet){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*return the size of rbt of treeSet*/
    return rbt_size(treeSet->rbt);
}


/*returns true if tree-set is empty otherwise returns false*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
bool tree_set_is_empty(TreeSet* treeSet){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*return if rbt is empty*/
    return rbt_is_empty(treeSet->rbt);
}

/*returns true if set contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*since release@2020.2*/
bool tree_set_contains(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get the node that contains the given key*/
    void* data = rbt_value(treeSet->rbt, key, comparator, freeKeyAtEnd);
    /*return appropriate result*/
    return (data != NULL);
}

/*returns the node containing given key if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree set and comparator are not NULL*/
/*since release@2020.2*/
void* tree_set_get(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get the node that contains the given key and return to caller*/
    return rbt_value(treeSet->rbt, key, comparator, freeKeyAtEnd);
}


/*returns the data containing given key if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*since release@2020.2*/
/*asserts that tree set and comparator are not NULL*/
void* tree_set_search(TreeSet* treeSet, void* searchKey, EqualityComparator comparator, bool freeKeyAtEnd){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*searches for the data in treeSet in order-fashion*/
    void* returnValue = rbt_pre_order_search(treeSet->rbt->root, searchKey, comparator);
    /*check if user opted for deletion of key*/
    if (freeKeyAtEnd && searchKey != NULL)  free (searchKey);
    /*return the search result*/
    return returnValue;
}

/*returns the floor of given key in set if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
void* tree_set_floor(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get the node that contains the floor of given key and return to caller*/
    return rbt_floor(treeSet->rbt, key, comparator, freeKeyAtEnd);
}

/*returns the ceil of given key in set if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that tree-set and comparator are not NULL*/
/*since release@2020.2*/
void* tree_set_ceil(TreeSet* treeSet, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on tree set*/
    assert (treeSet != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*get the node that contains the ceil of given key and return to caller*/
    return rbt_ceil(treeSet->rbt, key, comparator, freeKeyAtEnd);
}

/*returns the minimum element in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
void* tree_set_min(TreeSet* treeSet){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*get the minimum in rbt*/
    return rbt_min(treeSet->rbt);
}

/*returns the maximum element in set if exist otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
void* tree_set_max(TreeSet* treeSet){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*get the maximum in rbt*/
    return rbt_max(treeSet->rbt);
}

/*returns the content of set as a linked list if succeeds otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
LinkedList* tree_set_keys(TreeSet* treeSet){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*return the linked list representation of tree-set*/
    return rbt_keys(treeSet->rbt);
}

/*returns the content of set in sorted order as linked list if succeeds otherwise returns NULL*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
LinkedList* tree_set_sorted_keys(TreeSet* treeSet){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*return the linked list representation of tree-set*/
    return rbt_sorted_keys(treeSet->rbt);
}

/*frees the memory allocated to tree-set*/
/*optionally free the memory allocated to keys in set*/
/*asserts that tree-set is not NULL*/
/*since release@2020.2*/
void free_tree_set(TreeSet* treeSet, bool freeKeys){
    /*make an assertion on tree-set*/
    assert (treeSet != NULL);
    /*free memory allocated to rbt*/
    free_rbt(treeSet->rbt, freeKeys);
    /*free memory allocated to tree-set*/
    free (treeSet);
}