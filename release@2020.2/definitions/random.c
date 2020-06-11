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

/*include necessary header*/
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

/*seeds the random number generator*/
/*since release@2020.1*/
void randomize(void){
    /*seed the random number generator*/
    srand(time(NULL));
}


/*generates a random integer*/
/*since release@2020.1*/
int random_int(void){
    /*generate a random number and return to caller*/
    return rand();
}

/*generates a random integer with given upper bound i.e. in range [0...upper_bound]*/
/*asserts that upper bound is a non-negative integer*/
/*since release@2020.1*/
int random_int_upper_bound(int upper_bound){
    /*make an insertion on upper bound*/
    assert (upper_bound >= 0);
    /*return newly generator random number*/
    return (rand() % (upper_bound + 1));
}

/*generates a random integer withing given bounds i.e. in range [lower_bound...upper_bound]*/
/*asserts that 0 <= lower_bound <= upper_bound*/
/*since release@2020.1*/
int random_int_range(int lower_bound, int upper_bound){
    /*make an insertion on upper bound*/
    assert ( 0 <= lower_bound && lower_bound <= upper_bound);
    /*return newly generator random number*/
    return ((rand() % (upper_bound - lower_bound + 1)) + lower_bound);
}

/*generates a random double in range [0,1]*/
/*since release@2020.1*/
double random_double(void){
    /*return a new random number*/
    return rand () / (double)RAND_MAX;
}

/*generates a random double with given upper bound i.e. in range [0...upper_bound]*/
/*asserts that upper bound is a non-negative integer*/
/*since release@2020.1*/
double random_double_upper_bound(double upper_bound){
    /*make an insertion on upper bound*/
    assert (upper_bound >= 0);
    /*returns a newly generated random number in given bound*/
    return upper_bound*random_double();
}


/*generates a random double within given bounds i.e. in range [lower_bound...upper_bound]*/
/*asserts that 0 <= lower_bound <= upper_bound*/
/*since release@2020.1*/
double random_double_range(double lower_bound, double upper_bound){
    /*make an insertion on upper bound*/
    assert ( 0 <= lower_bound && lower_bound <= upper_bound);
    /*returns a newly generated random number in given bound*/
    return ((upper_bound - lower_bound)*random_double() + lower_bound);
}



/*generates a random binary string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_binary_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* binary_string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (binary_string == NULL)
        return NULL;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        binary_string[i] = random_int_upper_bound(1) + '0';
    /*set last character of string to null character*/
    binary_string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return binary_string;
}

/*generates a random octal string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_octal_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* oct_string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (oct_string == NULL)
        return NULL;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        oct_string[i] = random_int_upper_bound(7) + '0';
    /*set last character of string to null character*/
    oct_string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return oct_string;
}

/*generates a random decimal string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_decimal_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* decimal_string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (decimal_string == NULL)
        return NULL;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        decimal_string[i] = random_int_upper_bound(9) + '0';
    /*set last character of string to null character*/
    decimal_string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return decimal_string;
}

/*generates a random hexadecimal string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_hex_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*collection of characters for hexadecimal*/
    char possible_values[] = "0123456789abcdef";
    /*get the length of possible values*/
    int size = (int)strlen(possible_values) - 1;
    /*allocate memory for (length + 1) characters on heap*/
    char* hex_string = (char*)malloc(sizeof(char)*(length + 1));
    /*validate memory allocation*/
    if (hex_string == NULL)
        return NULL;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        hex_string[i] = possible_values[random_int_upper_bound(size)];
    /*set last character of string to null character*/
    hex_string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return hex_string;
}


/*generates a random printable string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_printable_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (string == NULL)
        return NULL;
    /*set of characters available*/
    char possible_values[] = "`~!@#$%^&*()_+-={}[]|\\:;\'\"?/<>,. 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /*get the length of the possible strings*/
    int size = (int)strlen(possible_values) - 1;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        /*select any character from possible set of characters*/
        string[i] = possible_values[random_int_upper_bound(size)];
    /*set last character of string to null character*/
    string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return string;
}


/*generates a random alphabetical string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_alphabetical_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (string == NULL)
        return NULL;
    /*set of characters available*/
    char possible_values[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /*get the length of the possible strings*/
    int size = (int)strlen(possible_values) - 1;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        /*select any character from possible set of characters*/
        string[i] = possible_values[random_int_upper_bound(size)];
    /*set last character of string to null character*/
    string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return string;
}

/*generates a random alphabetical string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_alphanumeric_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (string == NULL)
        return NULL;
    /*set of characters available*/
    char possible_values[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /*get the length of the possible strings*/
    int size = (int)strlen(possible_values) - 1;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        /*select any character from possible set of characters*/
        string[i] = possible_values[random_int_upper_bound(size)];
    /*set last character of string to null character*/
    string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return string;
}


/*generates a random special characters string of given length on HEAP and returns a pointer to string if succeeds otherwise returns a NULL pointer*/
/*asserts that input length > 0*/
/*since release@2020.1*/
char* random_special_string(int length){
    /*make an assertion on input length*/
    assert (length > 0);
    /*allocate memory for (length + 1) characters on heap*/
    char* string = (char*)malloc(sizeof(char) * (length + 1));
    /*validate memory allocation*/
    if (string == NULL)
        return NULL;
    /*set of characters available*/
    char possible_values[] = "`~!@#$%^&*()_+-={}[]|\\:;\'\"?/<>,.";
    /*get the length of the possible strings*/
    int size = (int)strlen(possible_values) - 1;
    /*iterate through each character and populate string*/
    for (int i = 0; i < length; ++i)
        /*select any character from possible set of characters*/
        string[i] = possible_values[random_int_upper_bound(size)];
    /*set last character of string to null character*/
    string[length] = '\0';
    /*return newly created random hexadecimal string*/
    return string;
}