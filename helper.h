#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

char * create_pointer(size_t size);
void is_null_terminated(const char *str);
void check_null_pointer(const char* ptr);
void wipe_memory(char* key);
void check_valid_key(char range_low, char range_high, int key);

#endif // HELPER_H
