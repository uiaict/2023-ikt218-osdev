.global idt_flush    # Allows the C code to call idt_flush().

idt_flush:
    movl 4(%esp), %eax    # Get the pointer to the IDT, passed as a parameter.
    lidt (%eax)           # Load the IDT pointer.
    ret                   # Return to the caller.   