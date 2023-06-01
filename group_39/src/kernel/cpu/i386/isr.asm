[bits 32]



; make the functions callable/referencable from C. 
[GLOBAL isr0]
[GLOBAL isr1]
[GLOBAL isr7]


; make C functions callable/referenceable from assembly
extern isr_handler
extern default_isr

extern irq_handler
extern irq0
extern irq1
extern irq2
extern irq3
extern irq4
extern irq5
extern irq6
extern irq7
extern irq8
extern irq9
extern irq10
extern irq11
extern irq12
extern irq13
extern irq14
extern irq15


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

    popa                ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov al, 0x20
    out 0x20, al
    add esp, 8          ; Cleans up the pushed error code and pushed ISR number
    sti                 ; Reenables interrupts
    iret                ; Pops 5 registers and returns




; The common stub for all IRQs. 

irq_common:
   pusha            ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds       ; Lower 16-bits of eax = ds.
   push eax         ; save the data segment descriptor

   mov ax, 0x10     ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop ebx          ; reload the original data segment descriptor
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popa             ; Pops edi,esi,ebp...
   add esp, 8       ; Cleans up the pushed error code and pushed ISR number
   sti
   iret             ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP



; --- Interrupt Service Routines --- 
; "Division by zero"
isr0:
    push byte 0 ; Push dummy error code 
    push 0      ; Push interrupt number
    jmp isr_common ; Jump to assembly handler

; "Debug"
isr1:
    push byte 0 ; Push dummy error code
    push 1      ; Push interrupt number
    jmp isr_common ; Jump to assembly handler

; "Device not available"
isr7:
    push byte 0; Push dummy code
    push 7     ; Push interrupt number
    jmp isr_common ; Jump to assembly handler


; --- IRQs ---
irq0:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 32 ; Push interrupt number
    jmp irq_common

irq1:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 33 ; Push interrupt number
    jmp irq_common

irq2:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 34 ; Push interrupt number
    jmp irq_common

irq3:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 35 ; Push interrupt number
    jmp irq_common

irq4:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 36 ; Push interrupt number
    jmp irq_common

irq5:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 37 ; Push interrupt number
    jmp irq_common

irq6:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 38 ; Push interrupt number
    jmp irq_common

irq7:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 39 ; Push interrupt number
    jmp irq_common

irq8:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 40 ; Push interrupt number
    jmp irq_common

irq9:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 41 ; Push interrupt number
    jmp irq_common

irq10:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 42 ; Push interrupt number
    jmp irq_common

irq11:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 43 ; Push interrupt number
    jmp irq_common

irq12:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 44 ; Push interrupt number
    jmp irq_common

irq13:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 45 ; Push interrupt number
    jmp irq_common

irq14:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 46 ; Push interrupt number
    jmp irq_common

irq15:
    cli ; Disable interrupts
    push byte 0 ; Dummy error code
    push byte 47 ; Push interrupt number
    jmp irq_common