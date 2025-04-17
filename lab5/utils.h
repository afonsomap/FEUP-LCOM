#ifndef _UTILS_H_
#define _UTILS_H_

#include <lcom/lcf.h>

/**
 * @defgroup utils utils
 * 
 * @{
 * 
 * Utility functions.
 */

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

/**
 * @brief Gets the LSB of a given value
 * 
 * @param val Value to get the LSB from
 * @param lsb Variable to store the LSB
 * @return Return 0 upon success and non-zero otherwise
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Gets the MSB of a given value
 * 
 * @param val Value to get the MSB from
 * @param msb Variable to store the MSB
 * @return Return 0 upon success and non-zero otherwise
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb);

/**@} */

#endif
