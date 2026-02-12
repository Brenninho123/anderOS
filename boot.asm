[org 0x7C00]
[bits 16]

mov ah, 0x0E
mov si, msg

print:
lodsb
cmp al, 0
je load_kernel
int 0x10
jmp print

; --- Load kernel (simple, next sector) ---
load_kernel:
mov ah, 0x02      ; BIOS read sector
mov al, 1         ; sectors to read
mov ch, 0
mov cl, 2         ; sector 2 (after boot)
mov dh, 0
mov bx, 0x0000
mov es, bx
mov bx, 0x1000    ; load address
int 0x13

jmp 0x0000:0x1000 ; jump to kernel

msg db "Booting anderOS...", 0

times 510-($-$$) db 0
dw 0xAA55