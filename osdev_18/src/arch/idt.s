.type loadIdt, @function
.global loadIdt
    
loadIdt:
    mov +4(%esp), %eax // Fetch the idt register
    lidt (%eax)        // Load the new IDT
    ret

// Exceptions
.macro isrGenerate n
    .type isr\n, @function
    .global isr\n

    isr\n:
        // Push a dummy error code for interrupts that don't have one.
        .if (\n != 8 && !(\n >= 10 && \n <= 14) && \n != 17)
            push $0
        .endif
        push $\n       // Push the interrupt number.
        jmp isrCommon  // Jump to the common handler.
.endmacro

.extern isrHandler

.type isrCommon, @function

isrCommon:
    pusha            // Pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

    mov %ds, %ax     // Lower 16-bits of eax = ds
    push %eax        // Save the data segment descriptor

    mov $0x10, %ax   // Load the kernel data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call isrHandler

    pop %eax         // Reload the original data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa             // Pops edi, esi, ebp, esp, ebx, edx, ecx, eax
    add 0x8, %esp    // Cleans up the pushed error code and pushed ISR number
    sti
    iret             // Pops cs, eip, eflags, ss, and esp

isrGenerate 0
isrGenerate 1
isrGenerate 2
isrGenerate 3
isrGenerate 4
isrGenerate 5
isrGenerate 6
isrGenerate 7
isrGenerate 8
isrGenerate 9
isrGenerate 10
isrGenerate 11
isrGenerate 12
isrGenerate 13
isrGenerate 14
isrGenerate 15
isrGenerate 16
isrGenerate 17
isrGenerate 18
isrGenerate 19
isrGenerate 20
isrGenerate 21
isrGenerate 22
isrGenerate 23
isrGenerate 24
isrGenerate 25
isrGenerate 26
isrGenerate 27
isrGenerate 28
isrGenerate 29
isrGenerate 30
isrGenerate 31

// Interrupt request routines
.macro irqGenerate index to 
    .type irq\index, @function
    .global irq\index

    irq\index:
        cli
        push $0
        push $\to
        jmp irqCommon
.endmacro

.extern irqHandler

.type irqCommon, @function

irqCommon:
    pusha            // Pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

    mov %ds, %ax     // Lower 16-bits of eax = ds
    push %eax        // Save the data segment descriptor

    mov $0x10, %ax   // Load the kernel data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call irqHandler

    pop %ebx         // Reload the original data segment descriptor
    mov %bx, %ds
    mov %bx, %es
    mov %bx, %fs
    mov %bx, %gs

    popa             // Pops edi, esi, ebp, esp, ebx, edx, ecx, eax
    add $8, %esp     // Cleans up the pushed error code and pushed ISR number
    sti
    iret             // Pops cs, eip, eflags, ss, and esp

irqGenerate 0 32
irqGenerate 1 33
irqGenerate 2 34
irqGenerate 3 35
irqGenerate 4 36
irqGenerate 5 37
irqGenerate 6 38
irqGenerate 7 39
irqGenerate 8 40
irqGenerate 9 41
irqGenerate 10 42
irqGenerate 11 43
irqGenerate 12 44
irqGenerate 13 45
irqGenerate 14 46
irqGenerate 15 47
