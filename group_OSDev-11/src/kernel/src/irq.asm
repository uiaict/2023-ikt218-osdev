; Forward declare irq_handler function from extern
extern irq_handler

; A macro that generates an IRQ stub with given IRQ number and corresponding ISR number
%macro IRQ 2
  global irq%1
  irq%1:
    push byte 0             ; Push a dummy error code
    push byte %2            ; Push the associated ISR number
    jmp irq_common          ; Jump to the common IRQ handler
%endmacro

; The Common IRQ stub: saves the processor state, switches to kernel mode segments,
; calls the C-level handler and finally restores the processor state.
irq_common:
    pusha                   ; Preserve all general purpose registers
    mov ax, ds              ; Copy Data Segment Descriptor into AX
    push eax                ; Push Data Segment Descriptor onto the stack
    mov ax, 0x10            ; Load the Kernel Data Segment Descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call irq_handler        ; Call C-level IRQ handler
    pop ebx                 ; Restore original Data Segment Descriptor from stack
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa                    ; Restore all general purpose registers
    add esp, 8              ; Remove dummy error code and ISR number from stack
    iret                    ; Return from the interrupt

; Generate IRQ stubs for each IRQ line, mapped to appropriate ISR numbers
IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47