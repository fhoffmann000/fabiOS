#include "io.h"
#include "types.h"
#include "asm.h"

void writeLetterToFramebuffer(uint8_t letter, uint16_t row, uint16_t col, uint8_t textColor, uint8_t bgColor) {
    volatile uint16_t *framebuffer = (volatile uint16_t*) FRAMEBUFFER;

    uint16_t letterFramebuffer = (0x00FF & letter);
    uint16_t bgColorFramebuffer = (0x000F &  bgColor) << 12;
    uint16_t textColorFramebuffer = (0x000F &  textColor) << 8;

    framebuffer[col + row*80] = letterFramebuffer | textColorFramebuffer | bgColorFramebuffer;
}

void moveCursor(uint16_t pos) {
    uint16_t posLowByte = pos & 0x00FF;
    uint16_t posHighByte = (pos>>8) & 0x00FF;

    outb(CRTC_CMD_PORT, CURSOR_POS_HIGH_BYTE_CMD);
    outb(CRTC_DATA_PORT, posHighByte);
    outb(CRTC_CMD_PORT, CURSOR_POS_LOW_BYTE_CMD);
    outb(CRTC_DATA_PORT, posLowByte);
}

void scroll(uint16_t row) {
    uint16_t pos = 80*row;
    uint16_t posLowByte = pos & 0x00FF;
    uint16_t posHighByte = (pos>>8) & 0x00FF;

    outb(CRTC_CMD_PORT, SCREEN_START_POS_HIGH_BYTE_CMD);
    outb(CRTC_DATA_PORT, posHighByte);
    outb(CRTC_CMD_PORT, SCREEN_START_POS_LOW_BYTE_CMD);
    outb(CRTC_DATA_PORT, posLowByte);
}