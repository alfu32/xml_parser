#ifndef _strings_test_c
#define _strings_test_c

#include <stdio.h>
#include "../include/strings.h"

static int test__strings() {
    // Test string__alloc
    string* str1 = string__alloc("Hello");
    if (str1 != NULL) {
        printf("str1: %s\n", str1->buffer);
    } else {
        printf("str1 allocation failed.\n");
    }

    // Test string__free
    string__free(str1);

    // Test string__concat
    string* str2 = string__alloc("Hello");
    string* str3 = string__alloc(", World!");
    if (str2 != NULL && str3 != NULL) {
        if (string__concat(str2, str3) == 0) {
            printf("str2 after concatenation: %s\n", str2->buffer);
        } else {
            printf("Concatenation failed.\n");
        }
    } else {
        printf("str2 or str3 allocation failed.\n");
    }

    // Test string__append
    string* str4 = string__alloc("Hello");
    const char* appendStr = ", World!";
    if (str4 != NULL) {
        if (string__append(str4, appendStr) == 0) {
            printf("str4 after append: %s\n", str4->buffer);
        } else {
            printf("Append failed.\n");
        }
    } else {
        printf("str4 allocation failed.\n");
    }

    // Test string_strstr
    string* str5 = string__alloc("This is a test string");
    const char* findStr = "test";
    if (str5 != NULL) {
        int pos = string_strstr(str5, findStr);
        if (pos != -1) {
            printf("'%s' found at position %d in str5.\n", findStr, pos);
        } else {
            printf("'%s' not found in str5.\n", findStr);
        }
    } else {
        printf("str5 allocation failed.\n");
    }

    // Cleanup
    string__free(str2);
    string__free(str3);
    string__free(str4);
    string__free(str5);

    return 0;
}
#endif