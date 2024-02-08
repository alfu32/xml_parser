#ifndef _MAIN_TEST_C
#define _MAIN_TEST_C 1
#include "test_headers/main_test.h"

/// ASCII 176: "░" (Light Shade) - This character represents a light shaded block.
/// ASCII 177: "▒" (Medium Shade) - This character represents a medium shaded block.
/// ASCII 178: "▓" (Dark Shade) - This character represents a dark shaded block.
/// 25% Filled Block: ▌ (U+258C)
/// 50% Filled Block: ▀ (U+2580) and ▄ (U+2584) combined
/// 75% Filled Block: ▀ (U+2580) with a space character
/// 50% Filled Block (Lower Side): ▄ (U+2584)
/// 25% Filled Block (Right Side): ▌ (U+258C)
/// 100% Filled Block: █ (U+2588)
// \x1b[30m
// \x1b[47m
int main() {
    printf("█▀▀▀▀\x1b[31m\x1b[47m test__strings \x1b[0m▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌\n");
    test__strings();
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌\n");
    printf("----------------------------------------------------------------------------\n");
    printf("█▀▀▀▀\x1b[31m\x1b[47m test__xml_parser \x1b[0m▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌\n");
    test__xml_parser();
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌\n");

    return 0;
}
#endif