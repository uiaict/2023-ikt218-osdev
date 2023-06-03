#include <cpu/isr.h>
#include <system.h>
#include <hardware_port.h>
#include <screen.h>
#include <cpu/input.h>


// Set up handlers
interrupt_t interrupt_handlers[256];

extern "C"{
    #include <kernel/memory.h>
    void init_isr() asm("init_isr");
    void init_irq() asm("init_irq");
    void irq_handler(registers_t reg) asm("irq_handler");
    void isr_handler(registers_t reg) asm("isr_handler");
}

// Initialize ISR
void init_isr(){
    // Nullify all the interrupt handlers.
    //memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
    print("ISR's initialized.\n");
}

// Can register all handlers
void register_interrupt_handler(uint8_t n, isr_t handler, void* context) {
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
}

void register_all_interrupt_handlers() {
    register_interrupt_handler(2,[](registers_t* regs, void* context)
    {
        print("Hello! It's me, Mr.Interrupt 2\n");
    }, NULL);
    register_interrupt_handler(3,[](registers_t* regs, void* context)
    {
        print("Hello! It's me, Mr.Interrupt 3\n");
    }, NULL);
    register_interrupt_handler(14, page_fault_handler, NULL);
}

void isr_handler(registers_t reg) {
    uint8_t int_no = reg.int_no & 0xFF;
    interrupt_t interrupt = interrupt_handlers[int_no];

    print("Recieved Interrupt!\n");

    if (interrupt.handler != NULL)
    {
        interrupt.handler(&reg, interrupt.context);
    }
    else
    {
        print("Error! No registered interrupt handler");
    }
}

// -- IRQ --
void init_irq() {
  for (int i = 0; i < 16; i++) {
    irq_handlers[i].data = NULL;
    irq_handlers[i].handler = NULL;
    irq_handlers[i].num = i;
  }
  print("IRQ's initialized.\n");
}

void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}

void register_all_irq_handlers() {
    // Enable
    asm volatile("sti");

    
    register_irq_handler(IRQ1, [](registers_t*, void*){
        // Read from keyboard
        unsigned char scan_code = inb(0x60);
        char f = scancode_to_ascii(&scan_code);

        if(f == 2){
            print_char('\n', -1, -1, 0x02);
        }
        else if(f == 3){
            print_char(' ', -1, -1, 0x02);
        }
        else if (f != 0) {
            print_char(f, -1, -1, 0x02);
        }

        // Disable
        asm volatile("cli");
    }, NULL);

    
}

void irq_handler(registers_t reg)
{
    if (reg.int_no >= 40)
    {
        outb(0xA0, 0x20);
    }
    // Send reset signal
    outb(0x20, 0x20);

    int_handler_t intrpt = irq_handlers[reg.int_no];
    if (intrpt.handler != NULL)
    {
        intrpt.handler(&reg, intrpt.data);
    }
    else
    {
        print("Error! No registered IRQ handler");
    }
}

// The handler for the page fault.
void page_fault_handler(registers_t* regs, void* context)
{
    uint32_t faulting_address;
    __asm__ __volatile__("mov %%cr2, %0" : "=r" (faulting_address));

    int32_t present = !(regs->err_code & 0x1);
    int32_t rw = regs->err_code & 0x2;
    int32_t us = regs->err_code & 0x4;
    int32_t reserved = regs->err_code & 0x8;
    int32_t id = regs->err_code & 0x10;


    printf("Page fault! (");
    if (present)
        printf("present");
    if (rw)
        printf("read-only");
    if (us)
        printf("user-mode");
    if (reserved)
        printf("reserved");
    printf(")\n\n");
    panic("Page fault");
}