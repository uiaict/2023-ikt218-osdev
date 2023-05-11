const utils = @import("utils.zig");

// Extern directives ASM ISR handlers
extern fn isr0() void;
extern fn isr1() void;
extern fn isr2() void;
extern fn isr3() void;
extern fn isr4() void;
extern fn isr5() void;
extern fn isr6() void;
extern fn isr7() void;
extern fn isr8() void;
extern fn isr9() void;
extern fn isr10() void;
extern fn isr11() void;
extern fn isr12() void;
extern fn isr13() void;
extern fn isr14() void;
extern fn isr15() void;
extern fn isr16() void;
extern fn isr17() void;
extern fn isr18() void;
extern fn isr19() void;
extern fn isr20() void;
extern fn isr21() void;
extern fn isr22() void;
extern fn isr23() void;
extern fn isr24() void;
extern fn isr25() void;
extern fn isr26() void;
extern fn isr27() void;
extern fn isr28() void;
extern fn isr29() void;
extern fn isr30() void;
extern fn isr31() void;

// Extern directives for ASM IRQ handlers
extern fn irq0() void;
extern fn irq1() void;
extern fn irq2() void;
extern fn irq3() void;
extern fn irq4() void;
extern fn irq5() void;
extern fn irq6() void;
extern fn irq7() void;
extern fn irq8() void;
extern fn irq9() void;
extern fn irq10() void;
extern fn irq11() void;
extern fn irq12() void;
extern fn irq13() void;
extern fn irq14() void;
extern fn irq15() void;

// https://wiki.osdev.org/Interrupt_Descriptor_Table#Gate_Descriptor
const IdtEntry = packed struct {
    offset_low: u16,
    segment_selector: u16,
    zero: u8,
    flags: u8,
    offset_high: u16,

    fn init(offset: u32, segment_selector: u16, flags: u8) IdtEntry {
        return .{
            .offset_low = @truncate(u16, offset & 0xFFFF),
            .offset_high = @truncate(u16, (offset >> 16) & 0xFFFF),
            .segment_selector = segment_selector,
            .zero = 0,
            .flags = flags,
        };
    }
};

const IdtRegister = packed struct {
    limit: u16,
    base: *[256]IdtEntry,

    fn init(table: *[256]IdtEntry) IdtRegister {
        return .{
            .limit = @as(u16, @sizeOf(@TypeOf(table.*))) - 1,
            .base = table,
        };
    }
};

extern fn loadIdt(register: *const IdtRegister) void;

var idt_table: [256]IdtEntry = undefined;
var idt_register: IdtRegister = undefined;

pub fn init() void {
    // Remap the irq table
    utils.outb(0x20, 0x11);
    utils.outb(0x21, 0x20);
    utils.outb(0xA1, 0x28);
    utils.outb(0x21, 0x04);
    utils.outb(0xA1, 0x02);
    utils.outb(0x21, 0x01);
    utils.outb(0xA1, 0x01);
    utils.outb(0x21, 0x00);
    utils.outb(0xA1, 0x00);

    // Load default exceptions into idt
    idt_table[0] = IdtEntry.init(@ptrToInt(isr0), 0x08, 0x8E);
    idt_table[1] = IdtEntry.init(@ptrToInt(isr1), 0x08, 0x8E);
    idt_table[2] = IdtEntry.init(@ptrToInt(isr2), 0x08, 0x8E);
    idt_table[3] = IdtEntry.init(@ptrToInt(isr3), 0x08, 0x8E);
    idt_table[4] = IdtEntry.init(@ptrToInt(isr4), 0x08, 0x8E);
    idt_table[5] = IdtEntry.init(@ptrToInt(isr5), 0x08, 0x8E);
    idt_table[6] = IdtEntry.init(@ptrToInt(isr6), 0x08, 0x8E);
    idt_table[7] = IdtEntry.init(@ptrToInt(isr7), 0x08, 0x8E);
    idt_table[8] = IdtEntry.init(@ptrToInt(isr8), 0x08, 0x8E);
    idt_table[9] = IdtEntry.init(@ptrToInt(isr9), 0x08, 0x8E);
    idt_table[10] = IdtEntry.init(@ptrToInt(isr10), 0x08, 0x8E);
    idt_table[11] = IdtEntry.init(@ptrToInt(isr11), 0x08, 0x8E);
    idt_table[12] = IdtEntry.init(@ptrToInt(isr12), 0x08, 0x8E);
    idt_table[13] = IdtEntry.init(@ptrToInt(isr13), 0x08, 0x8E);
    idt_table[14] = IdtEntry.init(@ptrToInt(isr14), 0x08, 0x8E);
    idt_table[15] = IdtEntry.init(@ptrToInt(isr15), 0x08, 0x8E);
    idt_table[16] = IdtEntry.init(@ptrToInt(isr16), 0x08, 0x8E);
    idt_table[17] = IdtEntry.init(@ptrToInt(isr17), 0x08, 0x8E);
    idt_table[18] = IdtEntry.init(@ptrToInt(isr18), 0x08, 0x8E);
    idt_table[19] = IdtEntry.init(@ptrToInt(isr19), 0x08, 0x8E);
    idt_table[20] = IdtEntry.init(@ptrToInt(isr20), 0x08, 0x8E);
    idt_table[21] = IdtEntry.init(@ptrToInt(isr21), 0x08, 0x8E);
    idt_table[22] = IdtEntry.init(@ptrToInt(isr22), 0x08, 0x8E);
    idt_table[23] = IdtEntry.init(@ptrToInt(isr23), 0x08, 0x8E);
    idt_table[24] = IdtEntry.init(@ptrToInt(isr24), 0x08, 0x8E);
    idt_table[25] = IdtEntry.init(@ptrToInt(isr25), 0x08, 0x8E);
    idt_table[26] = IdtEntry.init(@ptrToInt(isr26), 0x08, 0x8E);
    idt_table[27] = IdtEntry.init(@ptrToInt(isr27), 0x08, 0x8E);
    idt_table[28] = IdtEntry.init(@ptrToInt(isr28), 0x08, 0x8E);
    idt_table[29] = IdtEntry.init(@ptrToInt(isr29), 0x08, 0x8E);
    idt_table[30] = IdtEntry.init(@ptrToInt(isr30), 0x08, 0x8E);
    idt_table[31] = IdtEntry.init(@ptrToInt(isr31), 0x08, 0x8E);

    // Load default interrupt requests into idt
    idt_table[32] = IdtEntry.init(@ptrToInt(irq0), 0x08, 0x8E);
    idt_table[33] = IdtEntry.init(@ptrToInt(irq1), 0x08, 0x8E);
    idt_table[34] = IdtEntry.init(@ptrToInt(irq2), 0x08, 0x8E);
    idt_table[35] = IdtEntry.init(@ptrToInt(irq3), 0x08, 0x8E);
    idt_table[36] = IdtEntry.init(@ptrToInt(irq4), 0x08, 0x8E);
    idt_table[37] = IdtEntry.init(@ptrToInt(irq5), 0x08, 0x8E);
    idt_table[38] = IdtEntry.init(@ptrToInt(irq6), 0x08, 0x8E);
    idt_table[39] = IdtEntry.init(@ptrToInt(irq7), 0x08, 0x8E);
    idt_table[40] = IdtEntry.init(@ptrToInt(irq8), 0x08, 0x8E);
    idt_table[41] = IdtEntry.init(@ptrToInt(irq9), 0x08, 0x8E);
    idt_table[42] = IdtEntry.init(@ptrToInt(irq10), 0x08, 0x8E);
    idt_table[43] = IdtEntry.init(@ptrToInt(irq11), 0x08, 0x8E);
    idt_table[44] = IdtEntry.init(@ptrToInt(irq12), 0x08, 0x8E);
    idt_table[45] = IdtEntry.init(@ptrToInt(irq13), 0x08, 0x8E);
    idt_table[46] = IdtEntry.init(@ptrToInt(irq14), 0x08, 0x8E);
    idt_table[47] = IdtEntry.init(@ptrToInt(irq15), 0x08, 0x8E);

    // Load idt
    idt_register = IdtRegister.init(&idt_table);
    loadIdt(&idt_register);
}
