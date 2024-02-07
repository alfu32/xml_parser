#ifndef _XML_PARSER_C
#define _XML_PARSER_C
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/strings.h"
#include "../include/xml_parser.h"

// Function to extract text inside a tag using the string struct
int extractTextInsideTag(string* xml, const char* tag_name,string* result) {
    if (xml == NULL || xml->buffer == NULL || tag_name == NULL || result == NULL) {
        return 1;
    }

    // Construct opening and closing tags
    char opening_tag[strlen(tag_name) + 1]; // For "<%s"
    sprintf(opening_tag, "<%s", tag_name);

    // Find the opening tag
    char* start = strstr(xml->buffer, opening_tag);
    if (start == NULL) {
        return 2;
    }
    // Move to the start of the text within the tag
    start += strlen(opening_tag);

    // Find the end of the opening tag
    char* end_of_opening_tag = strchr(start, '>');
    if (end_of_opening_tag == NULL) {
        return 3;
    }
    // Move to the character after the end of the opening tag
    end_of_opening_tag++;

    // Construct the closing tag
    char closing_tag[strlen(tag_name) + 4]; // For "</%s>"
    sprintf(closing_tag, "</%s>", tag_name);

    // Find the closing tag
    char* end = strstr(end_of_opening_tag, closing_tag);
    if (end == NULL) {
        return 4;
    }

    // Calculate the length of the text inside the tags
    int text_length = end - start;

    // Copy the text inside the tags (excluding tags) to the result
    string__append(result, start);
    result->len = text_length;

    return 0;
}




#endif