const std = @import("std");
const isr = @import("../isr.zig");
const IntegerBitSet = std.bit_set.IntegerBitSet;

// https://wiki.osdev.org/Paging#32-bit_Paging_.28Protected_Mode.29
const Page = struct {
    present: u32 = 1,
    read_write: u32 = 1,
    user: u32 = 1,
    accessed: u32 = 1,
    dirty: u32 = 1,
    unused: u32 = 7,
    frame: u32 = 20,
};

const Table = struct {
    pages: [1024]Page,
};

const Directory = struct {
    tables: *[1024]Table,
    physical_tables: [1024]u32,
    physical_address: u32,
};

const frames: [10]IntegerBitSet(u32) = .{IntegerBitSet(32).initEmpty()} ** 10;

fn firstFrame() ?u32 {
    for (frames) |frame, i| {
        if (frame.findFirstSet()) |j| return i * 32 + j;
    }
    return null;
}

fn allocateFrame(page: *Page, is_kernel: bool, is_writeable: bool) void {
    if (page.frame == 0) {
        if (firstFrame()) |index| {} else {
            @panic("No free frames!");
        }
    } else return;
}

pub fn switchPageDirectory() void {}

pub fn getPage(address: u32, create: bool, directory: *Directory) *Page {}

pub fn handler(_: isr.Registers) void {}

pub fn init() void {}
