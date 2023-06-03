; Makes it so that gdt_flush here can be called in the gdt.cpp
global gdt_flush

; The section we want to be called
gdt_flush:
    mov eax, [esp+4] 
    lgdt [eax]       
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    jmp 0x08:.flush

.flush:
    ret ; Returns to the cpp

; SOURCES: https://github.com/uiaict/ikt218-osdev/pull/1