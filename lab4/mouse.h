#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"
#include "kbc.h"

/**
 * @brief Subscribes mouse interrupts
 * 
 * @param bit_no Pointer to store the bit number set in the interrupt mask
 * @return 0 on success, 1 on failure
 */
int (mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes mouse interrupts
 * 
 * @return 0 on success, 1 on failure
 */
int (mouse_unsubscribe_int)();

/**
 * @brief Mouse interrupt handler
 */
void (mouse_ih)();

#endif /* KEYBOARD_H */
