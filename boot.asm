[org 0x7C00]
[bits 16]

jmp start

; --- Mensagem de boot ---
msg db "Booting anderOS Protected Mode...",0

start:
    cli                 ; Desativa interrupções
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Imprime mensagem
    mov si, msg
print_loop:
    lodsb
    cmp al, 0
    je load_gdt
    mov ah, 0x0E
    int 0x10
    jmp print_loop

; --- GDT ---
load_gdt:
    lgdt [gdt_descriptor]    ; Carrega GDT
    mov eax, cr0
    or eax, 1                ; Ativa PE (Protected Mode)
    mov cr0, eax

    jmp 08h:pm_start          ; Salta para Protected Mode (cs = 0x08)

; --- GDT ---
gdt_start:
    dw 0, 0, 0, 0            ; Null descriptor
    dw 0xFFFF, 0, 0x9A, 0xCF ; Code segment
    dw 0xFFFF, 0, 0x92, 0xCF ; Data segment
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510-($-$$) db 0
dw 0xAA55

; --- Protected Mode Entry ---
[bits 32]
pm_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x9FC00      ; pilha
    call load_kernel
    cli
    hlt

load_kernel:
    ; Lê setor do kernel (simplificado)
    mov bx, 0x1000
    ret