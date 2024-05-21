#include <assert.h>
#include "crypto.h"

void test_cli(void) {
    char *argv1[] = {"program", "caesar-encrypt", "3", "HelloWorld"};
    assert(cli(4, argv1) == 0);

    char *argv2[] = {"program", "caesar-decrypt", "3", "Khoor, Zruog!"};
    assert(cli(4, argv2) == 0);

    char *argv3[] = {"program", "vigenere-encrypt", "abcd&", "Hello, World"};
    assert(cli(4, argv3) == 0);

    char *argv4[] = {"program", "vigenere-decrypt", "abcd&", "Nello, Eorld"};
    assert(cli(4, argv4) == 0);

    char *argv5[] = {"program", "invalid-operation", "3", "Hello, Worl"};
    assert(cli(4, argv5) == 1);

    char *argv6[] = {"program", "caesar-encrypt", "3"};
    assert(cli(3, argv6) == 1);
}

int main(void) {
    test_cli();
    return 0;
}
