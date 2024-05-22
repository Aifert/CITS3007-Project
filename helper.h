#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

int is_null_terminated(const char *str);
int check_null_pointer(const char* ptr);
int is_valid_integer(char * key);
int wipe_memory(char* key);
int is_valid_key_caeser(char * key, char range_low, char range_high);
int is_valid_key_vigenere(char * key, char range_low, char range_high);

#endif
