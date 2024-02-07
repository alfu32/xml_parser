#ifndef _STRINGS_C
#define _STRINGS_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/strings.h"


// Function to allocate a string with an initial value
string* string__alloc(const char* init_val) {
    string* new_str = (string*)malloc(sizeof(string));
    if (new_str != NULL) {
        new_str->len = strlen(init_val);
        new_str->buffer = (char*)malloc(new_str->len + 1);
        if (new_str->buffer != NULL) {
            strcpy(new_str->buffer, init_val);
        } else {
            free(new_str);
            new_str = NULL;
        }
    }
    return new_str;
}

// Function to free a string
int string__free(string* self) {
    if (self != NULL) {
        if (self->buffer != NULL) {
            free(self->buffer);
        }
        free(self);
    }
    return 0;
}

// Function to find a substring in a string and return its position
int string_strstr(string* self, const char* find_str) {
    if (self == NULL || self->buffer == NULL || find_str == NULL) {
        return -1;
    }
    char* position = strstr(self->buffer, find_str);
    if (position == NULL) {
        return -1;
    }
    return (int)(position - self->buffer);
}

// Function to concatenate two strings
int string__concat(string* self, string* other) {
    if (self == NULL || other == NULL || self->buffer == NULL || other->buffer == NULL) {
        return -1;
    }
    char* new_str = (char*)malloc(self->len + other->len + 1);
    if (new_str == NULL) {
        return -1;
    }
    strcpy(new_str, self->buffer);
    strcat(new_str, other->buffer);
    free(self->buffer);
    self->buffer = new_str;
    self->len += other->len;
    return 0;
}

// Function to append a string to another string
int string__append(string* self, const char* chars) {
    if (self == NULL || self->buffer == NULL || chars == NULL) {
        return -1;
    }
    int new_len = self->len + strlen(chars);
    char* new_str = (char*)realloc(self->buffer, new_len + 1);
    if (new_str == NULL) {
        return -1;
    }
    strcat(new_str, chars);
    self->buffer = new_str;
    self->len = new_len;
    return 0;
}


#endif