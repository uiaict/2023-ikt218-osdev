const Console = @import("Console.zig");
const isr = @import("../isr.zig");
const utils = @import("../utils.zig");

var ticks: u32 = 0;
var ticks_per_ms: u32 = undefined;

fn handler(_: isr.Registers) void {
    ticks += 1;
}

pub fn init(frequency: u32) void {
    isr.setHandler(isr.IRQ0, handler);
    ticks_per_ms = 1000 / frequency;
    const divisor = 1193180 / frequency;
    utils.outb(0x43, 0x36);
    utils.outb(0x40, @truncate(u8, divisor));
    utils.outb(0x40, @truncate(u8, (divisor >> 8)));
    utils.sti(); // Enable interrupts
}

pub fn sleepBusy(amount_ms: u32) void {
    const target_ticks = ticks + (amount_ms / ticks_per_ms);
    while (ticks < target_ticks) {}
}

pub fn sleepInterrupt(amount_ms: u32) void {
    const target_ticks = ticks + (amount_ms / ticks_per_ms);
    while (ticks < target_ticks) utils.hlt();
}
