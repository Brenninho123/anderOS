#!/bin/bash
set -e

# Compile kernel
gcc -ffreestanding -m32 -c kernel.c -o kernel.o

# Link kernel
ld -m elf_i386 -T linker.ld -o kernel.bin --oformat binary kernel.o

# Assemble bootloader
nasm -f bin boot.asm -o boot.bin

# Create OS image
cat boot.bin kernel.bin > anderOS.bin

# Run in QEMU
qemu-system-x86_64 -drive format=raw,file=anderOS.bin