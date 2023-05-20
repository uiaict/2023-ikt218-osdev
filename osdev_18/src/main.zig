const ALIGN = 1 << 0;
const MEMINFO = 1 << 1;
const MAGIC = 0x1BADB002;
const FLAGS = ALIGN | MEMINFO;

const MultiBoot = packed struct {
    magic: i32,
    flags: i32,
    checksum: i32,
};

export var multiboot align(4) linksection(".multiboot") = MultiBoot{
    .magic = MAGIC,
    .flags = FLAGS,
    .checksum = -(MAGIC + FLAGS),
};

export var stack_bytes: [16 * 1024]u8 align(16) linksection(".bss") = undefined;

// System
const std = @import("std");
const gdt = @import("gdt.zig");
const idt = @import("idt.zig");
const isr = @import("isr.zig");
const paging = @import("paging.zig");
const utils = @import("utils.zig");

// Drivers
const Console = @import("driver/Console.zig");
const Keyboard = @import("driver/Keyboard.zig");
const Timer = @import("driver/Timer.zig");

pub fn panic(message: []const u8, _: ?*std.builtin.StackTrace) noreturn {
    Console.write("Panic: ");
    Console.write(message);
    while (true)
        utils.hlt();
}

export fn _start() callconv(.Naked) noreturn {
    init();
    @call(.{ .stack = &stack_bytes }, main, .{});
    while (true)
        utils.hlt();
}

export fn isrHandler(registers: isr.Registers) void {
    Console.setColor(.red, .black);
    Console.write("INTERRUPT OCCURRED: ");
    Console.setColor(.green, .black);
    switch (registers.number) {
        0x00 => Console.write("Division by zero"),
        0x01 => Console.write("Single-step interrupt"),
        0x02 => Console.write("NMI"),
        0x03 => Console.write("Breakpoint"),
        0x04 => Console.write("Overflow"),
        0x05 => Console.write("Bound Range Exceeded"),
        0x06 => Console.write("Invalid Opcode"),
        0x07 => Console.write("Coprocessor not available"),
        0x08 => Console.write("Double Fault"),
        0x09 => Console.write("Coprocessor Segment Overrun"),
        0x0A => Console.write("Invalid Task State Segment"),
        0x0B => Console.write("Segment not present"),
        0x0C => Console.write("Stack Segment Fault"),
        0x0D => Console.write("General Protecion Fault"),
        0x0E => Console.write("Page Fault"),
        0x0F => Console.write("Reserved"),
        0x10 => Console.write("x87 Floating Point Exception"),
        0x11 => Console.write("Alignment Check"),
        0x12 => Console.write("Machine Check"),
        0x13 => Console.write("SIMD Floating-Point Exception"),
        0x14 => Console.write("Virtualization Exception"),
        0x15 => Console.write("Control Protection Exception"),
        else => Console.writeHex(@intCast(u8, registers.number)),
    }
    while (true)
        utils.hlt();
}

export fn irqHandler(registers: isr.Registers) void {
    if (registers.number >= 40)
        utils.outb(0xA0, 0x20); // Send reset signal to slave
    utils.outb(0x20, 0x20); // Send reset signal to master
    if (isr.getHandler(registers.number)) |handler|
        handler(registers);
}

fn init() void {
    gdt.init();
    idt.init();
    paging.init();
    Console.init();
    Keyboard.init();
}

fn main() void {
    Console.setColor(.green, .black);
    Console.write("kernel ");
    Console.setColor(.light_blue, .black);
    Console.write("> ");
    Console.setColor(.white, .black);
}
