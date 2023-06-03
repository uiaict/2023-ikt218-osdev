[org 0x7c00]

[GLOBAL load_gdt]

code_seg equ GDT_code - GDT_start
data_seg equ GDT_data - GDT_start

load_gdt:
    lgdt [GDT_descriptor]
    jmp code_seg:reload_segments

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start

reload_segments:
    mov ax, data_seg
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret