#include "helper.h"

char * create_pointer(size_t size){
    // Check for integer overflow and zero size
    if (size >= SIZE_MAX || size == 0){
        fprintf(stderr, "Invalid size\n");
        printf("Size: %ld\n", size);
        exit(EXIT_FAILURE);
    }
    char *ptr = malloc(size + 1);
    if (ptr == NULL){
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

bool is_null_terminated(const char *str){
    for (size_t i = 0; i < SIZE_MAX; i++){
        if(str[i] == '\0'){
            return true;
        }
    }
    fprintf(stderr, "Not null terminated\n");
    exit(EXIT_FAILURE);
}

void check_null_pointer(const char* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer error\n");
        exit(EXIT_FAILURE);
    }
}

void wipe_memory(char* key) {
    if (key != NULL) {
        memset(key, 0, strlen(key));
        free(key);
    }
}
