#!/bin/bash

rm -rf iso
rm -f os.iso kernel.elf loader.o

nasm -f elf32 loader.s -o loader.o
ld -T link.ld -melf_i386 loader.o -o kernel.elf

grub-file --is-x86-multiboot kernel.elf && echo "multibook config ok" || echo "multiboot config error"

mkdir -p iso/boot/grub
cp kernel.elf iso/boot/

cat << 'EOF' > ./iso/boot/grub/grub.cfg
set timeout=5
set default=0

menuentry "FabiOS" {
    multiboot /boot/kernel.elf
    boot
}
EOF

grub-mkrescue -o fabiOS.iso iso -d /usr/lib/grub/i386-pc