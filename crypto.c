#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "crypto.h"
#include "helper.h"

#define RANGE_LOW 'A'
#define RANGE_HIGH 'Z'

void caesar_encrypt(char range_low, char range_high, int key, const char *plain_text, char *cipher_text) {
    size_t length = strlen(plain_text);
    cipher_text[length] = '\0';

    int range = range_high - range_low + 1;

    if (key < 0) {
        key = (key % range + range) % range;
    } else {
        key = key % range;
    }

    for (size_t i = 0; plain_text[i]; i++) {
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            cipher_text[i] = (char)(((plain_text[i] - range_low + key) % range) + range_low);
        } else {
            cipher_text[i] = plain_text[i];
        }
    }
}
void caesar_decrypt(char range_low, char range_high, int key, const char *cipher_text, char *plain_text) {
    size_t length = strlen(cipher_text);
    plain_text[length] = '\0';

    int range = range_high - range_low + 1;
    for (size_t i = 0; cipher_text[i]; i++) {
        if (cipher_text[i] >= range_low && cipher_text[i] <= range_high) {
            int decrypted = ((cipher_text[i] - range_low - key) % range);
            if (decrypted < 0) decrypted += range;
            plain_text[i] = (char)(decrypted + range_low);
        } else {
            plain_text[i] = cipher_text[i];
        }
    }
}

void vigenere_encrypt(char range_low, char range_high, const char *key, const char *plain_text, char *cipher_text) {
    size_t length = strlen(plain_text);
    cipher_text[length] = '\0';

    int range = range_high - range_low + 1;
    size_t key_length = strlen(key);
    size_t key_index = 0;

    for (size_t i = 0; plain_text[i]; i++) {
        if (plain_text[i] >= range_low && plain_text[i] <= range_high) {
            int shift = key[key_index % key_length] - range_low;
            cipher_text[i] = (char)(((plain_text[i] - range_low + shift) % range) + range_low);
            key_index++;
        } else {
            cipher_text[i] = plain_text[i];
        }
    }
}

void vigenere_decrypt(char range_low, char range_high, const char *key, const char *cipher_text, char *plain_text) {
    size_t length = strlen(cipher_text);
    plain_text[length] = '\0';

    size_t key_length = strlen(key);
    int range = range_high - range_low + 1;
    for (size_t i = 0; cipher_text[i]; i++) {
        if (cipher_text[i] >= range_low && cipher_text[i] <= range_high) {
            int shift = key[i % key_length] - range_low;
            plain_text[i] = (char)(((cipher_text[i] - range_low - shift + range) % range) + range_low);
        } else {
            plain_text[i] = cipher_text[i];
        }
    }
}

int cli(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    for (int i = 1; i < 4; i++) {
        if (is_null_terminated(argv[i]) != 0) {
            fprintf(stderr, "Invalid Arguments\n");
            return 1;
        }

        if (check_null_pointer(argv[i]) != 0) {
            fprintf(stderr, "Invalid Arguments\n");
            return 1;
        }
    }

    const char *operation = argv[1];
    const char *key = argv[2];
    const char *message = argv[3];
    size_t size = strlen(message);

    if (size >= SIZE_MAX) {
        fprintf(stderr, "Invalid size\n");
        return 1;
    }

    char *result = malloc(size + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    if (strcmp(operation, "caesar-encrypt") == 0 || strcmp(operation, "caesar-decrypt") == 0) {
        if (is_valid_key_caeser(key, RANGE_LOW, RANGE_HIGH)) {
            char *endptr;
            long key_value = strtol(key, &endptr, 10);
            if (key_value < INT_MIN || key_value > INT_MAX || *endptr != '\0') {
                fprintf(stderr, "Invalid key\n");
                free(result);
                return 1;
            }

            int int_key = (int)key_value;

            if (strcmp(operation, "caesar-encrypt") == 0) {
                caesar_encrypt(RANGE_LOW, RANGE_HIGH, int_key, message, result);
            } else {
                caesar_decrypt(RANGE_LOW, RANGE_HIGH, int_key, message, result);
            }
        } else {
            fprintf(stderr, "Invalid key\n");
            free(result);
            return 1;
        }
    } else if (strcmp(operation, "vigenere-encrypt") == 0 || strcmp(operation, "vigenere-decrypt") == 0) {
        if (is_valid_key_vigenere(key, RANGE_LOW, RANGE_HIGH)) {
            if (strcmp(operation, "vigenere-encrypt") == 0) {
                vigenere_encrypt(RANGE_LOW, RANGE_HIGH, key, message, result);
            } else {
                vigenere_decrypt(RANGE_LOW, RANGE_HIGH, key, message, result);
            }
        } else {
            fprintf(stderr, "Invalid key\n");
            free(result);
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid operation\n");
        free(result);
        return 1;
    }

    printf("%s\n", result);
    wipe_memory(result);

    return 0;
}
