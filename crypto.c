#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"
#include "helper.h"

void caesar_encrypt(char range_low, char range_high, int key, const char *plain_text, char *cipher_text) {
    cipher_text[strlen(plain_text)] = '\0';

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
    plain_text[strlen(plain_text)] = '\0';

    int range = range_high - range_low + 1;
    for (int i = 0; cipher_text[i]; i++) {
        if (cipher_text[i] >= range_low && cipher_text[i] <= range_high) {
            int decrypted = ((cipher_text[i] - range_low - key) % range);
            if (decrypted < 0) decrypted += range;
            plain_text[i] = decrypted + range_low;
        } else {
            plain_text[i] = cipher_text[i];
        }
    }
}

void vigenere_encrypt(char range_low, char range_high, const char *key, const char *plain_text, char *cipher_text) {
    cipher_text[strlen(plain_text)] = '\0';

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
    plain_text[strlen(plain_text)] = '\0';

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


int cli(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    for(int i = 1; i < 4; i++){
        if (is_null_terminated(argv[i]) != 0) {
            fprintf(stderr, "Invalid Arguments\n");
            return 1;
        }

        if (check_null_pointer(argv[i]) != 0) {
            fprintf(stderr, "Invalid Arguments\n");
            return 1;
        }
    }

    char *operation = argv[1];
    char *key = argv[2];
    char *message = argv[3];

    size_t size = strlen(message);

    if (size >= SIZE_MAX){
        fprintf(stderr, "Invalid size\n");
        return 1;
    }


    char *result = malloc(size + 1);
    if (result == NULL){
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    if (strcmp(operation, "caesar-encrypt") == 0) {
        if (is_valid_integer(key)){
            caesar_encrypt('A', 'Z', atol(key), message, result);
        }
        else{
            fprintf(stderr, "Invalid key\n");
            return 1;
        }
    } else if (strcmp(operation, "caesar-decrypt") == 0) {
        if (is_valid_integer(key)){
            caesar_decrypt('A', 'Z', atol(key), message, result);
        }
        else{
            fprintf(stderr, "Invalid key\n");
            return 1;
        }
    } else if (strcmp(operation, "vigenere-encrypt") == 0) {
        vigenere_encrypt('A', 'Z', key, message, result);
    } else if (strcmp(operation, "vigenere-decrypt") == 0) {
        vigenere_decrypt('A', 'Z', key, message, result);
    } else {
        fprintf(stderr, "Invalid operation\n");
        // free(result);
        return 1;
    }

    printf("%s\n", result);

    // wipe_memory(result);

    return 0;
}
