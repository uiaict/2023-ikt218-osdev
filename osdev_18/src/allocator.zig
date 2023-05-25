const paging = @import("paging.zig");
const memory = @import("memory.zig");

// State
var start_block: ?*Block = null;
var last_block: ?*Block = null;

// Header for each block, actual data is allocated after (*Header) + sizeOf(header) which is 8.
const Block = packed struct {
    size: u31,
    used: bool,
    next: ?*Block,

    fn alloc(size: u31) *Block {
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

pub fn create(comptime T: type) *T {
    const size = @sizeOf(T);
    if (findBlock(size)) |*block| {
        block.*.used = true;
        const bytes = @ptrToInt(block.*) + @sizeOf(Block);
        return @intToPtr(*T, bytes);
    } else {
        // Create block then allocate for T
        createBlock(size);
        const bytes = memory.malloc(@sizeOf(T), .regular, null);
        return @intToPtr(*T, bytes);
    }
}

pub fn destroy(pointer: anytype) void {
    var block = blk: {
        const offset = @ptrToInt(pointer) - @sizeOf(Block);
        break :blk @intToPtr(*Block, offset);
    };
    block.*.used = false;
}

// pub fn alloc(comptime T: type, n: usize) []T {
//     const bytes = malloc(@sizeOf(T) * n, .regular, null);
//     const items = @intToPtr([*]T, bytes);
//     return items[0..n];
// }

// pub fn free(pointer: anytype) void {
//     const T = @typeInfo(@TypeOf(pointer)).Pointer.child;
//     const bytes = std.mem.sliceAsBytes(pointer);
//     _ = T;
//     _ = bytes;
// }

