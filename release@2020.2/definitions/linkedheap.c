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

/*include necessary headers*/
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../pair.h"
#include "../linkedlist.h"
#include "../queue.h"

/*define enumeration of types of heap*/
enum LinkedHeapType{LINKED_MAX_HEAP, LINKED_MIN_HEAP};

/*declaration of structure heap node*/
typedef struct LinkedHeapNode{
    /*each heap node has a data*/
    void* data;
    /*each heap node has address of its left and right child and parent*/
    struct LinkedHeapNode *left, *right, *parent;
} LinkedHeapNode;

/*declaration of structure heap*/
typedef struct LinkedHeap{
    /*each heap has address of its root*/
    LinkedHeapNode* root;
    /*each heap has its type*/
    enum LinkedHeapType type;
    /*each heap has address of node where child to be inserted*/
    LinkedHeapNode* nodeForInsertion;
    /*each heap has address of its last node*/
    LinkedHeapNode* nodeForDeletion;
    /*each heap its size*/
    int size;
}LinkedHeap;



/*------------------------FOR INTERMEDIATE PROCESSING--------*/

/*swaps the content of two nodes*/
/*asserts that neither of them is NULL*/
/*since release@2020.2*/
static void swap_linked_heap(LinkedHeapNode* node1, LinkedHeapNode* node2){
    /*make an assertion on nodes*/
    assert (node1 != NULL && node2 != NULL);
    /*swap nodes*/
    void* value = node1->data;
    node1->data = node2->data;
    node2->data = value;
}

/*fix the heap (heap property) in upward direction*/
/*asserts that callback is not NULL*/
/*since release@2020.2*/
static void heapifyUP_LPQ(enum LinkedHeapType type, LinkedHeapNode* current_node, Comparator comparator){
    /*make an assertion on compare callback*/
    assert (comparator != NULL);
    /*check if current node and its parent are valid*/
    if (current_node != NULL && current_node->parent != NULL){
        /*compare values and get result*/
        int cmp = ((*comparator)(current_node->data, current_node->parent->data));
        /*take decision based on type of heap*/
        if ((type == LINKED_MIN_HEAP && cmp > 0) ||
            (type == LINKED_MAX_HEAP && cmp < 0) ){
            /*get the parent*/
            LinkedHeapNode* parent = current_node->parent;
            /*swap values of child and parent*/
            swap_linked_heap(current_node, parent);
            /*call heapify up recursively on parent*/
            heapifyUP_LPQ(type, parent, comparator);
        }
    }
}

/*fix the heap (heap property) in downward direction*/
/*asserts that callback is not NULL*/
/*since release@2020.2*/
static void heapifyDOWN_LPQ(enum LinkedHeapType type, LinkedHeapNode* current_node, Comparator comparator) {
    /*make an assertion on compare callback*/
    assert (comparator != NULL);
    /*check if node is valid*/
    if (current_node != NULL){
        /*take decision based on type of heap or heap*/
        if (type == LINKED_MIN_HEAP){
            /*find the maximum*/
            LinkedHeapNode* max = current_node;
            /*get left and right child*/
            LinkedHeapNode *left = current_node->left, *right = current_node->right;
            /*compare with its left child*/
            if ( left != NULL && (*comparator)(left->data, max->data) > 0)
                max = left;
            /*compare with its right child*/
            if ( right != NULL && (*comparator)(right->data, max->data) > 0)
                max = right;
            /*check if heap property is violated*/
            if (max != current_node){
                /*swap max with its child*/
                swap_linked_heap(current_node, max);
                /*call heapify down recursively on max child*/
                heapifyDOWN_LPQ(type, max, comparator);
            }
        } else if (type == LINKED_MAX_HEAP){
            /*find the minimum*/
            LinkedHeapNode* min = current_node;
            /*get left and right child*/
            LinkedHeapNode *left = current_node->left, *right = current_node->right;
            /*compare with its left child*/
            if ( left != NULL && (*comparator)(left->data, min->data) < 0)
                min = left;
            /*compare with its right child*/
            if ( right != NULL && (*comparator)(right->data, min->data) < 0)
                min = right;
            /*check if heap property is violated*/
            if (min != current_node){
                /*swap min with its child*/
                swap_linked_heap(current_node, min);
                /*call heapify down recursively on max child*/
                heapifyDOWN_LPQ(type, min, comparator);
            }
        }
    }
}

/*updates the node for insertion*/
/*since release@2020.2*/
static LinkedHeapNode* new_node_for_insertion(LinkedHeapNode* current_node_for_insertion){
    /*make an assertion on current node for insertion*/
    assert (current_node_for_insertion  != NULL);
    /*check if its left or right child is NULL*/
    if (current_node_for_insertion->left == NULL || current_node_for_insertion->right == NULL)
        return current_node_for_insertion;
        /*check if parent of current node exist*/
    else if (current_node_for_insertion->parent == NULL)
        /*if parent does not exist then take its left child*/
        return current_node_for_insertion->left;
    else if (current_node_for_insertion == current_node_for_insertion->parent->left)
        /*if it is left child then its parent's right is next for insertion*/
        return current_node_for_insertion->parent->right;
    else{
        /*search for an ancestor in left subtree of which current node for insertion lies*/
        while (current_node_for_insertion->parent != NULL && current_node_for_insertion->parent->left != current_node_for_insertion)
            current_node_for_insertion = current_node_for_insertion->parent;
        /*check if parent's parent exist*/
        if (current_node_for_insertion->parent != NULL){
            current_node_for_insertion = current_node_for_insertion->parent->right;
            while (current_node_for_insertion->left != NULL)
                current_node_for_insertion = current_node_for_insertion->left;
            return current_node_for_insertion;
        } else {
            /*get the left most node in left subtree of current node for insertion*/
            while (current_node_for_insertion->left != NULL)
                current_node_for_insertion = current_node_for_insertion->left;
            return current_node_for_insertion;
        }
    }
}


/*returns the node containing given key in linked heap if exist otherwise returns NULL*/
/*asserts that heap and callback aren't NULL*/
static LinkedHeapNode* actual_linked_heap_contains(LinkedHeapNode* root, void* key, Comparator comparator){
    /*check if root is not NULL*/
    if (root != NULL){
        /*compare data with root's data*/
        if ( (*comparator)(root->data, key) == 0)
            /*data found in root*/
            return root;
        else {
            /*search for data in left subtree*/
            LinkedHeapNode* node1 = actual_linked_heap_contains(root->left, key, comparator);
            /*if data do not exist in left subtree then search in right subtree*/
            return node1 != NULL ? node1 : actual_linked_heap_contains(root->right, key, comparator);
        }
    } else {
        /*data not found*/
        return NULL;
    }
}


/*check if root is valid*/
/*since release@2020.2*/
static void actual_free_heap(LinkedHeapNode* root, bool freeKeys){
    if (root != NULL){
        /*first free its left subtree*/
        actual_free_heap(root->left, freeKeys);
        /*next free its right subtree*/
        actual_free_heap(root->right, freeKeys);
        /*check if values to be freed*/
        if (freeKeys && root->data != NULL)
            free (root->data);
        /*free memory allocated to root*/
        free (root);
    }
}




/*------------------------ACTUAL FUNCTIONS FOR USERS--------*/

/*creates a new linked heap and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that type is valid*/
/*since release@2020.2*/
LinkedHeap* new_linked_heap(enum LinkedHeapType type){
    /*allocate memory for new heap*/
    LinkedHeap* heap = (LinkedHeap*)malloc(sizeof(LinkedHeap));
    /*validate memory allocation*/
    if (heap != NULL){
        /*update the root of heap*/
        heap->root = heap->nodeForInsertion = heap->nodeForDeletion = NULL;
        /*update the type of heap*/
        heap->type = type;
        /*update size of heap*/
        heap->size = 0;
    }
    /*return newly created heap*/
    return heap;
}


/*adds given data to linked heap and returns true if succeeds otherwise returns false*/
/*asserts that heap and callback aren't NULL*/
/*since release@2020.2*/
bool linked_heap_add(LinkedHeap* heap, void* data, Comparator comparator){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on comparator*/
    assert (comparator!= NULL);
    /*allocate memory for new node*/
    LinkedHeapNode* node = (LinkedHeapNode*)malloc(sizeof(LinkedHeapNode));
    /*validate memory allocation*/
    if (node != NULL){
        /*update fields of node*/
        node->left = node->right = node->parent = NULL; node->data = data;
        /*check if last node for insertion is null*/
        if (heap->root == NULL){
            /*update root, node for insertion and node for deletion of heap*/
            heap->root = heap->nodeForInsertion = heap->nodeForDeletion = node;
        } else if (heap->nodeForInsertion->left == NULL){
            /*insert node as left child*/
            heap->nodeForInsertion->left = node;
            /*update parent of node*/
            node->parent = heap->nodeForInsertion;
        } else {
            /*insert in right child*/
            heap->nodeForInsertion->right = node;
            /*update parent of node*/
            node->parent = heap->nodeForInsertion;
        }
        /*update node for insertion*/
        heap->nodeForInsertion = new_node_for_insertion(heap->nodeForInsertion);
        /*update node for deletion*/
        heap->nodeForDeletion = node;
        /*increase size of heap by 1*/
        heap->size++;
        /*call heapify up on inserted node*/
        heapifyUP_LPQ(heap->type, node, comparator);


        /*return true as insertion was successful*/
        return true;
    } else {
        /*failed to allocated memory and hence insertion failed*/
        return false;
    }
}


/*returns and removes the data with max/min in heap if exist otherwise returns NULL*/
/*asserts that heap and callback aren't NULL*/
/*since release@2020.2*/
void* linked_heap_extract(LinkedHeap* heap, Comparator comparator){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*take a copy of root node*/
    LinkedHeapNode* root = heap->root;
    /*check if root is not NULL*/
    if (root != NULL){

        /*takes a copy of node to be deleted*/
        LinkedHeapNode* nodeForDeletion = heap->nodeForDeletion;
        /*take a copy of value of node to be deleted*/
        void* value = root->data;


        /*get the parent of node for deletion*/
        LinkedHeapNode* parent = nodeForDeletion->parent;
        /*check if parent of node for deletion exist*/
        if (parent != NULL){
            /*update node for insertion*/
            heap->nodeForInsertion = parent;
            /*check if node to be deleted is right child*/
            if (parent->right == nodeForDeletion){
                /*delete right child of it's parent*/
                parent->right = NULL;
                /*update node for deletion*/
                heap->nodeForDeletion = nodeForDeletion->parent->left;
            } else {
                /*it is left of its parent*/
                nodeForDeletion->parent->left = NULL;

                /*search for the ancestor in right child of which node for deletion lies*/
                while (parent->parent != NULL && parent->parent->right != parent)
                    parent = parent->parent;

                /*now check if parent's parent exist*/
                if (parent->parent != NULL){
                    /*fetch the right most node in left subtree of parent's parent*/
                    LinkedHeapNode* right_most_in_left = parent->parent->left;
                    while (right_most_in_left->right != NULL)
                        right_most_in_left = right_most_in_left->right;
                    /*update node for deletion*/
                    heap->nodeForDeletion = right_most_in_left;
                } else {
                    /*check if right of parent exist*/
                    if (parent->right != NULL){
                        /*fetch the right most node in left subtree of parent's parent*/
                        LinkedHeapNode* right_most_in_right = parent->right;
                        while (right_most_in_right->right != NULL)
                            right_most_in_right = right_most_in_right->right;
                        /*update node for deletion*/
                        heap->nodeForDeletion = right_most_in_right;
                    } else {
                        /*update node for deletion to be parent*/
                        heap->nodeForDeletion = parent;
                    }
                }
            }

            /*check if root exist - if so then call heapify down*/
            if (heap->root != NULL){
                /*copy data to root*/
                heap->root->data = nodeForDeletion->data;
                /*call heapify down to maintain heap property*/
                heapifyDOWN_LPQ(heap->type, heap->root, comparator);
            }
            /*free memory allocated to deleted Node*/
            free (nodeForDeletion);
            /*decrease the size of heap by 1*/
            heap->size--;
            /*return rge deleted values*/
            return value;
        } else {
            /*this is the only node to be deleted*/
            heap->root = heap->nodeForInsertion = heap->nodeForDeletion = NULL;
            heap->size = 0;
            /*free memory allocated to node*/
            free (root);
            /*returns the value of node deleted*/
            return value;
        }

    } else {
        /*empty heap - deletion fails*/
        return NULL;
    }
}


/*replace the 1st occurrence of key with newKey in if exist; returns true if succeeds otherwise returns false*/
/*optionally frees the memory allocated to key and keyInQueue*/
/*asserts that heap, heap's array, callback aren't NULL*/
/*since release@2020.2*/
bool linked_heap_replace(LinkedHeap* heap, void* oldKey, void* newKey, Comparator comparator, bool freeOldKey, bool freeKeyInQueue){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*search for the node containing given key*/
    LinkedHeapNode* node = actual_linked_heap_contains(heap->root, oldKey, comparator);
    /*check if node exist*/
    if (node != NULL){
        /*get the type of the heap*/
        enum LinkedHeapType type = heap->type;
        /*compare new key with old key*/
        int cmp = (*comparator)(newKey, oldKey);
        /*check if user opted to free key in heap*/
        if (freeKeyInQueue && node->data != NULL)
            free (node->data);
        /*replace old key with new key*/
        node->data = newKey;
        /*check if user opted to delete old key*/
        if (freeOldKey && oldKey != NULL)
            free (oldKey);
        /*take decision based on type and comparison result*/
        if ((type == LINKED_MIN_HEAP && cmp > 0) || (type == LINKED_MAX_HEAP && cmp < 0) ){
            heapifyUP_LPQ(type, node, comparator);
        } else if ((type == LINKED_MIN_HEAP && cmp < 0) || (type == LINKED_MAX_HEAP && cmp > 0) ){
            heapifyDOWN_LPQ(type, node, comparator);
        }
        /*returns true as process succeeds*/
        return true;
    } else {
        /*free memory allocated to oldKey if user opted for that*/
        if (freeOldKey && oldKey != NULL)
            free (oldKey);
        /*node do not exist and hence cannot update priority*/
        return false;
    }
}


/*returns the size of the linked heap*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
int linked_heap_size(LinkedHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*return the size of the heap*/
    return heap->size;
}


/*returns true if heap is empty otherwise returns false*/
/*asserts that heap is not NULL*/
/*since release@2020.2*/
bool linked_heap_is_empty(LinkedHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*return the size of the heap*/
    return heap->root == NULL;
}


/*returns the root of the heap if exist otherwise returns NULL*/
/*asserts that heap isn't NULL*/
/*since release@2020.2*/
void* linked_heap_root(LinkedHeap* heap){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*return root of heap*/
    return heap->root != NULL ? heap->root->data : NULL;
}

/*returns true if heap contains given key otherwise returns false*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that heap and callback aren't NULL*/
/*since release@2020.2*/
bool linked_heap_contains(LinkedHeap* heap, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*make an assertion on callback*/
    assert (comparator != NULL);
    /*search for node containing key*/
    LinkedHeapNode* node = actual_linked_heap_contains(heap->root, key, comparator);
    /*check if user opted for freeing key*/
    if (freeKeyAtEnd && key != NULL)
        free (key);
    /*return appropriate result*/
    return node != NULL;
}


/*frees the memory allocated to heap*/
/*optionally frees the memory  allocated to nodes*/
/*asserts that heap is not empty*/
void free_linked_heap(LinkedHeap* heap, bool freeKeys){
    /*make an assertion on heap*/
    assert (heap != NULL);
    /*iterate through heap and free memory allocated to it*/
    actual_free_heap(heap->root, freeKeys);
    /*free memory allocated to heap*/
    free (heap);
}
