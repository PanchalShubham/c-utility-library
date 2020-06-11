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
#include "../linkedlist.h"
#include "../queue.h"

/*declaration of colors*/
typedef enum COLOR{RED, BLACK}COLOR;
/*declaration of structure RBTNode*/
typedef struct RBTNode{
    /*each node has a data*/
    void* data;
    /*each node has a pointer to its left and right child*/
    struct RBTNode *left, *right;
    /*each node has its size*/
    int size;
    /*each node has its own color of edge that links it to its parent*/
    COLOR color;
}RBTNode;
/*declaration of structure RBT*/
typedef struct RBT{
    /*each rbt has a root*/
    RBTNode* root;
}RBT;

/*returns true if given node is a red node*/
/*since release@2020.2*/
static bool isRed(RBTNode* x){
    /*a NULL node has a black color*/
    return (x == NULL ? false : x->color == RED);
}
/*returns the number of nodes in rbt rooted at root*/
/*since release@2020.2*/
static int rbt_subtree_size(RBTNode* root){
    /*return an appropriate value*/
    return (root == NULL ? 0 : root->size);
}


/*performs a right rotation about given node h*/
/*make a left-leaning link lean to right*/
/*asserts that h and h's left child are not NULL and h's left child is colored red*/
/*since release@2020.2*/
static RBTNode* rotate_right(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    /*make an assertion on left child of h*/
    assert (h->left != NULL);
    /*make an assertion on color of left child*/
    assert (isRed(h->left));
    /*get the left node of h*/
    RBTNode* x = h->left;
    /*update the left of current node to right of left node*/
    h->left = x->right;
    /*update right of left node to current node*/
    x->right = h;
    /*update color of left node to color of current left's right node*/
    x->color = x->right->color;
    /*update color of left's right node to RED*/
    x->right->color = RED;
    /*update size of left node*/
    x->size = h->size;
    /*update size of current node*/
    h->size = 1 + rbt_subtree_size(h->left) + rbt_subtree_size(h->right);
    /*current node is now replaced by left node*/
    return x;
}

/*performs a left rotation about given node h*/
/*make a right leaning link lean to left*/
/*asserts that h and h's right child are not NULL and h's right child is colored red*/
/*since release@2020.2*/
static RBTNode* rotate_left(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    /*make an assertion on right child of h*/
    assert (h->right != NULL);
    /*make an assertion on color of red child*/
    assert (isRed(h->right));
    /*get the right node*/
    RBTNode* x = h->right;
    /*update the right of current node to left of right node*/
    h->right = x->left;
    /*update left of right node to current node*/
    x->left = h;
    /*update color of right node to right's left node*/
    x->color = x->left->color;
    /*update color of left node to RED*/
    x->left->color = RED;
    /*update size of left node*/
    x->size = h->size;
    /*update size of current node*/
    h->size = 1 + rbt_subtree_size(h->left) + rbt_subtree_size(h->right);
    /*current node is now replaced by its left node*/
    return x;
}

/*flips the colors of a node*/
/*asserts that h is not NULL and has two children colored opposite to h*/
/*since release@2020.2*/
static void flipColors(RBTNode* h){
    /*make assertion node and its children*/
    assert (h != NULL && h->left != NULL && h->right != NULL);
    /*make assertion on color of current node and its children*/
    assert ( (!isRed(h) && isRed(h->left) && isRed(h->right)) ||
                     (isRed(h) && !isRed(h->left) && !isRed(h->right)));
    /*flip color of current node*/
    h->color = h->color == RED ? BLACK : RED;
    /*flip color of left child*/
    h->left->color = h->left->color == RED ? BLACK : RED;
    /*flip color of right child*/
    h->right->color = h->right->color == RED ? BLACK : RED;
}


/*makes red node towards left*/
/*since release@2020.2*/
static RBTNode* move_red_left(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    /*asserts that h is red and its left and left's left are black*/
    assert (isRed(h) && !isRed(h->left) && !isRed(h->left->left));
    /*flip colors about h*/
    flipColors(h);
    /*check if we need to perform rotations*/
    if (isRed(h->right->left)){
        /*rotate right about right child of current node*/
        h->right = rotate_right(h->right);
        /*rotate left about new current node*/
        h = rotate_left(h);
        /*flip colors about new current node*/
        flipColors(h);
    }
    /*return new current node*/
    return h;
}

/*moves the red node to right*/
/*since release@2020.2*/
static RBTNode* move_red_right(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    /*asserts that h is red and its right and right's left are black*/
    assert (isRed(h) && !isRed(h->right) && !isRed(h->right->left));
    /*flip colors about h*/
    flipColors(h);
    /*check if we need to perform more rotations*/
    if (isRed(h->left->left)){
        /*make a right rotation about current node*/
        h = rotate_right(h);
        /*flip colors about current node*/
        flipColors(h);
    }
    /*return new current node*/
    return h;
}


/*restores the rbt invariants - left leaning RBT*/
/*asserts that h is not NULL*/
/*since release@2020.2*/
static RBTNode* rbt_balance(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    if (isRed(h->right))                         h = rotate_left(h);
    if (isRed(h->left) && isRed(h->left->left))  h = rotate_right(h);
    if (isRed(h->left) && isRed(h->right))       flipColors(h);
    h->size = 1 + rbt_subtree_size(h->left) + rbt_subtree_size(h->right);
    return h;
}




/*allocates memory for a new RBT and return a pointer to it if succeeds otherwise returns NULL*/
/*since release@2020.2*/
RBT* new_rbt(void){
    /*allocate memory for new RBT*/
    RBT* rbt = (RBT*)malloc(sizeof(RBT));
    /*validate memory allocation*/
    if (rbt != NULL)
        /*update root of rbt*/
        rbt->root = NULL;
    /*return newly created rbt*/
    return rbt;
}


/*puts the key in rbt and returns the new root*/
/*since release@2020.2*/
static RBTNode* actual_rbt_put(RBTNode* h, void* data, Comparator comparator, bool overwrite){
    if (h == NULL){
        /*allocate memory for new node*/
        RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
        /*validate memory allocation and update fields*/
        if (node != NULL){
            /*update fields of rbt*/
            node->left = node->right = NULL;
            node->data = data; node->size = 1;
            node->color = RED;
        }
        /*return newly created node*/
        return node;
    }

    /*make a comparison between root's data and data*/
    int cmp = (*comparator)(data, h->data);
    if       (cmp < 0)      h->left     = actual_rbt_put(h->left, data, comparator, overwrite);
    else if  (cmp > 0)      h->right    = actual_rbt_put(h->right, data, comparator, overwrite);
    else if (overwrite)     h->data     = data;

    /*fixup any right-leaning links*/
    if (isRed(h->right) && !isRed(h->left))      h = rotate_left(h);
    if (isRed(h->left) && isRed(h->left->left))  h = rotate_right(h);
    if (isRed(h->left) && isRed(h->right))       flipColors(h);

    /*update the size of current node*/
    h->size = 1 + rbt_subtree_size(h->left) + rbt_subtree_size(h->right);
    /*return new root*/
    return h;
}

/*adds data to rbt if doesn't exist; if exist then optionally overwrites the data*/
/*returns true if succeeds otherwise returns false*/
/*asserts that rbt and comparator aren't NULL*/
/*since release@2020.2*/
bool rbt_put(RBT* rbt, void* data, Comparator comparator, bool overwrite){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*get the old size of rbt*/
    int old_size = rbt_subtree_size(rbt->root);
    /*insert data in rbt*/
    rbt->root = actual_rbt_put(rbt->root, data, comparator, overwrite);
    /*color the root node as black*/
    if (rbt->root != NULL)  rbt->root->color = BLACK;
    /*get the new size of rbt*/
    int new_size = rbt_subtree_size(rbt->root);
    /*compare sizes and return appropriate result*/
    return (new_size == old_size + 1);
}


/*returns the keys in rbt in a linked list if succeeds otherwise returns NULL*/
/*assert that rbt is not NULL*/
/*since release@2020.2*/
LinkedList* rbt_keys(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*create a new queue*/
    Queue* queue = new_queue();
    /*create a new linked list*/
    LinkedList* list = new_linked_list();
    /*check if rbt is empty*/
    if (queue != NULL && list != NULL && rbt->root != NULL){
        /*enQueue root*/
        queue_enQueue(queue, rbt->root);
        /*iterate as long as we have data in queue*/
        while (!queue_is_empty(queue)){
            /*dequeue data from queue*/
            RBTNode* node = queue_deQueue(queue);
            /*insert data to queue*/
            linked_list_insert_back(list, node->data);
            /*insert left child if needed*/
            if (node->left != NULL)     queue_enQueue(queue, node->left);
            /*insert right child if needed*/
            if (node->right != NULL)     queue_enQueue(queue, node->right);
        }
    }
    /*free memory allocated to queue*/
    if (queue != NULL)  free_queue(queue, false);
    /*return the linked list*/
    return list;
}



/*fills the linked list with in-order traversal of keys*/
/*since release@2020.2*/
void rbt_actual_in_order(RBTNode* root, LinkedList* list){
    /*check if root is NULL*/
    if (root != NULL){
        /*first we process left subtree*/
        rbt_actual_in_order(root->left, list);
        /*then we visit root*/
        linked_list_insert_back(list, root->data);
        /*finally we process right subtree*/
        rbt_actual_in_order(root->right, list);
    }
}
/*returns the keys in the rbt in sorted order as linked list if succeeds otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
LinkedList* rbt_sorted_keys(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*create a new linked list*/
    LinkedList* list = new_linked_list();
    /*validate memory allocation and populate list*/
    if (list != NULL)
        rbt_actual_in_order(rbt->root, list);
    /*return newly created list*/
    return list;
}

/*returns the size of the rbt*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
int rbt_size(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*return the size of the tree*/
    return rbt_subtree_size(rbt->root);
}

/*returns true if rbt is empty otherwise returns false*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
bool rbt_is_empty(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*return an appropriate result*/
    return rbt->root == NULL;
}

/*returns the maximum of two integers*/
/*since release@2020.2*/
int find_max(int x, int y){
    /*returns an appropriate result*/
    return (x > y ? x : y);
}
/*returns the height of tree rooted at h*/
/*since release@2020.2*/
static int rbt_subtree_height(RBTNode* h){
    return (h == NULL ? -1 : 1 + find_max(rbt_subtree_height(h->left), rbt_subtree_height(h->right)));
}

/*returns the height of the rbt*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
int rbt_height(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*return the height of tree*/
    return rbt_subtree_height(rbt->root);
}


/*returns the minimum node in tree rooted at h if exist otherwise returns NULL*/
/*asserts that h is not NULL*/
/*since release@2020.2*/
static RBTNode* rbt_subtree_min(RBTNode* h){
    /*asserts that h is not NULL*/
    assert (h != NULL);
    /*stores the minimum node*/
    RBTNode* minimum = h;
    /*fetch the leftmost node in tree*/
    while (minimum->left != NULL)
        minimum = minimum->left;
    /*return the minimum node*/
    return minimum;
}
/*returns the minimum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
void* rbt_min(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*stores the minimum node*/
    RBTNode* minimum = NULL;
    /*check if tree is empty*/
    if (rbt->root != NULL)
        /*get the minimum node if exist*/
        minimum = rbt_subtree_min(rbt->root);
    /*return the appropriate result*/
    return (minimum != NULL ? minimum->data : NULL);
}

/*returns the maximum node in tree rooted at h if exist otherwise returns NULL*/
/*asserts that h is not NULL*/
/*since release@2020.2*/
static RBTNode* rbt_subtree_max(RBTNode* h){
    /*asserts that h is not NULL*/
    assert (h != NULL);
    /*stores the maximum node*/
    RBTNode* maximum = h;
    /*fetch the rightmost node in tree*/
    while (maximum->right != NULL)
        maximum = maximum->right;
    /*return the maximum node*/
    return maximum;
}
/*returns the maximum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
void* rbt_max(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*stores the maximum node*/
    RBTNode* maximum = NULL;
    /*check if tree is empty*/
    if (rbt->root != NULL)
        /*get the maximum node if exist*/
        maximum = rbt_subtree_max(rbt->root);
    /*return the appropriate result*/
    return (maximum != NULL ? maximum->data : NULL);
}

/*returns the node containing floor of given key in tree rooted at h if exist otherwise returns NULL*/
/*since release@2020.2*/
static RBTNode* rbt_actual_floor(RBTNode* h, void* key, Comparator comparator){
    /*check if root is NULL*/
    if (h == NULL)          return NULL;
    /*compare data with root's data*/
    int cmp = (*comparator)(key, h->data);
    if (cmp == 0)               return h;
    if (cmp < 0)                return rbt_actual_floor(h->left, key, comparator);
    RBTNode* t = rbt_actual_floor(h->right, key, comparator);
    if (t != NULL)      return t;
    else                return h;
}

/*returns the floor of given key in rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of operation*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
void* rbt_floor(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*get the floor node*/
    RBTNode* node = rbt_actual_floor(rbt->root, key, comparator);
    /*take a copy of return value*/
    void* returnValue = node != NULL ? node->data : NULL;
    /*free memory allocated to key*/
    if (freeKeyAtEnd && key != NULL)    free (key);
    /*return result to caller*/
    return returnValue;
}


/*returns the node containing ceil of given in tree rooted at h if exist otherwise returns NULL*/
/*since release@2020.2*/
static RBTNode* rbt_actual_ceil(RBTNode* h, void* key, Comparator comparator){
    if (h == NULL)          return NULL;
    /*make a comparison between key and root's key*/
    int cmp = (*comparator)(key, h->data);
    if (cmp == 0)       return  h;
    if (cmp > 0)        return rbt_actual_ceil(h->right, key, comparator);
    RBTNode* t = rbt_actual_ceil(h->left, key, comparator);
    if (t != NULL)  return t;
    else            return h;
}

/*returns the ceil of given key in rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of operation*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
void* rbt_ceil(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*get the ceil node*/
    RBTNode* node = rbt_actual_ceil(rbt->root, key, comparator);
    /*take a copy of return value*/
    void* returnValue = node != NULL ? node->data : NULL;
    /*free memory allocated to key*/
    if (freeKeyAtEnd && key != NULL)    free (key);
    /*return result to caller*/
    return returnValue;
}

/*returns the rank of given key in tree rooted at x*/
/*rank := number of nodes in tree that less than given node*/
/*since release@2020.2*/
static int rbt_actual_rank(RBTNode* x, void* key, Comparator comparator){
    if (x == NULL)      return 0;
    /*make a comparison between key and x's data*/
    int cmp = (*comparator)(key, x->data);
    /*take decision based on comparison result*/
    if (cmp < 0)            return rbt_actual_rank(x->left, key, comparator);
    else if (cmp > 0)       return 1 + rbt_subtree_size(x->left) + rbt_actual_rank(x->right, key, comparator);
    else                    return rbt_subtree_size(x->left);
}

/*returns the rank of given key in rbt if exist otherwise returns -1*/
/*rank := number of nodes in tree that less than given node*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
int rbt_rank(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*get the rank of key in tree rbt*/
    int rank = rbt_actual_rank(rbt->root, key, comparator);
    /*free memory allocated to key*/
    if (freeKeyAtEnd && key != NULL)
        free (key);
    /*return the rank*/
    return rank;
}






/*returns the data that matches key in rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of the search*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
void* rbt_value(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*traverse the rbt and search for data*/
    RBTNode* temp = rbt->root;
    while (temp != NULL){
        /*make a comparison between temp and key*/
        int cmp = (*comparator)(key, temp->data);
        /*take decision based on comparison result*/
        if (cmp < 0)
            /*search in left subtree*/
            temp = temp->left;
        else if (cmp > 0)
            /*search in right subtree*/
            temp = temp->right;
        else
            /*data found*/
            break;
    }
    /*check if user opted to free key*/
    if (freeKeyAtEnd && key != NULL) free (key);
    /*return appropriate result*/
    return temp == NULL ? NULL : temp->data;
}

/*returns true if rbt contains given key*/
/*optionally frees the memory allocated to key at the end*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
bool rbt_contains(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*search for node in rbt that contains key*/
    return rbt_value(rbt, key, comparator, freeKeyAtEnd) != NULL;
}


/*actually searches in rbt in pre-order fashion*/
/*since release@2020.2*/
static void* rbt_pre_order_search(RBTNode* root, void* searchKey, EqualityComparator comparator){
    if (root != NULL){
        /*first search in root*/
        if ( (*comparator)(searchKey, root->data))
            /*data matched*/
            return root->data;
        /*next search in left subtree*/
        void* left = rbt_pre_order_search(root->left, searchKey, comparator);
        /*check if data exist in left subtree exist*/
        if (left == NULL){
            /*search in right subtree*/
            return rbt_pre_order_search(root->right, searchKey, comparator);
        } else {
            /*key found in left subtree*/
            return left;
        }
    } else {
        /*cannot search in empty tree*/
        return NULL;
    }
}

/*returns the data containing given key if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end*/
/*since release@2020.2*/
/*asserts that rbt and comparator are not NULL*/
void* rbt_search(RBT* rbt, void* searchKey, EqualityComparator comparator, bool freeKeyAtEnd){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*searches for the data in rbt in order-fashion*/
    void* returnValue = rbt_pre_order_search(rbt->root, searchKey, comparator);
    /*check if user opted for deletion of key*/
    if (freeKeyAtEnd && searchKey != NULL)  free (searchKey);
    /*return the search result*/
    return returnValue;
}


/*removes the minimum key in tree rooted at h*/
/*asserts that h is not NULL*/
/*since release@2020.2*/
static RBTNode* rbt_actual_remove_min(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    /*check if h is the left most node*/
    if (h->left == NULL) {
        /*free memory allocated to h*/
        free(h);
        /*replace h with a NULL link*/
        return NULL;
    }
    /*check if we need to move red node*/
    if (!isRed(h->left) && !isRed(h->left->left))
        h = move_red_left(h);
    /*delete in left subtree of h and update its left*/
    h->left = rbt_actual_remove_min(h->left);
    /*balance rbt about h and return root*/
    return rbt_balance(h);
}
/*returns and removes the minimum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
void* rbt_remove_min(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*get the minimum node in rbt*/
    void* minimum = rbt_min(rbt);
    /*check if minimum exist*/
    if (minimum == NULL)    return NULL;
    /*delete the minimum node in tree*/
    if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
        rbt->root->color = RED;
    /*delete the minimum in tree rooted at root*/
    rbt->root = rbt_actual_remove_min(rbt->root);
    /*if root exist then color it black*/
    if (rbt->root != NULL)
        rbt->root->color = BLACK;
    /*return the value of node deleted*/
    return minimum;
}

/*removes the maximum key in tree rooted at h*/
/*asserts that h is not NULL*/
/*since release@2020.2*/
static RBTNode* rbt_actual_remove_max(RBTNode* h){
    /*make an assertion on h*/
    assert (h != NULL);
    /*check if left child is a red node*/
    if(isRed(h->left))
        /*make a right rotation about current node*/
        h = rotate_right(h);
    /*check if this is the rightmost node*/
    if (h->right == NULL){
        /*free memory allocated to current node*/
        free (h);
        /*replace this node with a NULL link*/
        return NULL;
    }
    /*check if we need to move red node towards right*/
    if (!isRed(h->right) && !isRed(h->right->left))
        h = move_red_right(h);
    /*delete in right subtree of current tree*/
    h->right = rbt_actual_remove_max(h->right);
    /*balance about current node and return result*/
    return rbt_balance(h);
}
/*returns and removes the maximum node in rbt if exist otherwise returns NULL*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
void* rbt_remove_max(RBT* rbt){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*get the maximum node in rbt*/
    void* maximum = rbt_max(rbt);
    /*check if maximum exist*/
    if (maximum == NULL)    return NULL;
    /*delete the maximum node in tree*/
    /*check if root is to be colored red*/
    if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
        rbt->root->color = RED;
    /*delete the minimum in tree rooted at root*/
    rbt->root = rbt_actual_remove_max(rbt->root);
    /*if root exist then color it black*/
    if (rbt->root != NULL)
        rbt->root->color = BLACK;
    /*return the value of node deleted*/
    return maximum;
}

/*removes the key from tree rooted at root and returns the new root of the rbt*/
/*since release@2020.2*/
static RBTNode* actual_rbt_remove(RBTNode* h, void* key, Comparator comparator){
    /*make a comparison between key and root's data*/
    int cmp = (*comparator)(key, h->data);
    /*take decision based on comparison result*/
    if ( (*comparator)(key, h->data) < 0){
        /*check if we need to move red node to left*/
        if (!isRed(h->left) && !isRed(h->left->left))
            h = move_red_left(h);
        /*delete in left subtree*/
        h->left = actual_rbt_remove(h->left, key, comparator);
    } else {
        /*check if left child is red colored*/
        if (isRed(h->left))
            /*rotate about current node*/
            h = rotate_right(h);
        if ((*comparator)(key, h->data) == 0 && h->right == NULL){
            /*free memory allocated to current node*/
            free (h);
            /*replace current node by a NULL link*/
            return NULL;
        }
        /*check if we can move red node to right*/
        if (!isRed(h->right) && !isRed(h->right->left))
            h = move_red_right(h);
        if ((*comparator)(key, h->data) == 0){
            /*get the successor node*/
            RBTNode* x = rbt_subtree_min(h->right);
            /*copy successor's data to current node*/
            h->data = x->data;
            /*delete successor from right subtree*/
            h->right = rbt_actual_remove_min(h->right);
        } else {
            /*delete in right subtree*/
            h->right = actual_rbt_remove(h->right, key, comparator);
        }
    }
    /*restore rbt invariant about current node and return new node*/
    return rbt_balance(h);
}

/*returns and removes the key from rbt if exist otherwise returns NULL*/
/*optionally frees the memory allocated to key at the end of the operation*/
/*asserts that rbt and comparator are not NULL*/
/*since release@2020.2*/
void* rbt_remove(RBT* rbt, void* key, Comparator comparator, bool freeKeyAtEnd){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*search for key in rbt*/
    void* node = rbt_value(rbt, key, comparator, false);
    /*check if key exist in rbt*/
    if (node == NULL){
        /*key do not exist in rbt - free memory allocated to key*/
        if (freeKeyAtEnd && key != NULL) free (key);
        /*return NULL to caller*/
        return NULL;
    }
    /*get the old size of the tree*/
    int old_size = rbt_subtree_size(rbt->root);

    /*if both children of root are black, set root to red*/
    if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
        rbt->root->color = RED;
    /*delete node and update root*/
    rbt->root = actual_rbt_remove(rbt->root, key, comparator);
    /*update color of root is it exist*/
    if (rbt->root != NULL)  rbt->root->color = BLACK;

    /*get the new size of the tree*/
    int new_size = rbt_subtree_size(rbt->root);
    /*check if we have to free key*/
    if (freeKeyAtEnd && key != NULL)    free (key);
    /*compare the sizes*/
    if (new_size == old_size - 1)
        /*return the deleted node*/
        return node;
    else
        /*deletion failed*/
        return NULL;
}

/*frees the memory allocated to tree rooted at root*/
/*optionally frees the memory allocated to its nodes*/
/*since release@2020.2*/
static void actual_free_rbt(RBTNode* h, bool freeKeys){
    if (h != NULL){
        /*first we free memory allocated to left subtree*/
        actual_free_rbt(h->left, freeKeys);
        /*next we free memory allocated to right child*/
        actual_free_rbt(h->right, freeKeys);
        /*we optionally free memory allocated to key*/
        if (freeKeys && h->data != NULL)
            free (h->data);
        /*finally we free the memory allocated to root node*/
        free (h);
    }
}
/*frees the memory allocated to rbt*/
/*optionally frees the memory allocated to its nodes*/
/*asserts that rbt is not NULL*/
/*since release@2020.2*/
void free_rbt(RBT* rbt, bool freeKeys){
    /*make an assertion on rbt*/
    assert (rbt != NULL);
    /*free memory allocated to nodes in post order fashion*/
    actual_free_rbt(rbt->root, freeKeys);
    /*free memory allocated to  RBT*/
    free (rbt);
}