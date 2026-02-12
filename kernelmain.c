#include "types.h"

#define FRAMEBUFFER 0x000B8000

void writeLetterToFramebuffer(uint8_t letter, uint16_t row, uint16_t col, uint8_t textColor, uint8_t bgColor) {
    volatile uint16_t *framebuffer = (volatile uint16_t*) FRAMEBUFFER;

    uint16_t letterFramebuffer = (0x00FF & letter);
    uint16_t bgColorFramebuffer = (0x000F &  bgColor) << 12;
    uint16_t textColorFramebuffer = (0x000F &  textColor) << 8;

    framebuffer[col + row*80] = letterFramebuffer | textColorFramebuffer | bgColorFramebuffer;
}

int kernel_main() {

    for (int j=0; j<80; j++) {
        for (int i=0; i<25; i++) {
            writeLetterToFramebuffer('X', i, j, GREEN, WHITE);
        }
    }

    return 0;
}