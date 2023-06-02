%macro isr_no_errors 1
  ; ISR without errors
  global isr%1
  isr%1:
    ;cli                         ; Disable interrupts firstly.
    push byte 0                 ; Push a dummy error code.
    push  %1                    ; Push the interrupt number.
    jmp isr_common_stub         ; Go to our common handler code.
%endmacro

; This macro creates a stub for an ISR which passes its own
; error code.
%macro isr_errors 1
  ; ISR with errors
  global isr%1
  isr%1:
    ;cli                         ; Disable interrupts.
    push %1                     ; Push the interrupt number
    jmp isr_common_stub
%endmacro


; This macro creates a stub for an irq - the first parameter is
; the irq number, the second is the ISR number it is remapped to.
%macro irq 2
  global irq%1
  irq%1:
    ;cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

isr_no_errors 0
isr_no_errors 1
isr_no_errors 2
isr_no_errors 3
isr_no_errors 4
isr_no_errors 5
isr_no_errors 6
isr_no_errors 7
isr_errors   8
isr_no_errors 9
isr_errors   10
isr_errors   11
isr_errors   12
isr_errors   13
isr_errors   14
isr_no_errors 15
isr_no_errors 16
isr_errors 17
isr_no_errors 18
isr_no_errors 19
isr_no_errors 20
isr_errors 21
isr_no_errors 22
isr_no_errors 23
isr_no_errors 24
isr_no_errors 25
isr_no_errors 26
isr_no_errors 27
isr_no_errors 28
isr_no_errors 29
isr_no_errors 30
isr_no_errors 31
isr_no_errors 128
irq   0,    32
irq   1,    33
irq   2,    34
irq   3,    35
irq   4,    36
irq   5,    37
irq   6,    38
irq   7,    39
irq   8,    40
irq   9,    41
irq  10,    42
irq  11,    43
irq  12,    44
irq  13,    45
irq  14,    46
irq  15,    47

extern isr_handler

isr_common_stub:
    pusha

    mov ax, ds
    push eax

    ; Load the Kernel Data Segment descriptor!
    mov ax, 0x10   
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler


    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa 

    add esp, 8
    sti
    iret

irq_common_stub:
    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    pusha                    

    ; Lower 16-bits of eax = ds.
    mov ax, ds               
    ; save the data segment descriptor
    push eax                 

    ; load the kernel data segment descriptor
    mov ax, 0x10  
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    extern irq_handler
    call irq_handler

    ; reload the original data segment descriptor
    pop ebx        
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    ; Pops edi,esi,ebp...
    popa           
    ; Cleans up the pushed error code and pushed ISR number         
    add esp, 8     

    ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
    iret           
