#ifndef KBD_H
#define KBD_H

#include <lcom/lcf.h>
#include <i8042.h>
#include <stdint.h>


/**
 * @brief Wrapper for sys_inb with counter support
 * 
 * @param port Port to read from
 * @param value Pointer to store the read value
 * @return 0 on success, 1 on failure
 */
int (util_sys_inb)(int port, uint8_t *value);

/**
 * @brief Subscribes keyboard interrupts
 * 
 * @param bit_no Pointer to store the bit number set in the interrupt mask
 * @return 0 on success, 1 on failure
 */
int (kbd_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes keyboard interrupts
 * 
 * @return 0 on success, 1 on failure
 */
int (kbd_unsubscribe_int)();

/**
 * @brief Reads the keyboard controller status
 * 
 * @param st Pointer to store the status byte
 * @return 0 on success, 1 on failure
 */
int (kbd_get_status)(uint8_t *st);

/**
 * @brief Keyboard interrupt handler
 */
void (kbc_ih)();

int (check_scancode_complete)(uint8_t* scancode_array, uint8_t *index);

/**
 * @brief Reads the scancode from the keyboard controller
 * 
 * @return 0 on success, 1 on failure
 */
int (kbd_get_scancode)();

#endif /* KEYBOARD_H */
