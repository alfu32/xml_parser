
#ifndef _xml_parser_test_c
#define _xml_parser_test_c

#include <stdlib.h>
#include <stdio.h>
#include "../include/strings.h"
#include "../include/xml_parser.h"


static int test__xml_parser() {
    const char* xml = "<root><name>John</name><age>30</age></root>";
    const char* tag = "<name>";

    // Create a string object from the XML
    string* xml_str = string__alloc(xml);
    string* extractedText = string__alloc("");

    // Extract the text inside the tag using the string struct
    int result = extractTextInsideTag(xml_str, tag,extractedText);

    if (result == 0) {
        printf("Text inside %s: %s\n", tag, extractedText->buffer);
        string__free(extractedText);
    } else {
        printf("Tag %s not found or error occurred. [%d]\n", tag,result);
    }

    // Free the xml_str
    string__free(xml_str);

    return 0;
}
#endif