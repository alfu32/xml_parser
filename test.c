#include <stdio.h>
#include "test/strings_test.c"
#include "test/xml_parser_test.c"

int main() {
    test__strings();
    test__xml_parser();

    return 0;
}