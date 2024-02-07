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
int string__add(string* self, const char* chars) {
    string__append(self,chars,strlen(chars));
    return 0;
}

// Function to append a string to another string
int string__append(string* self, const char* chars,size_t num_chars) {
    if (self == NULL || self->buffer == NULL || chars == NULL) {
        return -1;
    }
    size_t new_len = self->len + num_chars;
    char* new_str = (char*)realloc(self->buffer, new_len + 1);
    if (new_str == NULL) {
        return -1;
    }
    strncat(new_str, chars,num_chars);
    self->buffer = new_str;
    self->len = new_len;
    return 0;
}

string_slice* string__get_slice(string* self, int start, int end) {
    string_slice* slice = (string_slice*)malloc(sizeof(string_slice));
    slice->buffer = self->buffer + start;
    slice->len = end - start;
    slice->underlying_string=self;
    return slice;
}

int string_slice__free(string_slice* self){
    free(self);
    return 0;
}

// Function to extract text inside a tag using the string struct
int string__find_tagged_substrings(string* xml, const char* opening_tag, const char* closing_tag,string* result) {
    if (xml == NULL || xml->buffer == NULL ) {
        return -1;
    }
    if(opening_tag == NULL) {
        return -2;
    }
    if(closing_tag == NULL) {
        return -3;
    }
    if(result == NULL) {
        return -4;
    }
    int opening_tags_count = 0;
    char* start = NULL;

    size_t opening_tag_size = strlen(opening_tag);
    size_t closing_tag_size = strlen(closing_tag);

    size_t found_count=0;
    // Iterate through the XML string
    char* ptr = xml->buffer;
    //printf("=== start %s>..%s",opening_tag,closing_tag);
    while (*ptr != '\0') {
        if (*ptr == '<') {//
            //printf("found start char < @ index %d in %s\n",index,ptr);
            // Check for opening tag
            if (strncmp(ptr, opening_tag, opening_tag_size) == 0) {
                //printf("next %d chars match opening tag %s in %s\n",opening_tag_size,opening_tag,ptr);
                // Increment the opening tags count
                opening_tags_count++;
                if (opening_tags_count == 1) {
                    // Save the start pointer
                    start = ptr;
                    //printf("stored start index %d for the first occurence of %s in %s\n",index,opening_tag,ptr);
                }
            }
            // Check for closing tag
            else if (strncmp(ptr, closing_tag, closing_tag_size) == 0) {
                //printf("next %d chars match closing tag %s in %s\n",closing_tag_size,closing_tag,ptr);
                if (opening_tags_count > 0) {
                    // Decrement the opening tags count
                    opening_tags_count--;
                    if (opening_tags_count == 0 && start != NULL) {
                        // Exit the loop if both start and end pointers are set
                        //printf("stored end index %d for the last occurence of %s in %s\n",index + closing_tag_size,closing_tag,ptr);
                        int text_length = ptr + closing_tag_size - start;
                        string__append(result,start,text_length);
                        start=NULL;
                    }
                }
            }
        }
        // Move to the next character
        ptr++;
        found_count++;
    }
    return found_count;
}



#endif