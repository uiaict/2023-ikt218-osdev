[bits 32]



; make the functions callable from C. 
[GLOBAL] isr0
[GLOBAL] isr1
[GLOBAL] isr2



; make functions in C callable from assembly
extern isr_default


isr0:
    pusha               ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov ax, ds          ; Lower 16-bits of eax = ds.
    push eax            ; Save the data segment descriptor
    mov ax, 0x10        ; Kernel segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_default
    pop ebx             ; Pop the data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov al, 0x20
    out 0x20, al
    ;add esp, 8          ; Cleans up the pushed error code and pushed ISR number
    sti                 ; Reenables interrupts
    iret                ; Pops 5 registers and returns

isr1:
    push 1
    jmp isr_default

isr2:
    push 2
    jmp isr_default


