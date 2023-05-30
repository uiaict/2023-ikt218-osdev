; global gdt_flush
; gdt_flush:
;     lgdt [eax] ; Load the GDT pointer from the EAX register
;     mov ax, 0x10 ; Set the AX register to the data segment selector value (2 * 8)
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     mov ss, ax
;     jmp 0x08:.flush ; Set the CS register to the code segment selector value (1 * 8)
; .flush:
;     ret