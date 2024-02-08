#ifndef _STRINGS_TEST_C
#define _STRINGS_TEST_C 1
#include "../test_headers/strings_test.h"

int test__string__alloc(){
    
    // Test string__alloc
    string* str1 = string__alloc("Hello");
    if (str1 != NULL) {
        printf("str1: %s\n", str1->buffer);
        string__free(str1);
        return 0;
    } else {
        printf("str1 allocation failed.\n");
        return -1;
    }
}
int test__string__concat(){
    // Test string__concat
    string* str2 = string__alloc("Hello");
    string* str3 = string__alloc(", World!");
    if (str2 != NULL && str3 != NULL) {
        if (string__concat(str2, str3) == 0) {
            printf("str2 after concatenation: %s\n", str2->buffer);
            return 0;
        } else {
            printf("Concatenation failed.\n");
            return -1;
        }
        string__free(str2);
        string__free(str3);
    } else {
        printf("str2 or str3 allocation failed.\n");
        return -2;
    }
}
int test__string__append(){
    // Test string__append
    string* str4 = string__alloc("Hello");
    const char* appendStr = ", World!";
    if (str4 != NULL) {
        if (string__append(str4, appendStr,8) == 0) {
            printf("str4 after append: %s\n", str4->buffer);
            return 0;
        } else {
            printf("Append failed.\n");
            return -1;
        }
        string__free(str4);
    } else {
        printf("str4 allocation failed.\n");
        return -2;
    }
}
int test__string__index_of(){

    // Test string__index_of
    string* str5 = string__alloc("This is a test string");
    const char* findStr = "test";
    if (str5 != NULL) {
        int pos = string__index_of(str5, findStr);
        if (pos != -1) {
            printf("'%s' found at position %d in str5.\n", findStr, pos);
            string__free(str5);
            return 0;
        } else {
            printf("'%s' not found in str5.\n", findStr);
            return -1;
        }
    } else {
        printf("str5 allocation failed.\n");
        return -2;
    }
}
int test__string_util__trim_indent(){
    // Test string_util__trim_indent
    const char* input = "\n\
        <a>arch</a>\n\
        <b>bold</b>\n\
        <a>array</a>\n\
        <c>character</c>\n\
        <a>anytime</a>\n\
    \0";
    const char* trimmed_input = string_util__trim_indent(input);
    printf("[%s]\n trimmed is \n[%s]\n",input, trimmed_input);
    return 0;
}
int test__string__find_tagged_substrings(){
    // Test string_util__trim_indent
    const char* trimmed_input = string_util__trim_indent("\n\
        <a>arch</a>\n\
        <b>bold</b>\n\
        <a>array</a>\n\
        <c>character</c>\n\
        <a>\n\
            <a>brick</a>\n\
            <a>nail</a>\n\
            <a>hammer</a>\n\
            <a>mortar</a>\n\
            <a>hamster</a>\n\
        </a>\n\
    ");
    string* str6 = string__alloc(trimmed_input);
    string* str6result = string__alloc("");
    if (str6 != NULL) {
        int count = string__find_tagged_substrings(str6,"<a>","</a>", str6result);
        if (count >= 0) {
            printf("\x1b[32m%s\x1b[0m found in \x1b[34m%s\x1b[0m\n", str6result->buffer, str6->buffer);
            string__free(str6result);
            string__free(str6);
            return 0;
        } else {
            printf("'[%d]' error scanning str6.\n", count);
            string__free(str6);
            return -1;
        }
    } else {
        printf("str6 allocation failed.\n");
        return -2;
    }
}
int test__strings() {
    int result;

    printf("\n  \x1b[33m ==== test__string__alloc =========================\x1b[0m\n");
    result = test__string__alloc();
    printf("\n      \x1b[33m  --- result[%d] ---\x1b[0m\n",result);

    printf("\n  \x1b[33m ==== test__string__concat ========================\x1b[0m\n");
    result = test__string__concat();
    printf("\n      \x1b[33m  --- result[%d] ---\x1b[0m\n",result);

    printf("\n  \x1b[33m ==== test__string__append ========================\x1b[0m\n");
    result = test__string__append();
    printf("\n      \x1b[33m  --- result[%d] ---\x1b[0m\n",result);

    printf("\n  \x1b[33m ==== test__string__index_of ======================\x1b[0m\n");
    result = test__string__index_of();
    printf("\n      \x1b[33m  --- result[%d] ---\x1b[0m\n",result);

    printf("\n  \x1b[33m ==== test__string_util__trim_indent ==============\x1b[0m\n");
    result = test__string_util__trim_indent();
    printf("\n      \x1b[33m  --- result[%d] ---\x1b[0m\n",result);

    printf("\n  \x1b[33m ==== test__string__find_tagged_substrings ========\x1b[0m\n");
    result = test__string__find_tagged_substrings();
    printf("\n      \x1b[33m  --- result[%d] ---\x1b[0m\n",result);

    return 0;
}
#endif