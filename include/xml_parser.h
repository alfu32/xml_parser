#ifndef _XML_PARSER_H
#define _XML_PARSER_H
#include "../include/strings.h"

// Function to extract text inside a tag using the string struct
int extractTextInsideTag(string* xml, const char* tag_name,string* result);


#endif