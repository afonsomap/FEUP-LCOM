#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 KDC.
 */

#define KBC_IRQ 1 /**< @brief Keyboard IRQ line */ 
#define MOUSE_IRQ 12 /**< @brief Mouse IRQ line */


/* I/O port addresses */
#define KBC_ST_REG 0x64 /**< @brief Status Register */
#define KBC_CMD_REG 0x64 /**< @brief Command Register */
#define KBC_OUT_BUF 0x60 /**< @brief Output Buffer */
#define KBC_IN_BUF 0x60 /**< @brief Input Buffer */ /**Not used in lab3 */


#define KBC_OBF BIT(0) /**< @brief Output Buffer Full */
#define KBC_IBF BIT(1) /**< @brief Input Buffer Full */
#define KBC_PAR_ERR BIT(7) /**< @brief Parity Error */
#define KBC_TO_ERR BIT(6) /**< @brief Timeout Error */

/* Keyboard */
#define ESC_BREAKCODE 0x81 /**< @brief Breakcode of the ESC key */
#define TWO_BYTE_CODE 0xE0 /**< @brief First byte of a two byte scancode */
#define MAKECODE BIT(7) /**< @brief Breakcode bit */


#define WAIT_KBC 20000 /**< @brief Delay in microseconds */
#define MAX_TRIES 10 /**< @brief Maximum number of tries */
#define KBC_READ_CMD 0x20 /**< @brief Read Command Byte */
#define KBC_WRITE_CMD 0x60 /**< @brief Write Command Byte */


#endif /* _LCOM_I8254_H */
