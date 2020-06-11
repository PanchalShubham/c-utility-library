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

#ifndef UTILITY_TYPES_H
#define UTILITY_TYPES_H

#include <stdbool.h>

/*compares elements and returns*/
/*-1, 0 or 1 for less than, equal to or greater than respectively*/
/*since release@2020.1*/
typedef int(*Comparator)(const void*, const void*);

/*compares elements and returns true if they are same otherwise returns false*/
/*since release@2020.2*/
typedef bool(*EqualityComparator)(const void*, const void*);

/*swaps values of object pointed to by pointers*/
/*since release@2020.1*/
typedef void(*Swapper)(void*, void*);


#endif