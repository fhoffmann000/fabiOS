#include "serial.h"
#include "types.h"
#include "asm.h"

/**
 * http://wiki.osdev.org/Serial_Ports
 */

/**
 * The default speed of a serial
 * port is 115200 bits/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bits/s.
 */
void serial_configure_baud_rate(uint16_t com, uint16_t divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com),
            SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
            (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
            divisor & 0x00FF);
}

void serial_configure_line(uint16_t com) {
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
        * Content: | d | b | prty  | s | dl  |
        * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
        * 
        * d: Enables (d = 1) or disables (d = 0) DLAB
        * b: If break control is enabled (b = 1) or disabled (b = 0)
        * prty: The number of parity bits to use
        * s: The number of stop bits to use (s = 0 equals 1, s = 1 equals 1.5 or 2)
        * dl: Describes the length of the data
        */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}


/**
 * Buffer config
 * When data is transmitted via the serial port it is placed in FIFO buffers
 * The FIFO queue configuration byte:
 * Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
 * Content: | lvl | bs | r | dma | clt | clr | e |
 * lvl: How many bytes should be stored in the FIFO buffers
 * bs: If the buffers should be 16 or 64 bytes large
 * r: Reserved for future use
 * dma: How the serial port data should be accessed
 * clt: Clear the transmission FIFO buffer
 * clr: Clear the receiver FIFO buffer
 * e: If the FIFO buffer should be enabled or not
 */
void serial_configure_fifo(uint16_t com) {
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
        * Content: | lvl | bs | r | dma | clt | clr | e |
        * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
        */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/**
 * Modem config
 * The modem control register is used for very simple hardware flow control via the Ready To Transmit (RTS) and Data Terminal Ready (DTR) pins. 
 * When configuring the serial port we want RTS and DTR to be 1, which means that we are ready to send data.
 * 
 * Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
 * r: Reserved
 * af: Autoflow control enabled
 * lb: Loopback mode (used for debugging serial ports)
 * ao2: Auxiliary output 2, used for receiving interrupts
 * ao1: Auxiliary output 1
 * rts: Ready To Transmit
 * dtr: Data Terminal Ready
 */
void serial_configure_modem(uint16_t com) {
    /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
        * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
        * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1   | = 0x03
        */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}


/**
 * Writing data to the serial port is done via the data I/O port. However, before writing, the transmit FIFO queue has to be empty (all previous writes must have finished). 
 * The transmit FIFO queue is empty if bit 5 of the line status I/O port is equal to one.
 */
int8_t serial_is_transmit_fifo_empty(uint16_t com) {
    /* 0x20 = 0010 0000 */
    return (inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20) == 0x20;

}

void serial_setup(uint16_t com) {
    serial_configure_baud_rate(com, 1);
    serial_configure_line(com);
    serial_configure_fifo(com);
    serial_configure_modem(com);
}

void serial_write(uint16_t com, uint8_t data) {
    while (!serial_is_transmit_fifo_empty(com)) {}
    outb(SERIAL_DATA_PORT(com), data);
}

void serial_write_string(uint16_t com, const char *buf, uint32_t len) {
    for (uint32_t i=0; i<len; i++) {
        serial_write(com, buf[i]);
    }
}