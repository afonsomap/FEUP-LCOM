#ifndef _UART_H_
#define _UART_H_

#define UART_BASE 0x3F8
#define COM1_IRQ 4

#define SERIAL_HELLO 0xAA
#define SERIAL_ACK   0x55

#define RECEIVED_BUFFER_R 0x00
#define TRANSMITTER_HOLDING_R  0x00
#define INTERRUPT_ENABLE_R 0x01
#define INTERRUPT_IDENT_R 0x02
#define FIFO_CONTROL_R 0x02
#define LCR 0x03
#define MCR 0x04
#define LINE_STATUS_R 0x05
#define MSR 0x06
#define SR	 0x07 	// Scratchpad Register (Read/Write)

#define DLL	 0x00  // Divisor Latch (Read/Write)                   (DLAB=1)
#define DLM	 0x01  // Divisor Latch (Read/Write)                   (DLAB=1)

#define LSR_DATA_READY BIT(0)
#define LSR_OVERRUN_ERROR BIT(1)
#define LSR_PARITY_ERROR BIT(2)
#define LSR_FRAMING_ERROR BIT(3)
#define LSR_BI BIT(4)
#define LSR_TRANSMITTER_HOLDING_R_EMPTY BIT(5)
#define LSR_TRANS_EMPTY BIT(6)
#define LSR_RCVR_FIFO_ERROR BIT(7)

#define IER_RECEIVED_DATA_AVAILABLE BIT(0)
#define IER_ETBEI BIT(1)
#define IER_ELSI BIT(2)
#define IER_EDSSI BIT(3)

#define IIR_NO_INT_PENDING BIT(0)
#define IIR_ID BIT(1) | BIT(2) | BIT(3)
#define IIR_OGN_LINE_STATUS BIT(1) | BIT(2)
#define IIR_OGN_RCVD_DATA_AVL BIT(2)
#define IIR_FIFO_CT BIT(3) | BIT(2)
#define IIR_OGN_TRANS_EMPTY BIT(1)
#define IIR_INT_PENDING 0x00

#define FCR_CLEAR BIT(0) | BIT(1) | BIT(2)

#endif
