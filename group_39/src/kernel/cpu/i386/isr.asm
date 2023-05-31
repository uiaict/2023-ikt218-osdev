[bits 32]



; make the functions callable/referencable from C. 
[GLOBAL] isr0
[GLOBAL] isr1
[GLOBAL] isr2


; make isr_handler function in C callable from assembly
extern isr_handler

; This assembly "handler" gets called by each service routine. 
isr_common:
    pusha                ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov ax, ds           ; Lower 16-bits of eax = ds.
    push eax             ; Save the data segment descriptor
    mov ax, 0x10         ; Kernel segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler     ; Call the ISR handler in C.
    pop ebx              ; Pop the data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                 ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov al, 0x20
    out 0x20, al
    ;add esp, 8          ; Cleans up the pushed error code and pushed ISR number
    sti                  ; Reenables interrupts
    iret                 ; Pops 5 registers and returns




; --- Interrupt Service Routines --- 
; "Division by zero"
isr0:
    push byte 0 ; Push dummy error code 
    jmp isr_common ; Jump to assembly handler

; "Debug"
isr1:
    push byte 1 ; Push dummy error code
    push 1      ; Push interrupt number
    jmp isr_default ; Jump to assembly handler

; "Device not available"
isr7:
    push byte 0; Push dummy code
    push 7     ; Push interrupt number
    jmp isr_default ; Jump to assembly handler


