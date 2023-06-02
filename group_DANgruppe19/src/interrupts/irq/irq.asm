global irq0_handler
irq0_handler:
    pusha
    call irq0
    mov al, 0x20
    out 0x20, al
    popa
    iretd

global irq1_handler
irq1_handler:
    pusha
    call irq1
    mov al, 0x20
    out 0x20, al
    popa
    iretd

global irq2_handler
irq2_handler:
    pusha
    call irq2
    mov al, 0x20
    out 0x20, al
    popa
    iretd


global irq3_handler
irq3_handler:
    pusha
    call irq3
    mov al, 0x20
    out 0x20, al
    popa
    iretd


global irq4_handler
irq4_handler:
    pusha
    call irq4
    mov al, 0x20
    out 0x20, al
    popa
    iretd


global irq5_handler
irq5_handler:
    pusha
    call irq5
    mov al, 0x20
    out 0x20, al
    popa
    iretd


global irq6_handler
irq6_handler:
    pusha
    call irq6
    mov al, 0x20
    out 0x20, al
    popa
    iretd


global irq7_handler
irq7_handler:
    pusha
    call irq7
    mov al, 0x20
    out 0x20, al
    popa
    iretd

global irq8_handler
irq8_handler:
    pusha
    call irq8
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd

global irq9_handler
irq9_handler:
    pusha
    call irq9
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd


global irq10_handler
irq10_handler:
    pusha
    call irq10
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd



global irq11_handler
irq11_handler:
    pusha
    call irq11
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd



global irq12_handler
irq12_handler:
    pusha
    call irq12
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd



global irq13_handler
irq13_handler:
    pusha
    call irq13
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd



global irq14_handler
irq14_handler:
    pusha
    call irq14
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd


global irq15_handler
irq15_handler:
    pusha
    call irq15
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iretd
