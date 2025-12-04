BITS 64

section .data
align 8

gdt64:
    dq 0

    dw 0x0000
    dw 0x0000
    db 0x00
    db 0x9A
    db 0x20
    db 0x00

    dw 0x0000
    dw 0x0000
    db 0x00
    db 0x92
    db 0x00
    db 0x00

gdt64_end:

gdtr64:
    dw gdt64_end - gdt64 - 1
    dq gdt64

section .text
global gdt_init

gdt_init:
    cli
    lgdt [rel gdtr64]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    mov eax, 0x08
    push rax
    lea  rax, [rel .flush_cs]
    push rax
    retfq

.flush_cs:
    sti
    ret