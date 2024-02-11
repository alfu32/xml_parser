
#ifndef _XML_PARSER_TEST_H
#define _XML_PARSER_TEST_H 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/strings.h"
#include "../include/xml_parser.h"


int test__find_by_tag(string_t* xml_str,const char* tag);
int test__get_node_value(string_t* xml_str,const char* tag);

int test__xml_parser();

#endif