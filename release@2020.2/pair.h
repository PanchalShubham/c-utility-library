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

#ifndef UTILITY_PAIR_H
#define UTILITY_PAIR_H

/*include source*/
#include "definitions/pair.c"

/*creates a new pair on heap and returns a pointer to it if succeeds otherwise returns NULL*/
extern Pair* create_new_pair(void* first, void* second);

/*update the first element of the pair*/
/*asserts that pair is not NULL*/
extern void utility_pair_update_first(Pair* pair, void* new_first);

/*update the second element of the pair*/
/*asserts that pair is not NULL*/
extern void utility_pair_update_second(Pair* pair, void* new_second);

/*returns the first element of the pair*/
/*asserts that pair is not NULL*/
extern void* utility_pair_first(Pair* pair);

/*returns the second element of the pair*/
/*asserts that pair is not NULL*/
extern void* utility_pair_second(Pair* pair);


/*frees the memory allocated to pair*/
/*optionally frees the memory allocated to its values*/
/*asserts that pair is not NULL*/
extern void free_utility_pair(Pair* pair, bool free_values);

#endif