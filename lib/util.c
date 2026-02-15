#include "util.h"
#include "io.h"
#include "serial.h"

int64_t strlen(const char *str) {
    if (str == NULL) {
        return -1;
    }
    const char *start = str;
    while (*str != '\0') {
        str++;
    }
    return (int64_t) (str - start);
}

uint8_t printLine(const char *str, uint32_t len, uint32_t row) {
    for (uint32_t i = 0; i<len && str[i]!='\0'; i++) {
        if (i>79) return -1;
        writeLetterToFramebuffer(str[i], row, i, WHITE, BLACK);
    }
     return 0;
}

uint8_t logLine(const char *str, uint32_t len) {
    serial_setup(SERIAL_COM1_BASE);
    for (uint32_t i = 0; i<len && str[i]!='\0'; i++) {
        serial_write(SERIAL_COM1_BASE, str[i]);
    }
    serial_write(SERIAL_COM1_BASE, '\n');
    return 0;
}