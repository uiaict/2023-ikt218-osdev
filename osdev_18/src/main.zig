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
const gdt = @import("gdt.zig");
const idt = @import("idt.zig");
const isr = @import("isr.zig");
const utils = @import("utils.zig");

// Drivers
const Console = @import("driver/Console.zig");
const Keyboard = @import("driver/Keyboard.zig");

export fn _start() callconv(.Naked) noreturn {
    init();
    @call(.{ .stack = &stack_bytes }, main, .{});
    while (true)
        utils.hlt();
}

export fn isrHandler(registers: isr.Registers) void {
    Console.setColor(.red, .black);
    Console.write("\nINTERRUPT OCCURRED: ");
    Console.write(&.{@intCast(u8, registers.number) + '0'}); // Ascii code to letter
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
