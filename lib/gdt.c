#include "gdt.h"

#define GDT_NUM_ENTRIES 3

static struct gdt_descriptor gdt_table[GDT_NUM_ENTRIES];
static struct gdtr gdtr;

static void set_gdt_descriptor(uint16_t index, uint32_t base_address, uint32_t limit, uint8_t access, uint8_t flags) {
    struct gdt_descriptor *gdt_entry = &gdt_table[index];

    gdt_entry->base_low = (uint16_t)(base_address & 0xFFFF);
    gdt_entry->base_mid = (uint8_t)((base_address>>16) & 0xFF);
    gdt_entry->base_high = (uint8_t)((base_address>>24) & 0xFF);

    gdt_entry->limit_low = (uint16_t)(limit & 0xFFFF);
    gdt_entry->access = access;
    gdt_entry->flags_limit = (flags<<4 & 0xF0) | (limit>>16 & 0x0F);
}

void gdt_init() {
    set_gdt_descriptor(0, 0, 0, 0, 0);
    // Code segment
    set_gdt_descriptor(1, 0x0, 0xFFFFF, 0x9A, 0xC);
    // data segment
    set_gdt_descriptor(2, 0x0, 0xFFFFF, 0x92, 0xC);

    gdtr.size = (uint16_t) (sizeof(struct gdt_descriptor) * GDT_NUM_ENTRIES) - 1;
    gdtr.address = (uint32_t) gdt_table;

    gdt_flush(&gdtr); //pushes gdtr address on stack for asm function
}
