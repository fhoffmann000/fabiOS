BITS 32

global gdt_flush

gdt_flush:
    mov eax, [esp+4]

    lgdt [eax]

    mov ax, 0x10    ; all of the following regment registers are set to the data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; code segment is set with far jump
    jmp 0x08:.flush_cs

.flush_cs:
    ret