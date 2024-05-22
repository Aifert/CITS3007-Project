#ifndef HELPER_H
#define HELPER_H

/**
 * Checks if a string is null-terminated.
 *
 * @param str The string to check.
 * @return 0 if the string is null-terminated, 1 otherwise.
 */
int is_null_terminated(const char *str);

/**
 * Checks if a pointer is null.
 *
 * @param ptr The pointer to check.
 * @return 1 if the pointer is null, 0 otherwise.
 */
int check_null_pointer(const char* ptr);

/**
 * Checks if a string is a valid integer.
 *
 * @param key The string to check.
 * @return 1 if the string is a valid integer, 0 otherwise.
 */
int is_valid_integer(const char * key);

/**
 * Wipes a string from memory by setting all its characters to 0 and then freeing it.
 *
 * @param key The string to wipe.
 * @return 0.
 */
int wipe_memory(char* key);

/**
 * Checks if a string is a valid key for a Caesar cipher.
 *
 * @param key The string to check.
 * @param range_low The lower bound of the valid range.
 * @param range_high The upper bound of the valid range.
 * @return 1 if the string is a valid key, 0 otherwise.
 */
int is_valid_key_caeser(const char * key, char range_low, char range_high);

/**
 * Checks if a string is a valid key for a Vigenere cipher.
 *
 * @param key The string to check.
 * @param range_low The lower bound of the valid range.
 * @param range_high The upper bound of the valid range.
 * @return 1 if the string is a valid key, 0 otherwise.
 */
int is_valid_key_vigenere(const char * key, char range_low, char range_high);

#endif
