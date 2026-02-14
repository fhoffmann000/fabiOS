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

void styleCursor(CursorStyle cstyle) {
    uint8_t start;
    switch(cstyle) {
        case BIG:
            outb(CRTC_CMD_PORT, CURSOR_STYLE_START_CMD);
            outb(CRTC_DATA_PORT, 0x00);
            break;
        case SMALL:
            outb(CRTC_CMD_PORT, CURSOR_STYLE_START_CMD);
            outb(CRTC_DATA_PORT, 0x0C);
            break;
        case DISABLE:
            outb(CRTC_CMD_PORT, CURSOR_STYLE_START_CMD);
            start = inb(CRTC_DATA_PORT);
            outb(CRTC_DATA_PORT, start|0x20);
            break;
        case ENABLE:
            outb(CRTC_CMD_PORT, CURSOR_STYLE_START_CMD);
            start = inb(CRTC_DATA_PORT);
            outb(CRTC_DATA_PORT, start&0xBF);
            break;
        default:
    }
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

void writeLetterToScreen(const char c, uint16_t pos) {
    writeLetterToFramebuffer(c, 0, pos, WHITE, BLACK);
}

void writeToScreen(const char *buf, uint32_t len) {
    for (uint32_t i=0; i<len; i++) {
        writeLetterToFramebuffer(buf[i], 0, i, WHITE, BLACK);
    }
}

void printByte(uint8_t *pbyte, uint32_t pos) {
    for (int16_t bit=0; bit<8; bit++) {
        uint8_t mask = (uint8_t) 0x1 << (7-bit);
        if (*pbyte & mask) {
            writeLetterToScreen('1', pos+bit);
        } else {
            writeLetterToScreen('0', pos+bit);
        }
    }
}