#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"

void caesar_encrypt(char range_low, char range_high, int key, const char *plain_text, char *cipher_text) {
    int range = range_high - range_low + 1;
    for (int i = 0; plain_text[i]; i++) {
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            cipher_text[i] = ((plain_text[i] - range_low + key) % range) + range_low;
        } else {
            cipher_text[i] = plain_text[i];
        }
    }
}

void caesar_decrypt(char range_low, char range_high, int key, const char *cipher_text, char *plain_text) {
    caesar_encrypt(range_low, range_high, -key, cipher_text, plain_text);
}

void vigenere_encrypt(char range_low, char range_high, const char *key, const char *plain_text, char *cipher_text) {
    int range = range_high - range_low + 1;
    int key_length = strlen(key);
    for (int i = 0; plain_text[i]; i++) {
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            int shift = key[i % key_length] - range_low;
            cipher_text[i] = ((plain_text[i] - range_low + shift) % range) + range_low;
        } else {
            cipher_text[i] = plain_text[i];
        }
    }
}

void vigenere_decrypt(char range_low, char range_high, const char *key, const char *cipher_text, char *plain_text) {
    int key_length = strlen(key);
    for (int i = 0; cipher_text[i]; i++) {
        if (cipher_text[i] >= range_low && cipher_text[i] <= range_high) {
            int shift = key[i % key_length] - range_low;
            plain_text[i] = ((cipher_text[i] - range_low - shift + range_high - range_low + 1) % (range_high - range_low + 1)) + range_low;
        } else {
            plain_text[i] = cipher_text[i];
        }
    }
}

/**
 * @brief Command-line interface for encryption and decryption operations.
 *
 * This function takes command-line arguments and performs the specified operation.
 * The first argument should be the operation to perform: "caesar-encrypt", "caesar-decrypt",
 * "vigenere-encrypt", or "vigenere-decrypt". The second argument is the key, which is an integer
 * for Caesar cipher operations and a string for Vigenère cipher operations. The third argument is
 * the message to encrypt or decrypt.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return int Returns 0 if the operation was successful, or 1 if there was an error.
 */
int cli(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    char *operation = argv[1];
    char *key = argv[2];
    char *message = argv[3];

    char result[1024] = {0};

    if (strcmp(operation, "caesar-encrypt") == 0) {
        caesar_encrypt('A', 'Z', atoi(key), message, result);
    } else if (strcmp(operation, "caesar-decrypt") == 0) {
        caesar_decrypt('A', 'Z', atoi(key), message, result);
    } else if (strcmp(operation, "vigenere-encrypt") == 0) {
        vigenere_encrypt('A', 'Z', key, message, result);
    } else if (strcmp(operation, "vigenere-decrypt") == 0) {
        vigenere_decrypt('A', 'Z', key, message, result);
    } else {
        fprintf(stderr, "Invalid operation\n");
        return 1;
    }

    printf("%s\n", result);
    return 0;
}
