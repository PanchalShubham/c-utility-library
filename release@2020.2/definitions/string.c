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
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "../linkedlist.h"
#include "../wrapper.h"

/*declaration of type String*/
/*String instances are immutable*/
typedef struct StringObject{
    /*value is used to store characters*/
    const char* const value;
    /*each string object has a length*/
    const int length;
}String;

/*declaration of type StringBuilder*/
typedef struct StringBuilder{
    /*each string builder has a value*/
    char* value;
    /*each string builder has length*/
    int length;
}StringBuilder;





/*creates a new string builder on heap and returns a pointer to it if succeeds otherwise returns NULL*/
StringBuilder* new_string_builder(void);

/*appends the stringLiteral to the end of string builder*/
/*assert that stringBuilder and stringLiteral are not NULL*/
void string_builder_append(StringBuilder* stringBuilder, const char* stringLiteral);

/*creates a new string builder out of given string builder and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that string builder is not NULL*/
StringBuilder* string_builder_copyOf(StringBuilder* stringBuilder);

/*returns the string representation of StringBuilder*/
/*asserts that stringBuilder is not NULL*/
/*frees the memory allocated to string builder*/
String string_builder_value(StringBuilder* stringBuilder);












/*creates a new string object out of given string literal*/
/*asserts that stringLiteral is not NULL*/
String new_string(const char* stringLiteral){
    /*assert that stringLiteral is not NULL*/
    assert (stringLiteral != NULL);
    /*get the length of the string literal*/
    int len = 0; while (stringLiteral[len] != '\0') len++;
    /*allocate memory for (len + 1) characters on heap*/
    char* value = (char*)malloc(sizeof(char)*(len + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*copy stringLiteral to value*/
        for (int i = 0; i < len + 1; ++i) value[i] = stringLiteral[i];
        /*create a new String instance*/
        String string = {.value = value, .length = len};
        /*return newly created string*/
        return string;
    } else {
        /*create a new String instance*/
        String string = {.value = NULL, .length = 0};
        /*return a new string*/
        return string;
    }
}

/*creates a new string object out of given string literal*/
/*asserts that stringLiteral is not NULL and indices are in bound*/
String new_string_offset(const char* stringLiteral, int low, int high){
    /*assert that stringLiteral is not NULL*/
    assert (stringLiteral != NULL);
    /*get the length of the string literal*/
    int len = 0; while (stringLiteral[len] != '\0') len++;
    /*make an assertion on low and high*/
    assert (0 <= low && low <= high && high < len);
    /*allocate memory for (len + 1) characters on heap*/
    char* value = (char*)malloc(sizeof(char)*(high - low + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*copy stringLiteral to value*/
        for (int i = 0, j = low; j <= high ; ++j,++i) value[i] = stringLiteral[j];
        /*create a new String instance*/
        String string = {.value = value, .length = high - low + 1};
        /*return the newly created string*/
        return string;
    } else {
        /*create a new String instance*/
        String string = {.value = NULL, .length = 0};
        /*return newly created string*/
        return string;
    }
}


/*creates a new string object out of given String object*/
/*asserts that string value is not NULL and input string is not NULL*/
String string_copyOf(const String str){
    /*assert that str-value is not NULL*/
    assert (str.value != NULL);
    /*get the length of the string literal*/
    int len = 0; while (str.value[len] != '\0') len++;
    /*allocate memory for (len + 1) characters on heap*/
    char* value = (char*)malloc(sizeof(char)*(len + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*copy stringLiteral to value*/
        for (int i = 0; i < len + 1; ++i) value[i] = str.value[i];
        /*create a new String instance*/
        String string = {.value = value, .length = len};
        /*return the newly created string*/
        return string;
    } else {
        /*create a new String instance*/
        String string = {.value = NULL, .length = 0};
        /*return newly created string*/
        return string;
    }
}

/*concatenates str1 and str2 and returns a new string instance*/
/*assert that str1.value and str2.value aren't NULL*/
String string_concat(const String str1, const String str2){
    /*make an assertion on input strings*/
    assert (str1.value != NULL && str2.value != NULL);
    /*get the sum of lengths of two strings*/
    int length = str1.length + str2.length;
    /*allocate memory for (length + 1) many characters*/
    char* value = (char*)malloc(sizeof(char)*(length + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*iterate through both strings and write content to new string*/
        int index = 0;
        /*append string1*/
        for (int i = 0; i < str1.length; ++i) value[index++] = str1.value[i];
        /*append string2*/
        for (int i = 0; i < str2.length; ++i) value[index++] = str2.value[i];
        /*append a null character at the end*/
        value[index] = '\0';
        /*create a new String instance*/
        String string = {.value = value, .length = length};
        /*return newly created string*/
        return string;
    } else {
        /*create a new string*/
        String string = {.value = NULL, .length = 0};
        /*return newly created string*/
        return string;
    }
}


/*returns the sub-string from index start to index end of given String*/
/*asserts that indices are valid and string value is not NULL*/
String string_substring(const String string, int start, int end){
    /*make an assertion on indices*/
    assert (0 <= start && start <= end && end < string.length);
    /*make an assertion on value of input string*/
    assert (string.value != NULL);
    /*allocate memory for (end - start + 1) characters*/
    char* value = (char*)malloc(sizeof(char)*(end - start + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*used for indexing in value*/
        int index = 0;
        /*copy content from original string to value*/
        for (int i = start; i <= end; ++i) value[index++] = string.value[i];
        /*add a null character at the end*/
        value[index] = '\0';
        /*create a new string*/
        String newString = {.value = value, .length = end - start + 1};
        /*return newly created string*/
        return newString;
    } else {
        /*create a new String*/
        String newString = {.value = NULL, .length = 0};
        /*return newly created string*/
        return newString;
    }
}

/*returns true if given string start with prefix*/
/*asserts that string value and prefix are not NULL*/
bool string_starts_with(const String string, const char* prefix){
    /*make an assertion on input*/
    assert (string.value != NULL && prefix != NULL);
    /*get the length of the prefix*/
    int p = 0; while (prefix[p] != '\0') p++;
    /*get the length of input string*/
    int l = string.length;
    /*if p <= l then we can make character by character comparison*/
    if (p <= l){
        /*compare character by character*/
        for (int i = 0; i < p; ++i)
            /*perform a comparison between ith character*/
            if (string.value[i] != prefix[i])
                /*character mismatch*/
                return false;
        /*all characters matched and hence string starts with given prefix*/
        return true;
    }
    /*prefix is longer than string and hence string doesn't start with prefix*/
    return false;
}

/*returns true if given string ends with suffix*/
/*asserts that string value and suffix are not NULL*/
bool string_ends_with(const String string, const char* suffix){
    /*make an assertion on input*/
    assert (string.value != NULL && suffix != NULL);
    /*get the length of the suffix*/
    int p = 0; while (suffix[p] != '\0') p++;
    /*get the length of input string*/
    int l = string.length;
    /*if p <= l then we can make character by character comparison*/
    if (p <= l){
        /*compare character by character*/
        for (int pi = p - 1, li = l - 1; pi >= 0; --pi, --li)
            /*perform a comparison between ith character*/
            if (string.value[li] != suffix[pi])
                /*character mismatch*/
                return false;
        /*all characters matched and hence string ends with given suffix*/
        return true;
    }
    /*prefix is longer than string and hence string doesn't ends with suffix*/
    return false;
}

/*returns a linked list of zero-based indices of substring in given string*/
/*optionally ignores the case*/
/*asserts that string value and substring are not NULL*/
/*uses KMP string matching algorithm*/
LinkedList* string_indexOf(const String string, const char* substring, bool isCaseSensitive) {
    /*make an assertion on input*/
    assert (string.value != NULL && substring != NULL);
    /*create a new linked list*/
    LinkedList *linkedList = new_linked_list();
    /*create a pattern + $ + text string*/
    StringBuilder *stringBuilder = new_string_builder();
    /*append content to string builder*/
    string_builder_append(stringBuilder, substring);
    string_builder_append(stringBuilder, "$");
    string_builder_append(stringBuilder, string.value);
    /*get the equivalent string*/
    String string1 = string_builder_value(stringBuilder);
    /*get the length of new string*/
    int n = string1.length;
    /*create an array of size n*/
    int prefix[n], border;
    /*base case*/
    prefix[0] = 0; border = 0;
    /*compute the prefix function*/
    for (int i = 1; i < n; ++i){
        /*iterate and find the length of the border*/
        while (border > 0 && string1.value[i] != string1.value[border])
            border = prefix[border - 1];
        /*update the value of the border*/
        border = string1.value[i] == string1.value[border] ? border + 1 : 0;
        /*update the prefix for ith entry*/
        prefix[i] = border;
    }
    /*get the length of the substring*/
    int p = 0; while (substring[p] != '\0') ++p;
    /*iterate through prefix function*/
    for (int i = 0; i < n; ++i)
        if (prefix[i] == p)
            linked_list_insert_back(linkedList, wrap_int(i - 2*p));
    /*free memory allocated to string1*/
    free ((void*)string1.value);
    /*return the linked list of indices*/
    return linkedList;
}

/*returns true if the given string contains substring*/
/*optionally ignores the case*/
/*asserts that string value and substring are not NULL*/
bool string_contains(const String string, const char* substring, bool isCaseSensitive){
    /*get the indices of substring in string*/
    LinkedList* list = string_indexOf(string, substring, isCaseSensitive);
    /*check if size of linked list is greater than zero*/
    bool result = linked_list_size(list) > 0;
    /*free memory allocated to linked list along with its keys*/
    free_linked_list(list, true);
    /*return computed result*/
    return result;
}

/*transforms  the string to lowercase or uppercase appropriately*/
/*asserts that string value is not NULL*/
static String string_transform(const String string, bool toUpper){
    /*make an assertion on string value*/
    assert (string.value != NULL);
    /*allocate memory for (string.length + 1) characters*/
    char* value = (char*)malloc(sizeof(char)*(string.length + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*populate data in value*/
        for (int i = 0; i < string.length; ++i)
            /*update the value of ith character*/
            value[i] = (char)(toUpper ? toupper(string.value[i]) : tolower(string.value[i]));
        /*create a new instance of string*/
        String lowerString = {.value = value, .length = string.length};
        /*return newly created string*/
        return lowerString;
    } else {
        /*create a new string*/
        String newString = {.value = NULL, .length = 0};
        /*return newly created string*/
        return newString;
    }
}

/*returns the lowercase representation of given string*/
/*asserts that string value is not NULL*/
String string_lowercase(const String string){
    /*transform string to lowercase*/
    return string_transform(string, false);
}

/*returns the uppercase representation of given string*/
/*asserts that string value is not NULL*/
String string_uppercase(const String string){
    /*transform string to uppercase*/
    return string_transform(string, true);
}

/*compares string1 and string2 and returns -1, 0, 1 appropriately*/
/*asserts that value of strings are not NULL*/
int string_compare(const String string1, const String string2){
    /*make an assertion on values of strings*/
    assert (string1.value != string2.value);
    /*return the comparison result*/
    return strcmp(string1.value, string2.value);
}

/*returns true content of both strings are same otherwise returns false*/
/*asserts that value of strings are not NULL*/
bool string_equals(const String string1, const String string2){
    /*make a comparison and check if comparison results zero*/
    return (string_compare(string1, string2) == 0);
}


/*returns the long representation of string*/
/*asserts that string value is not NULL and
 * contains only digits optionally starting with + or -*/
long string_to_long(const String string){
    /*make an assertion on string value*/
    assert (string.value != NULL);
    /*get the length of the string*/
    int length = string.length;
    /*stores the start index*/
    int startIndex = (length > 0 && string.value[0] == '+' || string.value[0] == '-') ? 1 : 0;
    /*iterate thourgh each and every character and assert that it is digit*/
    for (int i = startIndex; i < length; ++i)
        /*make an assertion on ith character*/
        assert (isdigit(string.value[i]));
    /*if all conditions are satisfied then we cast string to integer*/
    return strtol(string.value, NULL, 10);

}
/*returns the double representation of string*/
/*asserts that string value is not NULL and
 * contains of only digits optionally starting with + or - sign
 * and at most one period*/
double string_to_double(const String string){
    /*make an assertion on value of string*/
    assert (string.value != NULL);
    /*get the length of the string*/
    int length = string.length;
    /*stores the start index*/
    int startIndex = (length > 0 && string.value[0] == '+' || string.value[0] == '-') ? 1 : 0;
    /*check if all characters are digit and it contains exactly one period*/
    int periodCount = 0;
    /*iterate through each character*/
    for (int i = startIndex; i < length; ++i){
        /*make an assertion on ith character*/
        assert (isdigit(string.value[i]) || string.value[i] == '.');
        /*if it is period then increase the count of period*/
        periodCount += string.value[i] == '.' ? 1 : 0;
        /*assert that count of period is at most 1*/
        assert (periodCount <= 1);
    }
    /*if every constraint is passed then we convert string to double*/
    return strtod(string.value, NULL);
}

/*returns the character at given index in string*/
/*asserts that index is in bound and string value is not NULL*/
char string_charAt(String string, int index){
    /*make an assertion on index*/
    assert (0 <= index && index < string.length);
    /*make an assertion on string value*/
    assert (string.value != NULL);
    /*return the value at given index*/
    return string.value[index];
}

/*frees the memory allocated to string*/
/*asserts that string is not NULL*/
void free_string(String* string){
    /*make an assertion on input string*/
    assert (string != NULL);
    /*free memory allocated to value of string (if not NULL)*/
    if (string->value != NULL) free ((void*)string->value);
}






/*creates a new string builder on heap and returns a pointer to it if succeeds otherwise returns NULL*/
StringBuilder* new_string_builder(void){
    /*allocate memory for new string builder*/
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));
    /*validate memory allocation*/
    if (sb != NULL){
        /*update fields of string builder*/
        sb->value = NULL;
        /*update the size of string builder*/
        sb->length = 0;
    }
    /*return newly created string builder*/
    return sb;
}

/*appends the stringLiteral to the end of string builder*/
/*assert that stringBuilder and stringLiteral are not NULL*/
void string_builder_append(StringBuilder* stringBuilder, const char* stringLiteral){
    /*make an assertion on stringBuilder*/
    assert (stringBuilder != NULL);
    /*make an assertion on stringLiteral*/
    assert (stringLiteral != NULL);
    /*get the old length of stringBuilder and length of stringLiteral*/
    int length1 = stringBuilder->length;
    int length2 = 0; while(stringLiteral[length2] != '\0') length2++;
    /*allocate memory for (length1 + length2 + 1) characters*/
    char* value = (char*)malloc(sizeof(char)*(length1 + length2 + 1));
    /*validate memory allocation*/
    if (value != NULL){
        /*used for indexing in value*/
        int index = 0;
        /*copy content of string builder to value*/
        for (int i = 0; i < length1; ++i) value[index++] = stringBuilder->value[i];
        /*copy content of string literal*/
        for (int i = 0; i < length2; ++i) value[index++] = stringLiteral[i];
        /*append a null character at the end of the string*/
        value[index] = '\0';
        /*free memory allocated to old value*/
        if (stringBuilder->value != NULL) free (stringBuilder->value);
        /*update the value of string builder*/
        stringBuilder->value = value;
        /*update the length of the string literal*/
        stringBuilder->length = length1 + length2;
    }
}

/*creates a new string builder out of given string builder and returns a pointer to it if succeeds otherwise returns NULL*/
/*asserts that string builder is not NULL*/
StringBuilder* string_builder_copyOf(StringBuilder* stringBuilder){
    /*make an assertion on stringBuilder*/
    assert (stringBuilder != NULL);
    /*create a new String builder*/
    StringBuilder* sb = new_string_builder();
    /*append the content of old string builder*/
    string_builder_append(sb, sb->value);
    /*return newly created string builder*/
    return sb;
}

/*returns the string representation of StringBuilder*/
/*asserts that stringBuilder is not NULL*/
/*frees the memory allocated to string builder*/
String string_builder_value(StringBuilder* stringBuilder){
    /*make an assertion on stringBuilder*/
    assert (stringBuilder != NULL);
    /*create a new String*/
    String string = {.value = stringBuilder->value, .length = stringBuilder->length};
    /*free memory allocated to stringBuilder*/
    free (stringBuilder);
    /*set stringBuilder to NULL*/
    stringBuilder = NULL;
    /*return the newly created string*/
    return string;
}
