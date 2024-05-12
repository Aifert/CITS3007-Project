#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "helper.h"

void check_null_pointer(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer error\n");
        exit(EXIT_FAILURE);
    }
}

void check_buffer_size(const char* input, char* output) {
    if (strlen(input) > strlen(output)) {
        fprintf(stderr, "Buffer overflow error\n");
        printf("Input: %s\n", input);
        printf("Output: %s\n", output);
        exit(EXIT_FAILURE);
    }
}

void wipe_memory(char* key) {
    if (key != NULL) {
        memset(key, 0, strlen(key));
        free(key);
    }
}
