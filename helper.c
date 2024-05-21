#include "helper.h"

char* create_pointer(size_t size) {
    char *ptr = (char *)malloc(size + 1);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    ptr[size] = '\0';
    return ptr;
}

void is_null_terminated(const char *str) {
    if (str == NULL || str[strlen(str)] != '\0') {
        fprintf(stderr, "String is not null terminated\n");
        exit(1);
    }
}

void check_null_pointer(const char* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer error\n");
        exit(EXIT_FAILURE);
    }
}

void wipe_memory(char *ptr) {
    if (ptr != NULL) {
        memset(ptr, 0, strlen(ptr));
        free(ptr);
    }
}
