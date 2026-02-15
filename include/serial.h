#pragma once

#include "types.h"

/**
 * http://wiki.osdev.org/Serial_Ports
 */

#define SERIAL_COM1_BASE                0x3F8

/* All the I/O ports are calculated relative to the data port. This is because
    * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
    * order, but they start at different values.
    */
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

 /* SERIAL_LINE_ENABLE_DLAB:
     * Tells the serial port to expect first the highest 8 bits on the data port,
     * then the lowest 8 bits will follow
     */
#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_configure_baud_rate(uint16_t com, uint16_t divisor);
void serial_configure_line(uint16_t com);
void serial_configure_fifo(uint16_t com);
void serial_configure_modem(uint16_t com);
int8_t serial_is_transmit_fifo_empty(uint16_t com);
void serial_setup(uint16_t com);
void serial_write(uint16_t com, uint8_t data);
void serial_write_string(uint16_t com, const char *buf, uint32_t len);