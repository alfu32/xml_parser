#include <stdio.h>
#include "strings_test.c"
#include "xml_parser_test.c"

int main() {
    test__strings();
    test__xml_parser();

    return 0;
}