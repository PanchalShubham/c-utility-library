/*
    This file is a part of utility library.
    https://github.com/PanchalShubham/UtilityLibrary
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
#include <assert.h>

/*define the type pair*/
typedef struct Pair{
    /*each pair has two fields called first and second*/
    void* first; void* second;
}Pair;

/*creates a new pair on heap and returns a pointer to it if succeeds otherwise returns NULL*/
Pair* create_new_pair(void* first, void* second){
    /*allocate memory for one pair on heap*/
    Pair* pair = (Pair*)malloc(sizeof(Pair));
    /*validate memory allocation*/
    if (pair != NULL){
        /*update fields of pair*/
        pair->first = first; pair->second = second;
    }
    /*return newly created pair*/
    return pair;
}


/*update the first element of the pair*/
/*asserts that pair is not NULL*/
void pair_update_first(Pair* pair, void* new_first){
    /*make an assertion on pair*/
    assert (pair != NULL);
    /*update first element of pair*/
    pair->first = new_first;
}

/*update the second element of the pair*/
/*asserts that pair is not NULL*/
void pair_update_second(Pair* pair, void* new_second){
    /*make an assertion on pair*/
    assert (pair != NULL);
    /*update second element of pair*/
    pair->second = new_second;
}

/*returns the first element of the pair*/
/*asserts that pair is not NULL*/
void* pair_first(Pair* pair){
    /*make an assertion on pair*/
    assert (pair != NULL);
    /*return first element of pair*/
    return pair->first;
}

/*returns the second element of the pair*/
/*asserts that pair is not NULL*/
void* pair_second(Pair* pair){
    /*make an assertion on pair*/
    assert (pair != NULL);
    /*return first element of pair*/
    return pair->second;
}


/*frees the memory allocated to pair*/
/*optionally frees the memory allocated to its values*/
/*asserts that pair is not NULL*/
void free_pair(Pair* pair, bool free_values){
    /*make an assertion on pair*/
    assert (pair != NULL);
    /*check if values to be freed*/
    if (free_values){
        /*free if first value exist*/
        if (pair->first != NULL) free (pair->first);
        /*free if second value exist*/
        if (pair->second != NULL) free (pair->second);
    }
    /*free memory allocated to pair*/
    free (pair);
}