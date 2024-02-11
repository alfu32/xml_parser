#ifndef _STRINGS_C
#define _STRINGS_C
#include "../include/strings.h"

const char* string_util__trim_indent(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    // Find the smallest number of spaces at the beginning of each line
    int min_spaces = -1;
    const char* ptr = str;
    while (*ptr != '\0') {
        // Count the number of spaces at the beginning of the current line
        int num_spaces = 0;
        while (*ptr == ' ' || *ptr == '\t') {
            num_spaces++;
            ptr++;
        }

        // Update min_spaces if necessary
        if ((min_spaces == -1 || num_spaces < min_spaces) && *(ptr) != '\0' && *(ptr) != '\n') {
            min_spaces = num_spaces;
        }

        // Move to the next line
        while (*ptr != '\0' && *ptr != '\n') {
            ptr++;
        }

        // Skip the newline character
        if (*ptr == '\n') {
            ptr++;
        }
    }
    // printf("min spaces for \n %s \n is %d\n",str,min_spaces);
    // Allocate memory for the trimmed string_t
    char* trimmed_str = (char*)malloc(strlen(str) + 1);
    if (trimmed_str == NULL) {
        return NULL;
    }
    char* trimmed_ptr = trimmed_str;

    // Trim the same number of spaces from the beginning of each line
    ptr = str;
    while (*ptr != '\0') {
        // Copy characters to trimmed string_t
        *trimmed_ptr = *ptr;
        // putchar(*ptr);

        if (*ptr == '\n') {
            int k=0;
            while((*ptr == '\n' || *ptr == ' ' || *ptr == '\t') && k<min_spaces){
                ptr++;
                k++;
                
            }
        }
        ptr++;
        trimmed_ptr++;
    }

    // Null-terminate the trimmed string_t
    *trimmed_ptr = '\0';

    return trimmed_str;
}

// Function to allocate a string_t with an initial value
string_t* string__alloc(const char* init_val) {
    string_t* new_str = (string_t*)malloc(sizeof(string_t));
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
string_t* string__copy(string_t* init_val){
    return string__alloc(init_val->buffer);
}

// Function to free a string_t
int string__free(string_t* self) {
    if (self != NULL) {
        if (self->buffer != NULL) {
            free(self->buffer);
        }
        free(self);
    }
    return 0;
}

// Function to find a substring in a string_t and return its position
int string__index_of(string_t* self, const char* find_str) {
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
int string__concat(string_t* self, string_t* other) {
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

// Function to append a string_t to another string_t
int string__add(string_t* self, const char* chars) {
    string__append(self,chars,strlen(chars));
    return 0;
}

// Function to append a string_t to another string_t
int string__append(string_t* self, const char* chars,size_t num_chars) {
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

string_slice* string__get_slice(string_t* self, int start, int end) {
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

// Function to extract text inside a tag using the string_t struct
int string__find_tagged_substrings(string_t* xml, const char* opening_tag, const char* closing_tag,string_t* result) {
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
    // Iterate through the XML string_t
    char* ptr = xml->buffer;
    while (*ptr != '\0') {
        if (*ptr == opening_tag[0] && strncmp(ptr, opening_tag, opening_tag_size) == 0) {
                // Increment the opening tags count
                if (opening_tags_count == 0) {
                    start = ptr;
                }
                opening_tags_count++;
                ptr+=opening_tag_size-1;
        }
        if (*ptr == closing_tag[0] && strncmp(ptr, closing_tag, closing_tag_size) == 0 && opening_tags_count > 0) {
            // Decrement the opening tags count
            if (opening_tags_count == 1 && start != NULL) {
                // Exit the loop if both start and end pointers are set
                int text_length = ptr + closing_tag_size - start;
                string__append(result,start,text_length);
                string__add(result,"");
                start=NULL;
                found_count++;
            }
            opening_tags_count--;
            ptr+=closing_tag_size-1;
        }
        // Move to the next character
        ptr++;
    }
    return found_count;
}



#endif