; loader.s
BITS 32

global loader
extern testfunc_sum

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE equ 4096

section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .text
align 4
loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; Setup stack pointer
    push dword 3
    push dword 2
    push dword 1
    call testfunc_sum
    add esp, 12
.hang:
    jmp .hang

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

; set stack as non-executable
section .note.GNU-stack noalloc