#ifndef _XML_PARSER_C
#define _XML_PARSER_C
#include "../include/strings.h"
#include "../include/xml_parser.h"

// Function to extract text inside a tag using the string struct
int xml_parser__outer_xml(string* xml, const char* tag_name,string* result) {
    if (xml == NULL || xml->buffer == NULL ) {
        return -1;
    }
    if(tag_name == NULL) {
        return -2;
    }
    if(result == NULL) {
        return -3;
    }
    size_t tag_size = strlen(tag_name);
    const char* p = tag_name;
    size_t index_tag=0;
    while (*p && *p!=' ') {
        p++;
        index_tag++;
    }

    char tag[index_tag];
    strncpy(tag,tag_name,index_tag);
    tag[index_tag]='\0';
    int opening_tags_count = 0;
    char* start = NULL;
    char* end = NULL;

    // Construct opening and closing tags
    char opening_tag[tag_size + 2]; // For "<%s>"
    sprintf(opening_tag, "<%s", tag_name);

    char closing_tag[tag_size + 4]; // For "</%s>"
    sprintf(closing_tag, "</%s>", tag);

    size_t opening_tag_size = strlen(opening_tag);
    size_t closing_tag_size = strlen(closing_tag);

    size_t index=0;
    // Iterate through the XML string
    char* ptr = xml->buffer;
    //printf("=== start %s>..%s",opening_tag,closing_tag);
    while (*ptr != '\0') {
        if (*ptr == '<') {//
            //printf("found start char < @ index %d in %s\n",index,ptr);
            // Check for opening tag
            if (strncmp(ptr, opening_tag, opening_tag_size) == 0) {
                //printf("next %d chars match opening tag %s in %s\n",opening_tag_size,opening_tag,ptr);
                // Increment the opening tags count
                opening_tags_count++;
                if (opening_tags_count == 1) {
                    // Save the start pointer
                    start = ptr;
                    //printf("stored start index %d for the first occurence of %s in %s\n",index,opening_tag,ptr);
                }
            }
            // Check for closing tag
            else if (strncmp(ptr, closing_tag, closing_tag_size) == 0) {
                //printf("next %d chars match closing tag %s in %s\n",closing_tag_size,closing_tag,ptr);
                if (opening_tags_count > 0) {
                    // Decrement the opening tags count
                    opening_tags_count--;
                    if (opening_tags_count == 0 && start != NULL) {
                        // Save the end pointer
                        end = ptr + closing_tag_size;
                        // Exit the loop if both start and end pointers are set
                        //printf("stored end index %d for the last occurence of %s in %s\n",index + closing_tag_size,closing_tag,ptr);
                        break;
                    }
                }
            }
        }
        // Move to the next character
        ptr++;
        index++;
    }
    // If both start and end pointers are set, return the string slice
    if (start != NULL && end != NULL) {
        // Calculate the length of the text inside the tags
        int text_length = end - start;
        string__append(result,start,text_length);
        return 0;
    } else {
        return -4;
    }
}




#endif