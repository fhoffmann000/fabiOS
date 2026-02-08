; loader.s
BITS 32

global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)

section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

;Code section
section .text
loader:
    mov eax, 0xABCDEF00
.hang:
    jmp .hang