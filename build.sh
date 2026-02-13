#!/bin/bash

echo "==============================="
echo " Building anderOS (32-bit)"
echo "==============================="

set -e

# --- Compile all modules ---
gcc -ffreestanding -m32 -c source/utils.c -o utils.o
gcc -ffreestanding -m32 -c source/keyboard.c -o keyboard.o
gcc -ffreestanding -m32 -c source/logo.c -o logo.o
gcc -ffreestanding -m32 -c source/terminal.c -o terminal.o
gcc -ffreestanding -m32 -c source/kernel.c -o kernel.o
gcc -ffreestanding -m32 -c source/os/system.c -o system.o
gcc -ffreestanding -m32 -c source/os/memory.c -o memory.o
gcc -ffreestanding -m32 -c source/os/io.c -o io.o

echo "[OK] Compilation finished"

# --- Link kernel ---
ld -m elf_i386 -T linker.ld -o kernel.bin --oformat binary \
kernel.o utils.o keyboard.o logo.o terminal.o system.o memory.o io.o

echo "[OK] Kernel linked"

# --- Assemble bootloader ---
nasm -f bin boot.asm -o boot.bin

echo "[OK] Bootloader assembled"

# --- Create final OS image ---
cat boot.bin kernel.bin > anderOS.bin

echo "[OK] anderOS.bin created"

# --- Run in QEMU ---
echo "Starting QEMU..."
qemu-system-x86_64 -m 64M -drive format=raw,file=anderOS.bin -boot a