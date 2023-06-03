pub const IRQ0: u8 = 32;
pub const IRQ1: u8 = 33;
pub const IRQ2: u8 = 34;
pub const IRQ3: u8 = 35;
pub const IRQ4: u8 = 36;
pub const IRQ5: u8 = 37;
pub const IRQ6: u8 = 38;
pub const IRQ7: u8 = 39;
pub const IRQ8: u8 = 40;
pub const IRQ9: u8 = 41;
pub const IRQ10: u8 = 42;
pub const IRQ11: u8 = 43;
pub const IRQ12: u8 = 44;
pub const IRQ13: u8 = 45;
pub const IRQ14: u8 = 46;
pub const IRQ15: u8 = 47;

pub const Registers = extern struct {
    ds: usize,
    edi: usize,
    esi: usize,
    ebp: usize,
    esp: usize,
    ebx: usize,
    edx: usize,
    ecx: usize,
    eax: usize,
    number: usize,
    error_code: usize,
    eip: usize,
    cs: usize,
    eflags: usize,
    useresp: usize,
    ss: usize,
};

var interrupt_handlers: [256]?fn (Registers) void = .{null} ** 256;

pub fn setHandler(index: usize, handler: fn (Registers) void) void {
    interrupt_handlers[index] = handler;
}

pub fn getHandler(index: usize) ?fn (Registers) void {
    return interrupt_handlers[index];
}
