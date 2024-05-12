#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

char * create_pointer(size_t size);
bool is_null_terminated(const char *str);
void check_null_pointer(const char* ptr);
void wipe_memory(char* key);
