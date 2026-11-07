// -----------------------------------------------------------------------------
// Umicom Bits2Banking
// File: labs/languages/zig-activity/activity.zig
//
// PURPOSE:
//   Translate the existing C activity bridge result into a Zig error union.
//
// AUTHOR AND ORGANISATION:
// Sammy Hegab
// Umicom Foundation
//
// LICENCE:
// MIT
// -----------------------------------------------------------------------------
const std = @import("std");
extern fn BtbActivityNext(current: c_int) c_int;

pub const ActivityError = error{Refused};

pub fn advance(current: c_int) ActivityError!c_int {
    // The C bridge is the only implementation of input and count rules.
    // No pointer crosses this boundary and no state is retained by the bridge.
    const next = BtbActivityNext(current);
    if (next < 0) return error.Refused;
    return next;
}

test "ordinary values and final permitted transition" {
    try std.testing.expectEqual(@as(c_int, 1), try advance(0));
    try std.testing.expectEqual(@as(c_int, 42), try advance(41));
    try std.testing.expectEqual(@as(c_int, 1000), try advance(999));
}

test "capacity and invalid signed values are refused" {
    const invalid = [_]c_int{ -1, std.math.minInt(c_int), 1000, 1001, std.math.maxInt(c_int) };
    for (invalid) |value| try std.testing.expectError(error.Refused, advance(value));
}

test "a refusal does not change a later call" {
    try std.testing.expectEqual(@as(c_int, 42), try advance(41));
    try std.testing.expectError(error.Refused, advance(1000));
    try std.testing.expectEqual(@as(c_int, 42), try advance(41));
}

