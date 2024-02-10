#ifndef _XML_PARSER_H
#define _XML_PARSER_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/strings.h"

// Function to extract text inside a tag using the string struct
int xml_parser__find_elements_by_tag_text(string* xml, const char* tag_name,string* result);
int xml_parser__get_node_value(string* xml,string* result);
int xml_parser__get_inner_xml(string* xml,string* result);

#define XML_PARSER_ERR_VOID_REF -1
#define XML_PARSER_ERR_EMPTY_TAG -2
#define XML_PARSER_ERR_VOID_RESULT -3


#endif