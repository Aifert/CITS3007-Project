#include "helper.h"
#include "crypto.h"

int is_null_terminated(const char *str){
    for (size_t i = 0; i < SIZE_MAX; i++){
        if(str[i] == '\0'){
            return 0;
        }
    }
    fprintf(stderr, "Not null terminated\n");
    return 1;
}

int check_null_pointer(const char* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer error\n");
        return 1;
    }
    return 0;
}

int wipe_memory(char* key) {
    if (key != NULL) {
        memset(key, 0, strlen(key));
        free(key);
    }
    return 0;
}

int is_valid_integer(char *key) {
    size_t i = 0;
    if (key[0] == '-') {
        if (strlen(key) == 1) {
            return 0;
        }
        i = 1;
    }
    for (; i < strlen(key); i++) {
        if (key[i] < '0' || key[i] > '9') {
            return 0;
        }
    }

    long value = atol(key);
    if (value < INT_MIN || value > INT_MAX) {
        return 0;
    }
    return 1;
}


int is_valid_key(char * key, char range_low, char range_high){
    long value = atol(key);
    if (value < (range_low - range_high) || value > (range_high - range_low)) {
        return 0;
    }

    if(!is_valid_integer(key)){
        return 0;
    }

    return 1;
}
