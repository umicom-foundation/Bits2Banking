// -----------------------------------------------------------------------------
// Umicom Bits2Banking
// File: labs/languages/zig-activity/main.zig
//
// PURPOSE:
//   Present checked C activity results from a small Zig command-line client.
//
// AUTHOR AND ORGANISATION:
// Sammy Hegab
// Umicom Foundation
//
// LICENCE:
// MIT
// -----------------------------------------------------------------------------
const std = @import("std");
const activity = @import("activity.zig");

pub fn main() void {
    const values = [_]c_int{ 0, 41, 999, 1000 };
    for (values) |current| {
        const next = activity.advance(current) catch {
            std.debug.print("{d} -> refused\n", .{current});
            continue;
        };
        std.debug.print("{d} -> {d}\n", .{ current, next });
    }
}

