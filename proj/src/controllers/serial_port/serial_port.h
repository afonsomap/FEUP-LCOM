#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_
#include <lcom/lcf.h>
#include "UART.h"
#include "queue.h"

/**
 * @brief Subscribes to serial port interrupts
 * 
 * @param bitno Pointer to store the bit number for the interrupt
 * @return 0 on success, non-zero on failure
 */
int sp_subscribe_int(uint8_t* bitno);

/**
 * @brief Unsubscribes from serial port interrupts
 * 
 * @return 0 on success, non-zero on failure
 */
int sp_unsubscribe_int();

/**
 * @brief Gets the status of the serial port
 * 
 * @param status Pointer to store the status
 * @return 0 on success, non-zero on failure
 */
int sp_get_status(uint8_t* status);

/**
 * @brief Initializes the serial port
 */
void sp_init();

/**
 * @brief Exits the serial port, clearing any buffers
 */
void sp_exit();

/**
 * @brief Sends a byte to the serial port
 * 
 * @param byte The byte to send
 * @return 0 on success, non-zero on failure
 */
int send_byte(uint8_t byte);

/**
 * @brief Reads a byte from the serial port and stores it in the input queue
 * @return 0 on success, non-zero on failure
 */
int read_byte();

/**
 * @brief Clears the input and output buffers of the serial port
 * 
 * @return 0 on success, non-zero on failure
 */
int sp_clear_buffers();


/**
 * @brief Interrupt handler for the serial port
 */
void sp_ih();

/**
 * @brief returns the next byte to be processed from the input queue
 * 
 * @return The next byte from the input queue, or 0 if the queue is empty
 */
uint8_t get_sp_byte();

#endif // _SERIAL_PORT_H_



