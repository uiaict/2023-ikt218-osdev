const std = @import("std");
const paging = @import("paging.zig");
const memory = @import("memory.zig");

// State
var start_block: ?*Block = null;
var last_block: ?*Block = null;

var current_size: u32 = 0;
var current_offset: u32 = 0;

// Header for each block, actual data is allocated after
// *Header + @sizeOf(header)
pub const Block = packed struct {
    size: u31,
    used: bool,
    next: ?*Block,

    fn alloc(size: u31) *Block {
        // Fetch page from physical memory
        current_offset += @sizeOf(Block) + size;
        if (current_offset < current_size) {
            current_size += 0x1000;
            paging.virtual_address += 0x1000;
            paging.createFrame(paging.virtual_address);
            paging.sync();
        }
        const bytes = memory.malloc(@sizeOf(Block), .regular, null);
        const block = @intToPtr(*Block, bytes);
        block.* = .{
            .size = size,
            .used = true,
            .next = null,
        };
        return block;
    }

    fn fits(self: *Block, size: u31) bool {
        return size <= self.size and !self.used;
    }
};

fn createBlock(size: u31) void {
    const new_block = Block.alloc(size);
    if (last_block) |*block| {
        block.*.next = new_block;
    } else {
        start_block = new_block;
    }
    last_block = new_block;
}

fn findBlock(size: u31) ?*Block {
    var current = start_block;
    while (current) |block| {
        if (block.fits(size))
            return block;
        current = block.next;
    }
    return null;
}

// Get bytes for size by either finding block with size or creating one
fn getBytes(size: u31) usize {
    if (findBlock(size)) |*block| {
        block.*.used = true;
        return @ptrToInt(block.*) + @sizeOf(Block);
    } else {
        // Create block then allocate for T
        createBlock(size);
        return memory.malloc(size, .regular, null);
    }
}

// Allocator pattern
const KernelAllocator = struct {
    const vtable = std.mem.Allocator.VTable{
        .alloc = alloc,
        .resize = resize,
        .free = free,
    };

    fn alloc(_: *anyopaque, len: usize, _: u29, _: u29, _: usize) ![]u8 {
        const bytes = getBytes(@intCast(u31, len));
        const items = @intToPtr([*]u8, bytes);
        return items[0..len];
    }

    fn resize(_: *anyopaque, _: []u8, _: u29, _: usize, _: u29, _: usize) ?usize {
        return null;
    }

    fn free(_: *anyopaque, buf: []u8, _: u29, _: usize) void {
        const offset = @ptrToInt(&buf[0]) - @sizeOf(Block);
        var block = @intToPtr(*Block, offset);
        block.*.used = false;
    }
};

pub const kernel_allocator = std.mem.Allocator{
    .ptr = undefined,
    .vtable = &KernelAllocator.vtable,
};
