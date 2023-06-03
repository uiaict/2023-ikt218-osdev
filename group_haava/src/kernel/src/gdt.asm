global gdt_load
gdt_load:
    push ebp
    mov ebp, esp

    cli ; disable interrupts

    ; Copy memory location of GDT struct to register, storing this in 'ecx'
    ; because we need to dereference the location one more time.
    mov ecx, [ebp + 8]
    lgdt [ecx]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:reload_cs ; far jump to flush CS register
reload_cs:

    sti ; enable interrupts

    mov esp, ebp
    pop ebp
    ret
