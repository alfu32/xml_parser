#ifndef _XML_PARSER_C
#define _XML_PARSER_C
#include <stdlib.h>
#include <string.h>
#include "../include/strings.h"
#include "../include/xml_parser.h"

// Function to extract text inside a tag using the string struct
string* extractTextInsideTag(string* xml, const char* tag) {
    if (xml == NULL || xml->buffer == NULL || tag == NULL) {
        return NULL;
    }

    // Find the opening tag
    int start_pos = string_strstr(xml, tag);
    if (start_pos == -1) {
        return NULL;
    }

    // Find the closing tag
    const char* close_tag = strstr(xml->buffer + start_pos, "</");
    if (close_tag == NULL) {
        return NULL;
    }

    // Calculate the length of the text inside the tags
    int text_length = close_tag - (xml->buffer + start_pos) + strlen(close_tag);

    // Create a new string to hold the result
    string* result = string__alloc("");
    if (result != NULL) {
        // Append the text inside the tags (including tags) to the result
        string__append(result, xml->buffer + start_pos);
        result->len = text_length;
    }

    return result;
}



#endif