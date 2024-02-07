#ifndef _STRINGS_H
#define _STRINGS_H

// Define the string struct
typedef struct string {
    char* buffer;
    int len;
} string;

string* string__alloc(const char* init_val);
int string__free(string* self);
int string_strstr(string* self,const char* find_str);
int string__concat(string* self,string* other);
int string__concat(string* self,string* other);
int string__append(string* self,const char* chars);


#endif