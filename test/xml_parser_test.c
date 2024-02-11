
#ifndef _XML_PARSER_TEST_C
#define _XML_PARSER_TEST_C 1
#include "../test_headers/xml_parser_test.h"

int test__find_by_tag(string_t* xml_str,const char* tag) {
    int error;
    
    string_t* result=string__alloc("");
    error = xml_parser__find_elements_by_tag_text(xml_str, tag, result);

    if (error < 0) {
        printf("Tag <%s> not found or error occurred. [%d]\n", tag,error);
    } else {
        printf("Found %d occurences of <%s></%s> :  [%s]\n", error,tag,tag, result->buffer);
        string__free(result);
    }
    return error;
}

int test__get_node_value(string_t* xml_str,const char* tag) {
    int count;
    
    string_t* result=string__alloc("");
    count = xml_parser__find_elements_by_tag_text(xml_str, tag, result);

    if (count < 0) {
        printf("Tag <%s> not found or error occurred. [%d]\n", tag,count);
        return count;
    } else {
        printf("Found %d occurences of <%s></%s> :  [%s]\n", count,tag,tag, result->buffer);

        string_t* inner_xml=string__alloc("");
        int error = xml_parser__get_node_value(result, inner_xml);

        if (error < 0) {
            printf("Error %d seeking inner xml in [%s]\n", error,result->buffer);
        } else {
            printf("Found inner xml [%s] in  [%s]\n", inner_xml->buffer, result->buffer);
            string__free(inner_xml);
        }

        string__free(result);
        return error;
    }
}

int test__get_inner_xml(string_t* xml_str,const char* tag) {
    int count;
    
    string_t* result=string__alloc("");
    count = xml_parser__find_elements_by_tag_text(xml_str, tag, result);

    if (count < 0) {
        printf("Tag <%s> not found or error occurred. [%d]\n", tag,count);
        return count;
    } else {
        printf("Found %d occurences of <%s></%s> :  [%s]\n", count,tag,tag, result->buffer);

        string_t* inner_xml=string__alloc("");
        int error = xml_parser__get_inner_xml(result, inner_xml);

        if (error < 0) {
            printf("Error %d seeking inner xml in [%s]\n", error,result->buffer);
        } else {
            printf("Found inner xml [%s] in  [%s]\n", inner_xml->buffer, result->buffer);
            string__free(inner_xml);
        }

        string__free(result);
        return error;
    }
}

int test__xml_parser() {
    const char* xml = "<root><name>John</name><age>30</age><com><com id=\"1\">john</com><com id=\"2\">yes</com><com id=\"3\">HDYD?</com></com></root>";

    // Create a string_t object from the XML
    string_t* xml_str = string__alloc(xml);

    test__find_by_tag(xml_str,"name");

    test__find_by_tag(xml_str,"com");

    test__find_by_tag(xml_str,"com id=\"");

    test__find_by_tag(xml_str,"com id=\"1\"");

    test__get_node_value(xml_str,"name");

    test__get_node_value(xml_str,"com");

    test__get_node_value(xml_str,"com id=\"");

    test__get_node_value(xml_str,"com id=\"1\"");

    test__get_inner_xml(xml_str,"name");

    test__get_inner_xml(xml_str,"com");

    test__get_inner_xml(xml_str,"com id=\"");

    test__get_inner_xml(xml_str,"com id=\"1\"");
    
    

    // Free the xml_str
    string__free(xml_str);

    return 0;
}

#endif