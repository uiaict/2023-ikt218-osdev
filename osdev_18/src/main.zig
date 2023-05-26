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
const utils = @import("utils.zig");
const paging = @import("paging.zig");
const memory = @import("memory.zig");
const Allocator = @import("allocator.zig");
const allocator = Allocator.kernel_allocator;

// Drivers
const Console = @import("driver/Console.zig");
const Keyboard = @import("driver/Keyboard.zig");
const Timer = @import("driver/Timer.zig");

pub fn panic(message: []const u8, _: ?*std.builtin.StackTrace) noreturn {
    Console.write("Panic occured: ");
    Console.write(message);
    while (true)
        utils.hlt();
}

export fn _start() callconv(.Naked) noreturn {
    init();
    main() catch @panic("Error occured");
    while (true)
        utils.hlt();
}

export fn isrHandler(registers: isr.Registers) void {
    if (isr.getHandler(registers.number)) |handler|
        handler(registers)
    else {
        Console.write("Received interrupt: 0x");
        Console.writeHex(@intCast(u8, registers.number));
        Console.write("\n");
    }
}

export fn irqHandler(registers: isr.Registers) void {
    if (registers.number >= 40)
        utils.outb(0xA0, 0x20); // Send reset signal to slave
    utils.outb(0x20, 0x20); // Send reset signal to master
    if (isr.getHandler(registers.number)) |handler|
        handler(registers);
}

fn init() void {
    Console.init();
    memory.init();
    gdt.init();
    idt.init();
    paging.init();
    memory.printLayout();
    Keyboard.init();
    Timer.init(1000);
}

fn main() !void {
    const first = try allocator.create(u32);
    first.* = 0x1234;
    try Console.writeFmt("overhead for each allocation: {d} bytes\n", .{@sizeOf(Allocator.Block)});
    try Console.writeFmt("first  [u32] at address 0x{x} with value 0x{x}\n", .{ @ptrToInt(first), first.* });

    const second = try allocator.create(u32);
    second.* = 0x2345;

    allocator.destroy(first);
    const third = try allocator.create(u32);
    third.* = 0x3456;

    try Console.writeFmt("second [u32] at address 0x{x} with value 0x{x}\n", .{ @ptrToInt(second), second.* });
    Console.write("freeing first...\n");
    try Console.writeFmt("third  [u32] at address 0x{x} with value 0x{x}\n", .{ @ptrToInt(third), third.* });

    Console.showPrompt();
}
