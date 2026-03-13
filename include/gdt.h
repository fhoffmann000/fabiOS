#pragma once

#include "types.h"

/* https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf
* 8-byte segment descriptors
* First descriptor in table has to be null
* See Intel manual figure 3-8
*/
struct gdt_descriptor {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;         //  | segment present | descriptor privilege level | descriptor type | segment type |
                            //  | 7  | 6  5 | 4  | 3  | 2  | 1  | 0  |
                            //  | Pr | DPL  | S  | Ex | DC | RW | Ac |
                            //  | 1  | 0  0 | 1  | 1  | 0  | 1  | 0  | = 0x9A   for code segment
                            //  | 1  | 0  0 | 1  | 0  | 0  | 1  | 0  | = 0x92   for data segment
    uint8_t flags_limit;    // | granularity | default operation size segment | 64-bit code segment | avl | limit |
                            //  | 7  | 6  |  5  |  4  |   3   |   2   |   1   |   0   |
                            //  | G  | DB | res | res | limit | limit | limit | limit |
                            //  | 1  | 1  |  0  |  0  | limit | limit | limit | limit |
                            //         = 0xC
                            // G=1: limit is given in 4KB blocks, i.e. 0xFFFFF*4KB = 4GB
                            // DB=1: 32-bit-segment

    uint8_t base_high;
} __attribute__((packed));

struct gdtr {
    uint16_t size;
    uint32_t address;
} __attribute__((packed));

void gdt_init();
struct gdt_descriptor set_gdt_descriptor(uint16_t index, uint32_t base_address, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_flush(struct gdtr *gdtr);