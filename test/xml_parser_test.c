
#ifndef _XML_PARSER_TEST_C
#define _XML_PARSER_TEST_C 1
#include "../test_headers/xml_parser_test.h"


int test__xml_parser() {
    const char* xml = "<root><name>John</name><age>30</age><com><com id=\"1\">john</com><com id=\"2\">yes</com><com id=\"3\">HDYD?</com></com></root>";
    const char* tag = "name";
    const char* comments = "com";
    const char* comment = "com id=\"";

    // Create a string object from the XML
    string* xml_str = string__alloc(xml);

    // Extract the text inside the tag using the string struct
    string* result;
    int error;
    
    result=string__alloc("");
    error = xml_parser__outer_xml(xml_str, tag, result);

    if (error == 0) {
        printf("Text inside <%s:> %s\n", tag, result->buffer);
        string__free(result);
    } else {
        printf("Tag %s not found or error occurred. [%d]\n", tag,error);
    }

    result=string__alloc("");
    error = xml_parser__outer_xml(xml_str, comments, result);

    if (error == 0) {
        printf("Text inside <%s>: %s\n", comments, result->buffer);
        string__free(result);
    } else {
        printf("Tag %s not found or error occurred. [%d]\n", tag,error);
        
    } 

    result=string__alloc("");
    error = xml_parser__outer_xml(xml_str, comment, result);

    if (error == 0) {
        printf("Text inside <%s>: %s\n", comment, result->buffer);
        string__free(result);
    } else {
        printf("Tag %s not found or error occurred. [%d]\n", tag,error);
    }
    //// result=string__alloc("");
    //// string_slice* next = string__get_slice(xml_str,last_index,strlen(xml_str));
    //// 
    //// last_index = xml_parser__outer_xml((string*)next, comments, result);
    //// 
    //// if (last_index >= 0) {
    ////     printf("Text matching %s: %s\n", tag, result->buffer);
    ////     string__free(next);
    ////     string__free(result);
    //// } else {
    ////     printf("Tag %s not found or error occurred. [%d]\n", tag,last_index);
    ////     
    //// }

    // Free the xml_str
    string__free(xml_str);

    return 0;
}
#endif