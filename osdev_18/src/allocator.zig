const paging = @import("paging.zig");
const memory = @import("memory.zig");

// State
var start_block: ?*Block = null;
var last_block: ?*Block = null;

var current_size: u32 = 0;
var current_offset: u32 = 0;

// Header for each block, actual data is allocated after (*Header) + sizeOf(header) which is 8.
const Block = packed struct {
    size: u31,
    used: bool,
    next: ?*Block,

    fn alloc(size: u31) *Block {
        // Fetch page from physical memory
        if (current_offset + size < current_size) {
            current_size += 0x1000;
            paging.virtual_address += 0x1000;
            paging.createFrame(paging.virtual_address);
            paging.sync();
        }
        current_offset += size + @sizeOf(Block);
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

pub fn create(comptime T: type) *T {
    const bytes = getBytes(@sizeOf(T));
    return @intToPtr(*T, bytes);
}

pub fn alloc(comptime T: type, n: u31) []T {
    const bytes = getBytes(@sizeOf(T) * n);
    const items = @intToPtr([*]T, bytes);
    return items[0..n];
}

pub fn free(pointer: anytype) void {
    var block = @intToPtr(*Block, @ptrToInt(&pointer[0]) - @sizeOf(Block));
    block.*.used = false;
}

pub fn destroy(pointer: anytype) void {
    var block = @intToPtr(*Block, @ptrToInt(pointer) - @sizeOf(Block));
    block.*.used = false;
}
