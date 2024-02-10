#ifndef _XML_PARSER_C
#define _XML_PARSER_C
#include "../include/strings.h"
#include "../include/xml_parser.h"

const char * XML_PARSER_ERR[] = {
    "operator succesfull",
    "xml_parser member function was called on a null object",
    "xml_parser__find_elements_by_tag_text called with an undefined ( void ) tag",
    "xml_parser member function was called with an uninitialised string* result"
};

// Function to extract text inside a tag using the string struct
int xml_parser__find_elements_by_tag_text(string* xml, const char* tag_name,string* result) {
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
    // int opening_tags_count = 0;
    // char* start = NULL;

    // Construct opening and closing tags
    char opening_tag[tag_size + 2]; // For "<%s>"
    sprintf(opening_tag, "<%s", tag_name);

    char closing_tag[tag_size + 4]; // For "</%s>"
    sprintf(closing_tag, "</%s>", tag);

    /// size_t opening_tag_size = strlen(opening_tag);
    /// size_t closing_tag_size = strlen(closing_tag);

    int opening_tags_count = string__find_tagged_substrings(xml, opening_tag, closing_tag, result);

    return opening_tags_count;
}
#define STATUS_START 0
#define STATUS_START_OPENING_TAG 1
#define STATUS_START_QUOTES 2
#define STATUS_END_QUOTES 3
#define STATUS_END_OPENING_TAG 4
#define STATUS_END 5
#define STATUS_END_END_TAG 6
#define STATUS_START_END_TAG 7
int xml_parser__get_node_value(string* xml,string* result){
    if (xml == NULL || xml->buffer == NULL ) {
        return -1;
    }
    if(result == NULL) {
        return -3;
    }
    char* ptr=xml->buffer;
    char* start=NULL;
    
    int index_start=0;
    
    int status=STATUS_START;

    while(*ptr !='\0') {
        if(status == STATUS_START && *ptr == '<'){
            status=STATUS_START_OPENING_TAG;
            /// printf("%c @ %d status changed from STATUS_START to STATUS_START_OPENING_TAG\n",*ptr,index_start);
        }
        if((status==STATUS_START_OPENING_TAG || status==STATUS_END_QUOTES) && *ptr == '"') {
            status=STATUS_START_QUOTES;
            /// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_START_QUOTES\n",*ptr,index_start);
        }
        if(status == STATUS_START_QUOTES && *ptr == '"') {
            status=STATUS_END_QUOTES;
            /// printf("%c @ %d status changed from STATUS_START_QUOTES to STATUS_END_QUOTES\n",*ptr,index_start);
        }
        if((status==STATUS_START_OPENING_TAG || status==STATUS_END_QUOTES) && *ptr == '>') {
            status=STATUS_END_OPENING_TAG;
            /// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_END_OPENING_TAG\n",*ptr,index_start);
            start=ptr;
            start++;
            index_start++;
            break;
        }
        ptr++;
        index_start++;
    }
    int index_end=xml->len - 1;
    char* end=NULL;
    ptr=xml->buffer;
    status = STATUS_END;
    /// printf("start looking up end tag %d \n",index_end);
    if( start == NULL ){
        return -4;
    } else {
        while(index_end != 0){

            if(status == STATUS_END && ptr[index_end] == '>'){
                status=STATUS_END_END_TAG;
                /// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_END_OPENING_TAG\n",ptr[index_end],index_end);
            }
            if(status == STATUS_END_END_TAG && ptr[index_end] == '/' && ptr[index_end-1] == '<'){
                status=STATUS_START_END_TAG;
                /// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_END_OPENING_TAG\n",ptr[index_end],index_end);
                end=ptr-index_end-1;
                index_end--;
                break;
            }
            index_end--;
        }
        if(end == NULL){
            return -5;
        } else {
            /// printf("substring %s starts at %d and ends at %d in %s \n",start,index_start,index_end,xml->buffer);
            string__append(result,start,index_end-index_start);
            return 0;
        }
    }
}

int xml_parser__get_inner_xml(string* xml,string* result){

    if (xml == NULL || xml->buffer == NULL ) {
        return -1;
    }
    char* ptr=xml->buffer;
    char* start=NULL;
    char* end=NULL;
    
    int index_start=0;
    int index_end=0;
    int index=0;
    
    int status=STATUS_START;

    while(*ptr !='\0') {
        if(status == STATUS_START && *ptr == '<'){
            status=STATUS_START_OPENING_TAG;
            //// printf("%c @ %d status changed from STATUS_START to STATUS_START_OPENING_TAG\n",*ptr,index_start);
        }
        if((status==STATUS_START_OPENING_TAG || status==STATUS_END_QUOTES) && *ptr == '"') {
            status=STATUS_START_QUOTES;
            //// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_START_QUOTES\n",*ptr,index_start);
        }
        if(status == STATUS_START_QUOTES && *ptr == '"') {
            status=STATUS_END_QUOTES;
            //// printf("%c @ %d status changed from STATUS_START_QUOTES to STATUS_END_QUOTES\n",*ptr,index_start);
        }
        if((status==STATUS_START_OPENING_TAG || status==STATUS_END_QUOTES) && *ptr == '>') {
            status=STATUS_END_OPENING_TAG;
            //// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_END_OPENING_TAG\n",*ptr,index_start);
            start=ptr;
            index_start=index+1;
            start++;
        }
        if(status == STATUS_END_OPENING_TAG && *ptr == '<' && *(ptr+1) == '/'){
            status=STATUS_START_END_TAG;
            //// printf("%c @ %d status changed from STATUS_END_OPENING_TAG to STATUS_START_END_TAG\n",*ptr,index_start);
            end=ptr;
            index_end = index;
            ptr++;
            index++;
        }
        if( status==STATUS_START_END_TAG && *ptr == '>') {
            status=STATUS_END_END_TAG;
            //// printf("%c @ %d status changed from STATUS_START_OPENING_TAG to STATUS_END_OPENING_TAG\n",*ptr,index_start);
            // start=ptr;
            // start++;
            // TODO find multiples
            break;
        }
        ptr++;
        index++;
    }
    if( start == NULL || end == NULL ){
        return -4;
    } else {
        string__append(result,start,index_end-index_start);
        return 0;
    }
}

#endif