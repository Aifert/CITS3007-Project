#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

// ANSI escape codes for colors
#define GREEN "\033[92m"
#define RED "\033[91m"
#define RESET "\033[0m"

// Structure to hold test cases
typedef struct {
    char operation[256];
    char key[256];
    char input[256];
    char extra_args[256];
    char expected_encrypt[256];
    char expected_decrypt[256];
} TestCase;

// Define function test cases
typedef struct {
    char operation[256];
    char key[256];
    char input[256];
    char expected[256];
    char range_low;
    char range_high;
} FunctionTestCase;

FunctionTestCase function_tests[] = {
    // Caesar tests
    { "caesar-encrypt", "3", "HELLO", "KHOOR", 'A', 'Z' },
    { "caesar-decrypt", "3", "KHOOR", "HELLO", 'A', 'Z' },
    { "caesar-encrypt", "5", "AAAAA", "FFFFF", 'A', 'Z' },
    { "caesar-decrypt", "5", "FFFFF", "AAAAA", 'A', 'Z' },
    { "caesar-encrypt", "22", "HELLO", "DAHHK", 'A', 'Z' },
    { "caesar-decrypt", "22", "DAHHK", "HELLO", 'A', 'Z' },
    { "caesar-encrypt", "-23", "HELLOWORLDHOWAREYOU", "KHOORZRUOGKRZDUHBRX", 'A', 'Z' },
    { "caesar-decrypt", "-23", "KHOORZRUOGKRZDUHBRX", "HELLOWORLDHOWAREYOU", 'A', 'Z' },
    { "caesar-encrypt", "-12", "Hello I am an example test case! Hopefully I don't fail :(", "vY``c w Ua Ub YlUad`Y hYgh WUgY! vcdYZi``m w Xcb'h ZU]` :(", 'A', 'z' },
    { "caesar-decrypt", "-12", "vY``c w Ua Ub YlUad`Y hYgh WUgY! vcdYZi``m w Xcb'h ZU]` :(", "Hello I am an example test case! Hopefully I don't fail :(", 'A', 'z' },
    // Edge cases for Caesar
    { "caesar-encrypt", "3", "hello", "khoor", 'a', 'z' },
    { "caesar-encrypt", "3", "12345", "45678", '0', '9' },
    { "caesar-encrypt", "3", "HELLO, WORLD!", "KHOOR, ZRUOG!",'A', 'Z' },
    { "caesar-encrypt", "0", "hello", "hello", 'a', 'z' },

    // Vigenere tests
    { "vigenere-encrypt", "KEY", "HELLO", "RIJVS", 'A', 'Z' },
    { "vigenere-decrypt", "KEY", "RIJVS", "HELLO", 'A', 'Z' },
    { "vigenere-encrypt", "ABC", "XYZ", "XZB", 'A', 'Z' },
    { "vigenere-decrypt", "ABC", "XZB", "XYZ",  'A', 'Z' },
    // Edge cases for Vigenere
    { "vigenere-encrypt", "key", "hello", "rijvs", 'a', 'z' },
    { "vigenere-encrypt", "KEY", "HELLO, WORLD!", "RIJVS, UYVJN!", 'A', 'Z' }
};

// Define CLI test cases
TestCase cli_tests[] = {
    // Standard functionality
    { "caesar-encrypt", "3", "HELLO", "", "KHOOR", "" },
    { "caesar-decrypt", "3", "KHOOR", "", "", "HELLO" },
    { "vigenere-encrypt", "KEY", "HELLO", "", "RIJVS", "" },
    { "vigenere-decrypt", "KEY", "RIJVS", "", "", "HELLO" },
    { "caesar-encrypt", "5", "AAAAA", "", "FFFFF", "" },
    { "caesar-decrypt", "5", "FFFFF", "", "", "AAAAA" },
    { "vigenere-encrypt", "ABC", "XYZ", "", "XZB", "" },
    { "vigenere-decrypt", "ABC", "XZB", "", "", "XYZ" }
};

int num_cli_tests = sizeof(cli_tests) / sizeof(cli_tests[0]);

// Cases where CLI should abort
TestCase fail_tests[] = {
    // Wrong number of arguments
    { "caesar-decrypt", "KHOOR", "", "", "Error", "" },
    { "vigenere-encrypt", "KEY", "KHOOR", "MORE stuff", "Error", "" },
    // Blank kets
    { "caesar-encrypt", "", "HELLO", "", "Error", "" },
    { "caesar-decrypt", "", "KHOOR", "", "Error", "" },
    { "vigenere-encrypt", "  ", "HELLO", "", "Error", "" },
    { "vigenere-decrypt", "", "RIJVS", "", "Error", "" },
    // Invalid keeys
    { "caesar-encrypt", "abc", "HELLO", "", "Error", "" },
    { "caesar-decrypt", "-27", "KHOOR", "", "Error", "" },
    { "caesar-encrypt", "100000000000000", "HELLO", "", "Error", "" },
    { "vigenere-encrypt", "123", "HELLO", "", "Error", "" },
    { "caesar-encrypt", "!Key@", "HELLO", "", "Error", "" },
    { "vigenere-encrypt", "!Key@", "HELLO", "", "Error", "" },
    { "caesar-encrypt", "  3 ", "HELLO", "", "Error", "" },
    { "vigenere-encrypt", " K E Y ", "HELLO", "", "Error", "" }
};

int num_fail_tests = sizeof(fail_tests) / sizeof(fail_tests[0]);

void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void run_cli_test(TestCase test) {
    char *argv[6];
    int argc = 0;

    argv[argc++] = "encryptor";
    if (strlen(test.operation) > 0) argv[argc++] = test.operation;
    if (strlen(test.key) > 0) argv[argc++] = test.key;
    if (strlen(test.input) > 0) argv[argc++] = test.input;
    if (strlen(test.extra_args) > 0) argv[argc++] = test.extra_args;

    // Redirect stdout to a buffer
    char output[256] = {0};
    FILE *fp = freopen("/dev/null", "a", stdout);
    setvbuf(stdout, output, _IOFBF, sizeof(output));

    int result = cli(argc, argv);

    // Restore stdout
    freopen("/dev/tty", "a", stdout);

    // Strip the newline character from the output
    strip_newline(output);

    if (result == 0 && (strcmp(output, test.expected_encrypt) == 0 || strcmp(output, test.expected_decrypt) == 0)) {
        printf(GREEN "Test passed: %s %s %s %s -> %s" RESET "\n", test.operation, test.key, test.input, test.extra_args, output);
    } else {
        printf(RED "Test failed: %s %s %s %s -> %s (expected: %s)" RESET "\n", test.operation, test.key, test.input, test.extra_args, output,
               (strcmp(test.expected_encrypt, "") != 0) ? test.expected_encrypt : test.expected_decrypt);
    }
}

void run_fail_test(TestCase test) {
    char *argv[6];
    int argc = 0;

    argv[argc++] = "encryptor";
    if (strlen(test.operation) > 0) argv[argc++] = test.operation;
    if (strlen(test.key) > 0) argv[argc++] = test.key;
    if (strlen(test.input) > 0) argv[argc++] = test.input;
    if (strlen(test.extra_args) > 0) argv[argc++] = test.extra_args;

    // Redirect stdout to a buffer
    char output[256] = {0};
    FILE *fp = freopen("/dev/null", "a", stdout);
    setvbuf(stdout, output, _IOFBF, sizeof(output));

    int result = cli(argc, argv);

    // Restore stdout
    freopen("/dev/tty", "a", stdout);

    // Strip the newline character from the output
    strip_newline(output);

    if (result != 0) {
        printf(GREEN "Test passed (code failed as expected): %s %s %s %s" RESET "\n", test.operation, test.key, test.input, test.extra_args);
    } else {
        printf(RED "Test failed (code did not exit as expected): %s %s %s %s (unexpected success)" RESET "\n", test.operation, test.key, test.input, test.extra_args);
    }
}

int num_function_tests = sizeof(function_tests) / sizeof(function_tests[0]);

void run_function_test(FunctionTestCase test) {
    char result[256];

    if (strcmp(test.operation, "caesar-encrypt") == 0) {
        int key = atoi(test.key);
        caesar_encrypt(test.range_low, test.range_high, key, test.input, result);
    } else if (strcmp(test.operation, "caesar-decrypt") == 0) {
        int key = atoi(test.key);
        caesar_decrypt(test.range_low, test.range_high, key, test.input, result);
    } else if (strcmp(test.operation, "vigenere-encrypt") == 0) {
        vigenere_encrypt(test.range_low, test.range_high, test.key, test.input, result);
    } else if (strcmp(test.operation, "vigenere-decrypt") == 0) {
        vigenere_decrypt(test.range_low, test.range_high, test.key, test.input, result);
    }

    if (strcmp(result, test.expected) == 0) {
        printf(GREEN "Test passed: (operation: %s) %s -> %s (expected: %s)" RESET "\n", test.operation, test.input, result, test.expected);
    } else {
        printf(RED "Test failed: (operation: %s) %s -> %s (expected: %s)" RESET "\n", test.operation, test.input, result, test.expected);
    }

}

int main() {
    // Run CLI tests
    for (int i = 0; i < num_cli_tests; i++) {
        run_cli_test(cli_tests[i]);
    }

    // Run fail tests
    for (int i = 0; i < num_fail_tests; i++) {
        run_fail_test(fail_tests[i]);
    }

    // Run function tests
    for (int i = 0; i < num_function_tests; i++) {
        run_function_test(function_tests[i]);
    }

    return 0;
}
