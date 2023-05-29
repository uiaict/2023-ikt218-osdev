global irq0_handler
irq0_handler:
    ; Save CPU state
    pusha
    ; Call C handler
    call irq0
    ; Send EOI to PIC
    mov al, 0x20
    out 0x20, al
    ; Restore CPU state
    popa
    iretd
