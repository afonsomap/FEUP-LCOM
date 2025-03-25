#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>

#include "i8254.h"

/** @defgroup timer timer
 * @{
 * 
 * This file contains the declarations of the functions in timer.c needed for the lab4
 */


/**
 * @brief Returns the current count value
 * 
 * @return The current count value
 */
unsigned int timer_get_count();

/**
 * @brief Sets the count value to 0
 */
void timer_reset_count();

/**
 * @brief Subscribes and enables Timer 0 interrupts
 * 
 * @param bit_no Address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int (timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Timer 0 interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (timer_unsubscribe_int)();

/**
 * @brief Increments the count variable
 */
void (timer_int_handler)();

#endif
