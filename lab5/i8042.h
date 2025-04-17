#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 KBC.
 */

#define KBD_IRQ 1 /**< @brief Keyboard IRQ line */ 
#define MOUSE_IRQ 12 /**< @brief Mouse IRQ line */


/* I/O port addresses */
#define KBC_ST_REG 0x64 /**< @brief Status Register */
#define KBC_CMD_REG 0x64 /**< @brief Command Register */
#define KBC_OUT_BUF 0x60 /**< @brief Output Buffer */
#define KBC_IN_BUF 0x60 /**< @brief Input Buffer */ /**Not used in lab3 */

/* KBC status register bits */
#define KBC_OBF BIT(0) /**< @brief Output Buffer Full */
#define KBC_IBF BIT(1) /**< @brief Input Buffer Full */
#define KBC_PAR_ERR BIT(7) /**< @brief Parity Error */
#define KBC_TO_ERR BIT(6) /**< @brief Timeout Error */
#define KBC_AUX BIT(5) /**< @brief Mouse Data */

/* KBC utility macros */
#define WAIT_KBC 20000 /**< @brief Delay in microseconds */
#define MAX_TRIES 10 /**< @brief Maximum number of tries */
#define ESC_BREAKCODE 0x81 /**< @brief Breakcode of the ESC key */
#define TWO_BYTE_CODE 0xE0 /**< @brief First byte of a two byte scancode */
#define MAKECODE BIT(7) /**< @brief Breakcode bit */

/* KBC commands */
#define KBC_READ_CMD 0x20 /**< @brief Read Command Byte */
#define KBC_WRITE_CMD 0x60 /**< @brief Write Command Byte */

/* KBC Data report */
#define KBC_ENABLE_DATA_REPORT 0xF4 /**< @brief Enable Data Reporting */
#define KBC_DISABLE_DATA_REPORT 0xF5 /**< @brief Disable Data Reporting */
#define KBC_ACK 0xFA /**< @brief Acknowledgment */
#define WRITE_BYTE_TO_MOUSE 0xD4 /**< @brief Write Byte to Mouse */

/* Mouse */
#define MOUSE_LB BIT(0) /**< @brief Left Button */
#define MOUSE_RB BIT(1) /**< @brief Right Button */
#define MOUSE_MB BIT(2) /**< @brief Middle Button */
#define MOUSE_XOVF BIT(6) /**< @brief X Overflow */
#define MOUSE_YOVF BIT(7) /**< @brief Y Overflow */
#define MOUSE_XSIGN BIT(4) /**< @brief X Sign */
#define MOUSE_YSIGN BIT(5) /**< @brief Y Sign */

#endif /* _LCOM_I8254_H */

