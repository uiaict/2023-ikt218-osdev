; Reference to the ISR handler in isr.c
extern isr_handler

; Macro definition to create a no-error-code ISR handler.
%macro NOERR_ISR 1
  global isr%1
  isr%1:
    ;push byte 0                 ; Inserting dummy error code
    push  %1                    ; Insert the interrupt identifier
    jmp isr_common              ; Proceed to the universal handler code
%endmacro

; Macro definition to create an error-code passing ISR handler.
%macro ERR_ISR 1
  global isr%1
  isr%1:
    push %1                     ; Insert the interrupt identifier
    jmp isr_common              ; Proceed to the universal handler code
%endmacro

NOERR_ISR 0
NOERR_ISR 1
NOERR_ISR 2
NOERR_ISR 3
NOERR_ISR 4
NOERR_ISR 5
NOERR_ISR 6
NOERR_ISR 7
ERR_ISR   8
NOERR_ISR 9
ERR_ISR   10
ERR_ISR   11
ERR_ISR   12
ERR_ISR   13
ERR_ISR   14
NOERR_ISR 15
NOERR_ISR 16
ERR_ISR   17
NOERR_ISR 18
NOERR_ISR 19
NOERR_ISR 20
ERR_ISR   21
NOERR_ISR 22
NOERR_ISR 23
NOERR_ISR 24
NOERR_ISR 25
NOERR_ISR 26
NOERR_ISR 27
NOERR_ISR 28
NOERR_ISR 29
NOERR_ISR 30
NOERR_ISR 31
NOERR_ISR 128

; The universal ISR handler, that preserves the processor state, configures for kernel mode segments, triggers the C-level fault handler and ultimately restores the stack frame.
isr_common:
    pusha                    ; Save all general purpose registers

    mov ax, ds               ; Take ds into ax.
    push eax                 ; Preserve data segment descriptor

    mov ax, 0x10             ; Load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx                  ; Recover the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     ; Restore all general purpose registers
    add esp, 8               ; Take care of the pushed error code and ISR number
    sti
    iret                     ; Return from the interrupt