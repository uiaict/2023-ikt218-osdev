%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    push byte 0                 ; Push a dummy error code.
    push  %1                    ; Push the interrupt number.
    jmp isr_common_stub         ; Go to our common handler code.
%endmacro


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7


extern isr_handler

isr_common_stub:
    pusha           ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds      ; Lower 16-bits of eax = ds.
    push eax        ; save the data segment descriptor

    mov ax, 0x10    ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx         ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa            ; Pops edi,esi,ebp...
    add esp, 8      ; Cleans up the pushed error code and pushed ISR number
    sti
    iret            ; pops 5 things at once: CS, EIP, EFLAGS, SS and ESP
