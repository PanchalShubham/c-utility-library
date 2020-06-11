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

#include "../rbt.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/*declaration of structure TreeMapNode*/
typedef struct TreeMapNode{
    /*each tree-map node has a value and key*/
    void* key; void* value;
}TreeMapNode;
/*declaration of structure tree-map*/
typedef struct TreeMap{
    /*each tree map has a rbt*/
    RBT* rbt;
    /*each tree map has its own comparator*/
    Comparator comparator;
}TreeMap;

/*allocates memory for new tree-map-node on heap and returns a pointer to it if succeeds otherwise returns NULL*/
static TreeMapNode* tree_map_node(void* key, void* value){
    /*allocate memory for new tree-map-node*/
    TreeMapNode* treeMapNode = (TreeMapNode*)malloc(sizeof(TreeMapNode));
    /*validate memory allocation and update fields*/
    if (treeMapNode != NULL){
        /*update fields of tree-map-node*/
        treeMapNode->key = key; treeMapNode->value = value;
    }
    /*return the memory allocated to new tree-map-node*/
    return treeMapNode;
}

/*define a comparator for tree-map-node*/
int treeMapNodeComparator(const void* node1, const void* node2){
    /*compare */
}

/*creates a new tree map and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that comparator is not NULL*/
/*since release@2020.2*/
TreeMap* new_tree_map(Comparator comparator){
    /*make an assertion on comparator*/
    assert (comparator != NULL);
    /*allocate memory for new tree-map*/
    TreeMap* treeMap = (TreeMap*)malloc(sizeof(TreeMap));
    /*validate memory allocation*/
    if (treeMap != NULL){
        /*create a new rbt*/
        treeMap->rbt = new_rbt();
        /*update comparator for*/
    }
    /*return newly created tree-map*/
    return treeMap;
}

/*adds a new key-value pair to map; if already exist then overwrites the data*/
/*asserts that tree-map and comparator are not NULL*/
/*since release@2020.2*/
void tree_map_put(TreeMap* treeMap, void* key, void* value, Comparator keyComparator){
    /*make an assertion on tree-map*/
    assert (treeMap != NULL);
    /*make an assertion on comparator*/
    assert (keyComparator != NULL);
    /*insert key-value in rbt of tree-map*/
    rbt_put(treeMap->rbt, tr)
}