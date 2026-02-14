#pragma once

#include "types.h"

#define FRAMEBUFFER 0x000B8000
#define CRTC_CMD_PORT 0x3D4
#define CRTC_DATA_PORT 0x3D5
#define CURSOR_POS_HIGH_BYTE_CMD 0x0E
#define CURSOR_POS_LOW_BYTE_CMD 0x0F
#define SCREEN_START_POS_HIGH_BYTE_CMD 0x0C
#define SCREEN_START_POS_LOW_BYTE_CMD 0x0D

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHTGREY 0x7E
#define DARKGREY 0x8
#define LIGHTBLUE 0x9
#define LIGHTGREEN 0xA
#define LIGHTCYAN 0xB
#define LIGHTRED 0xC
#define LIGHTMAGENTA 0xB
#define LIGHTBROWN 0xE
#define WHITE 0xF

void writeLetterToFramebuffer(uint8_t letter, uint16_t row, uint16_t col, uint8_t textColor, uint8_t bgColor);
void moveCursor(uint16_t pos);
void scroll(uint16_t row);
void writeToScreen(const char *buf, uint32_t len);