#include <stdio.h>
#include "strings.test.c"
#include "xml_parser.test.c"

int main() {
    test__strings();
    test__xml_parser();

    return 0;
}