[GLOBAL idt_flush]  // Define a global symbol 'idt_flush' which can be linked from other translation units

idt_flush:  // Define the function start point
    mov eax, [esp+4]  // Load the value at the address (esp+4) into eax. This is the first argument of the function as the x86 stack grows down and ESP is pointing at the return address
    lidt [eax]  // Load the Interrupt Descriptor Table Register (IDTR) from the memory pointed to by eax. This is the actual flushing operation.
    ret  // Return to the caller
