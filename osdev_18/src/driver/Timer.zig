const Console = @import("Console.zig");
const isr = @import("../isr.zig");
const utils = @import("../utils.zig");

fn handler(_: isr.Registers) void {
    Console.write("T");
}

pub fn init(frequency: u32) void {
    isr.setHandler(isr.IRQ0, handler);
    const divisor = 1193180 / frequency;
    utils.outb(0x43, 0x36);
    utils.outb(0x40, @truncate(u8, divisor));
    utils.outb(0x40, @truncate(u8, (divisor >> 8)));
    utils.sti(); // Enable interrupts
}
