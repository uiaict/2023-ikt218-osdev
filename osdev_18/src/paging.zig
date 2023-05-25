const std = @import("std");
const isr = @import("isr.zig");
const utils = @import("utils.zig");
const memory = @import("memory.zig");
const Console = @import("driver/Console.zig");
const BitSet = std.bit_set.IntegerBitSet(32);

// https://wiki.osdev.org/Paging#32-bit_Paging_.28Protected_Mode.29
const Page = packed struct {
    present: u1,
    read_write: u1,
    user: u1,
    accessed: u1,
    dirty: u1,
    unused: u7,
    frame: u20,
};

const Table = struct {
    pages: [1024]Page,
};

const Directory = struct {
    tables: [1024]?*Table,
    physical_tables: [1024]u32,
    physical_address: u32,
};

// State for paging
var frames: []BitSet = undefined;
var kernel_directory: *Directory = undefined;

fn firstFrame() ?u32 {
    const amount = frames.len / 32;
    for (frames[0..amount]) |*frame, i| {
        var j: usize = 0;
        while (j < 32) : (j += 1) {
            if (!frame.isSet(j)) {
                frame.set(j);
                return i * 32 + j;
            }
        }
    }
    return null;
}

fn allocateFrame(page: *Page, is_kernel: bool, is_writeable: bool) void {
    if (page.frame == 0) {
        if (firstFrame()) |index| {
            page.present = 1;
            page.read_write = if (is_writeable) 1 else 0;
            page.user = if (is_kernel) 0 else 1;
            page.frame = @truncate(u20, index);
        } else @panic("No free frames!");
    } else return;
}

pub fn getPage(address: u32, create: bool, directory: *Directory) ?*Page {
    const page_address = address / 0x1000;
    const table_index = page_address / 1024;
    if (directory.tables[table_index]) |*table| {
        return &table.*.pages[page_address % 1024];
    } else if (create) {
        var temporary: usize = 0;
        const table = blk: {
            const bytes = memory.malloc(@sizeOf(Table), .page, &temporary);
            break :blk @intToPtr(*Table, bytes);
        };
        directory.tables[table_index] = table;
        directory.physical_tables[table_index] = temporary | 0x7;
        return &table.pages[page_address % 1024];
    } else return null;
}

pub fn switchPageDirectory(directory: *Directory) void {
    asm volatile ("mov %[physical_tables], %%cr3"
        :
        : [physical_tables] "r" (&directory.physical_tables),
    );
    var cr0: u32 = 0;
    asm volatile ("mov %%cr0, %[cr0]"
        : [cr0] "=r" (cr0),
    );
    cr0 |= 0x80000000; // Enable paging!
    asm volatile ("mov %[input], %%cr0"
        :
        : [input] "r" (cr0),
    );
}

pub fn handler(registers: isr.Registers) void {
    const cr2 = asm ("mov %%cr2, %[value]"
        : [value] "=r" (-> u32),
    );
    const present = (registers.error_code & 0x1) == 0;
    const read_write = (registers.error_code & 0x2) > 0;
    const user_mode = (registers.error_code & 0x4) > 0;
    const reserved = (registers.error_code & 0x8) > 0;
    Console.write("Page fault! [ ");
    if (present) Console.write("present ");
    if (read_write) Console.write("read-only ");
    if (user_mode) Console.write("user-mode ");
    if (reserved) Console.write("reserved ");
    Console.write("] at 0x");
    Console.writeHex(cr2);
    Console.write("\n");
    @panic("Page fault");
}

pub fn init() void {
    // Size of physical memory
    const memory_size = 0x1000000;

    // Initialize frames set to 0
    frames = blk: {
        const amount = memory_size / 0x1000;
        const bytes = memory.malloc(@sizeOf(BitSet) * amount, .page, null);
        const items = @intToPtr([*]BitSet, bytes);
        for (items[0..amount]) |*frame|
            frame.* = BitSet.initEmpty();
        break :blk items[0..amount];
    };

    // Create page directory
    kernel_directory = blk: {
        const bytes = memory.malloc(@sizeOf(Directory), .page, null);
        const slice = @intToPtr([*]u8, bytes);
        for (slice[0..@sizeOf(Directory)]) |*byte|
            byte.* = 0;
        break :blk @intToPtr(*Directory, bytes);
    };

    // Identity map physical address to virtual address from 0x0 to end of used memory
    var i: usize = 0;
    while (i < memory.address + 0x1000) : (i += 0x1000) {
        if (getPage(i, true, kernel_directory)) |page|
            allocateFrame(page, false, false);
    }

    // Register page fault handler, then enable paging
    isr.setHandler(14, handler);
    switchPageDirectory(kernel_directory);
}
