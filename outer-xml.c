
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/strings.h"
#include "include/xml_parser.h"

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    // Check if tag name is provided as command line argument
    if (argc != 2) {
        printf("Usage: %s <tag_name>\n", argv[0]);
        return 1;
    }

    const char* tag_name = argv[1];

    // Read XML content line by line from stdin
    char line[MAX_LINE_LENGTH];
    string* xml_string = string__alloc("");
    if (xml_string == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for XML string\n");
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        // Append the line to the XML string
        string__add(xml_string, line);
    }

    string* result;
    int error;
    result=string__alloc("");
    error = xml_parser__outer_xml(xml_string, tag_name, result);

    if (error == 0) {
        printf("%s\n",result->buffer);
        string__free(result);
    } else {
        printf("Tag %s not found or error occurred. [%d]\n", tag_name,error);
    }

    // Free allocated memory
    string__free(xml_string);

    return error;
}