#ifndef _XML_PARSER_H
#define _XML_PARSER_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/strings.h"

// Function to extract text inside a tag using the string_t struct
int xml_parser__find_elements_by_tag_text(string_t* xml, const char* tag_name,string_t* result);
int xml_parser__get_node_value(string_t* xml,string_t* result);
int xml_parser__get_inner_xml(string_t* xml,string_t* result);

#define XML_PARSER_ERR_VOID_REF -1
#define XML_PARSER_ERR_EMPTY_TAG -2
#define XML_PARSER_ERR_VOID_RESULT -3


#endif