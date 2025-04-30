#ifndef TIMER_COUNT_H
#define TIMER_COUNT_H

#include <lcom/lcf.h>

/** @defgroup timer timer
 * @{
 *
 * Functions to interact with the count variable of the timer.c
 * 
 * This file contains the functions that allow to interact with the count variable of the timer.c file, instead of directly accessing it using the extern keyword.
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

#endif
