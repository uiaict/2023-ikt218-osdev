; This macro generates an Interrupt Service Routine (ISR) stub that doesn't provide its own error code,
; it pushes a dummy error code instead.
%macro NOERR_ISR 1
  global isr%1
  isr%1:
    cli                     ; Temporarily disable interrupts for safe state preservation
    push byte 0             ; Push dummy error code to stack
    push  %1                ; Push the ISR number to stack
    jmp isr_common     ; Transfer control to the common ISR handler
%endmacro

; Declare the isr_handler function, defined in isr.cpp
extern isr_handler

; Common ISR stub saves processor state, adjusts for kernel mode segments, calls the isr_handler in C,
; and finally restores the original stack frame.
isr_common:
    pusha                  ; Save all general-purpose registers

    mov ax, ds             ; Copy data segment descriptor into AX
    push eax               ; Push it onto stack

    mov ax, 0x10  ; Load kernel data segment descriptor into AX
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler       ; Call C handler

    pop ebx        ; Restore original data segment descriptor from stack
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                   ; Restore all general-purpose registers
    add esp, 8     ; Remove the error code and ISR number that were initially pushed onto the stack
    sti                    ; Enable interrupts
    iret           ; Return from the interrupt, restoring flags, CS, EIP, SS, ESP from stack

; This macro generates an Interrupt Service Routine (ISR) stub that provides its own error code.
%macro ERR_ISR 1
  global isr%1
  isr%1:
    cli                     ; Disable interrupts temporarily for safe state preservation
    push %1                 ; Push the ISR number to the stack
    jmp isr_common     ; Jump to common ISR handler
%endmacro

; Create ISR stubs for various interrupts using the macros
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
