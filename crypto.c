#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"
#include "helper.h"

void caesar_encrypt(char range_low, char range_high, int key, const char *plain_text, char *cipher_text) {
    check_valid_key(range_low, range_high, key);

    is_null_terminated(plain_text);

    check_null_pointer(plain_text);
    check_null_pointer(cipher_text);

    cipher_text[strlen(plain_text)] = '\0';

    size_t length = strlen(plain_text);
    int range = range_high - range_low + 1;
    for (int i = 0; plain_text[i]; i++) {
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            cipher_text[i] = (char)(((plain_text[i] - range_low + key) % range + range) % range + range_low);
        } else {
            cipher_text[i] = plain_text[i];
        }
    }

    cipher_text[length] = '\0';
}

void caesar_decrypt(char range_low, char range_high, int key, const char *cipher_text, char *plain_text) {
    // Ensure valid key and null-terminated strings
    check_valid_key(range_low, range_high, key);
    is_null_terminated(cipher_text);

    // Check for null pointers
    check_null_pointer(cipher_text);
    check_null_pointer(plain_text);

    size_t length = strlen(cipher_text);
    int range = range_high - range_low + 1;

    for (size_t i = 0; i < length; i++) {
        if (cipher_text[i] >= range_low && cipher_text[i] <= range_high) {
            plain_text[i] = (char)(((cipher_text[i] - range_low - key + range) % range + range) % range + range_low);
        } else {
            plain_text[i] = cipher_text[i];
        }
    }

    plain_text[length] = '\0';
}


void vigenere_encrypt(char range_low, char range_high, const char *key, const char *plain_text, char *cipher_text) {
    // Check for null terminated
    is_null_terminated(plain_text);

    // Check for null pointers
    check_null_pointer(plain_text);
    check_null_pointer(cipher_text);

    size_t length = strlen(plain_text);
    size_t key_length = strlen(key);
    int range = range_high - range_low + 1;
    for (size_t i = 0; plain_text[i]; i++) {
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            int shift = key[i % key_length] - range_low;
            cipher_text[i] = (char)(((plain_text[i] - range_low + shift) % range + range) % range + range_low);
        } else {
            cipher_text[i] = plain_text[i];
        }
    }

    cipher_text[length] = '\0';
}

void vigenere_decrypt(char range_low, char range_high, const char *key, const char *cipher_text, char *plain_text) {
    // Check for null terminated
    is_null_terminated(plain_text);

    // Check for null pointers
    check_null_pointer(plain_text);
    check_null_pointer(cipher_text);

    plain_text[strlen(plain_text)] = '\0';

    size_t length = strlen(cipher_text);
    size_t key_length = strlen(key);
    int range = range_high - range_low + 1;
    for (size_t i = 0; cipher_text[i]; i++) {
        if (cipher_text[i] >= range_low && cipher_text[i] <= range_high) {
            int shift = key[i % key_length] - range_low;
            plain_text[i] = (char)(((cipher_text[i] - range_low - shift) % range + range) % range + range_low);
        } else {
            plain_text[i] = cipher_text[i];
        }
    }

    plain_text[length] = '\0';
}

int cli(int argc, char **argv) {
    if (argc != 4) {
        return 1;
    }

    char *operation = argv[1];
    char *key = argv[2];
    char *message = argv[3];

    is_null_terminated(key);
    is_null_terminated(message);

    check_null_pointer(key);
    check_null_pointer(message);

    char * result = create_pointer(strlen(message));

    if (strcmp(operation, "caesar-encrypt") == 0) {
        caesar_encrypt('A', 'z', atoi(key), message, result);
    } else if (strcmp(operation, "caesar-decrypt") == 0) {
        caesar_decrypt('A', 'Z', atoi(key), message, result);
    } else if (strcmp(operation, "vigenere-encrypt") == 0) {
        vigenere_encrypt('A', 'Z', key, message, result);
    } else if (strcmp(operation, "vigenere-decrypt") == 0) {
        vigenere_decrypt('A', 'Z', key, message, result);
    } else {
        free(result);
        return 1;
    }

    wipe_memory(result);

    return 0;
}
