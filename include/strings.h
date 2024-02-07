#ifndef _STRINGS_H
#define _STRINGS_H

#define INHERIT_STRING char* buffer;\
    size_t len;\
    
typedef struct string string;
typedef struct string_slice string_slice;
// Define the string struct
typedef struct string {
    INHERIT_STRING
} string;

string* string__alloc(const char* init_val);
int string__free(string* self);
int string_strstr(string* self,const char* find_str);
int string__concat(string* self,string* other);
int string__append(string* self,const char* chars,size_t num_chars);
int string__add(string* self, const char* chars);
string__find_tagged_substrings(string* xml, const char* opening_tag, const char* closing_tag,string* result);

// Define the string_slice struct
typedef struct string_slice {
    INHERIT_STRING
    string* underlying_string;
} string_slice;

string_slice* string__get_slice(string* self,int start, int end);
int string_slice__free(string_slice* self);


#endif