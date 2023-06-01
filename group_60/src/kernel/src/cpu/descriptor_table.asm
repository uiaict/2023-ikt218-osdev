[global gdt_flush]     ; Allows the C code to link to this

extern esp
gdt_flush:
    mov eax, [esp+4]    ; esp is passed as parameter, points to GDT
    lgdt [eax]
    mov ax, 0x10        ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax          ; moves all the data segments and therefor loads them
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    ret               ; Returns back to the C code