@echo off
echo Building anderOS...

REM Compile kernel
gcc -ffreestanding -m32 -c kernel.c -o kernel.o
if errorlevel 1 goto error

REM Link kernel
ld -m elf_i386 -T linker.ld -o kernel.bin --oformat binary kernel.o
if errorlevel 1 goto error

REM Assemble bootloader
nasm -f bin boot.asm -o boot.bin
if errorlevel 1 goto error

REM Create OS image
copy /b boot.bin + kernel.bin anderOS.bin > nul

echo.
echo Build successful!
echo Running in QEMU...
echo.

REM Run in QEMU
qemu-system-x86_64 -drive format=raw,file=anderOS.bin

goto end

:error
echo.
echo Build failed!
pause

:end