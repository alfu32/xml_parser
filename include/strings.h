#ifndef _STRINGS_H
#define _STRINGS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INHERIT_STRING char* buffer;\
    size_t len;\
    
typedef struct string string;
typedef struct string_array string_array;
typedef struct string_slice string_slice;
// Define the string struct
typedef struct string {
    INHERIT_STRING
} string;


const char* string_util__trim_indent(const char* str);

string* string__alloc(const char* init_val);
string* string__copy(string* init_val);
int string__free(string* self);
int string__index_of(string* self,const char* find_str);
int string__concat(string* self,string* other);
int string__append(string* self,const char* chars,size_t num_chars);
int string__add(string* self, const char* chars);
int string__find_tagged_substrings(string* xml, const char* opening_tag, const char* closing_tag,string* result);

// Define the string_slice struct
typedef struct string_slice {
    INHERIT_STRING
    string* underlying_string;
} string_slice;

string_slice* string__get_slice(string* self,int start, int end);
int string_slice__free(string_slice* self);

typedef struct string_array {
    INHERIT_STRING
    string* items;
    size_t items_len;
} string_array;

string_array* string_array__alloc_init_from_buffer(const char* init_val);
string_array* string_array__alloc_init_from_string(string* init_val);
string_array* string_array__copy(string* init_val);
int string_array__split(string_array* arr,char delimiter);

#endif