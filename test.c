#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "crypto.h"

void test_cli() {
    // Valid Caesar cipher encryption and decryption
    char *argv1[] = {"program", "caesar-encrypt", "3", "HELLO, WORLD"};
    assert(cli(4, argv1) == 0);

    char *argv2[] = {"program", "caesar-decrypt", "3", "KHOOR, ZRUOG!"};
    assert(cli(4, argv2) == 0);

    // Valid Vigenere cipher encryption and decryption
    char *argv3[] = {"program", "vigenere-encrypt", "KEY", "HELLO, WORLD"};
    assert(cli(4, argv3) == 0);

    char *argv4[] = {"program", "vigenere-decrypt", "KEY", "RIJVS, UYVJN!"};
    assert(cli(4, argv4) == 0);

    // Invalid operation
    char *argv5[] = {"program", "invalid-operation", "3", "HELLO, WORLD"};
    assert(cli(4, argv5) == 1);

    // Invalid Caesar key (non-integer)
    char *argv6[] = {"program", "caesar-encrypt", "a", "HELLO, WORLD"};
    assert(cli(4, argv6) == 1);

    char *argv7[] = {"program", "caesar-decrypt", "a", "HELLO, WORLD"};
    assert(cli(4, argv7) == 1);

    // Missing arguments
    char *argv8[] = {"program", "caesar-encrypt", "3"};
    assert(cli(3, argv8) == 1);

    char *argv9[] = {"program", "caesar-encrypt"};
    assert(cli(2, argv9) == 1);

    // Empty message
    char *argv10[] = {"program", "caesar-encrypt", "3", ""};
    assert(cli(4, argv10) == 0);

    char *argv11[] = {"program", "vigenere-encrypt", "KEY", ""};
    assert(cli(4, argv11) == 0);

    // Large Caesar key (testing wrap-around)
    char *argv12[] = {"program", "caesar-encrypt", "100", "HELLO, WORLD"};
    assert(cli(4, argv12) == 1);

    char *argv13[] = {"program", "caesar-decrypt", "100", "DASSI, VMIPL!"};
    assert(cli(4, argv13) == 1);

    // Negative Caesar key
    char *argv14[] = {"program", "caesar-encrypt", "-3", "HELLO, WORLD"};
    assert(cli(4, argv14) == 0);

    char *argv15[] = {"program", "caesar-decrypt", "-3", "EBIIL, TLOIA!"};
    assert(cli(4, argv15) == 0);

    // Vigenere key with special characters
    char *argv16[] = {"program", "vigenere-encrypt", "####()()()()()(@@@@@", "HELLO, WORLD"};
    assert(cli(4, argv16) == 1);

    char *argv17[] = {"program", "vigenere-decrypt", "K3Y!", "RIJVS, UYVJN!"};
    assert(cli(4, argv17) == 0);

    // Non-ASCII characters in the message (should remain unchanged)
    char *argv18[] = {"program", "caesar-encrypt", "3", "∫˜∆˜∫˙˚˜∆˚˙∫˙¨¬˚˜"};
    assert(cli(4, argv18) == 0);

    char *argv19[] = {"program", "caesar-decrypt", "3", "∫˜∆˜∫˙˚˜∆˚˙∫˙¨¬˚˜"};
    assert(cli(4, argv19) == 0);

    char *overflow_str = "28934809238402895732948923843908"; // INT_MAX + 1 as a string

    char *argv22[] = {"program", "caesar-encrypt", overflow_str, "HELLO, WORLD"};
    assert(cli(4, argv22) == 1); // Should fail due to integer overflow

    char *argv23[] = {"program", "caesar-decrypt", overflow_str, "HELLO, WORLD"};
    assert(cli(4, argv23) == 1); // Should fail due to integer overflow
}

int main(void) {
    test_cli();
    return 0;
}
