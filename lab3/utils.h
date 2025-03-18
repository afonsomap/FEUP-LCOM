#ifndef _UTILS_H_
#define _UTILS_H_

#include <lcom/lcf.h>

/**
 * @brief Returns the value of the sys_counter
 * 
 * @return Value of the sys_counter
 */
int get_sys_counter();

/**
 * @brief Reads a byte from a given port using sys_inb and increments the sys_counter if compiled with LAB3
 * 
 * @param port Port to read from
 * @param value Variable to store the read byte
 * @return Return 0 upon success and non-zero otherwise
 */
int (util_sys_inb)(int port, uint8_t *value);

#endif
