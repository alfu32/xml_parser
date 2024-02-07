
#include <stdlib.h>
#include <stdio.h>
#include "../include/strings.h"
#include "../include/xml_parser.h"


int test__xml_parser() {
    const char* xml = "<root><name>John</name><age>30</age></root>";
    const char* tag = "<name>";

    // Create a string object from the XML
    string* xml_str = string__alloc(xml);

    // Extract the text inside the tag using the string struct
    string* extractedText = extractTextInsideTag(xml_str, tag);

    if (extractedText != NULL) {
        printf("Text inside %s: %s\n", tag, extractedText->buffer);
        string__free(extractedText);
    } else {
        printf("Tag %s not found or error occurred.\n", tag);
    }

    // Free the xml_str
    string__free(xml_str);

    return 0;
}