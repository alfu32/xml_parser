#ifndef _STRINGS_H
#define _STRINGS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INHERIT_STRING char* buffer;\
    size_t len;\
    
typedef struct string_s string_t;
typedef struct string_array_s string_array_t;
typedef struct string_slice_s string_slice_t;
// Define the string_t struct
typedef struct string_s {
    INHERIT_STRING
} string_t;


const char* string_util__trim_indent(const char* str);

string_t* string__alloc(const char* init_val);
string_t* string__copy(string_t* init_val);
int string__free(string_t* self);
int string__index_of(string_t* self,const char* find_str);
int string__concat(string_t* self,string_t* other);
int string__append(string_t* self,const char* chars,size_t num_chars);
int string__add(string_t* self, const char* chars);
int string__find_tagged_substrings(string_t* xml, const char* opening_tag, const char* closing_tag,string_t* result);

// Define the string_slice_t struct
typedef struct string_slice_s {
    INHERIT_STRING
    string_t* underlying_string;
} string_slice_t;

string_slice_t* string__get_slice(string_t* self,int start, int end);
int string_slice__free(string_slice_t* self);

typedef struct string_array_s {
    INHERIT_STRING
    string_t* items;
    size_t items_len;
} string_array_t;

string_array_t* string_array__alloc_init_from_buffer(const char* init_val);
string_array_t* string_array__alloc_init_from_string(string_t* init_val);
string_array_t* string_array__copy(string_t* init_val);
int string_array__split(string_array_t* arr,char delimiter);

#endif