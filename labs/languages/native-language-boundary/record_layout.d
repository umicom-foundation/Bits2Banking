/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/record_layout.d
 *
 * PURPOSE:
 *   Inspect native field layout while keeping value semantics separate from a serialized protocol.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

module record_layout;
import std.stdio : writeln;

struct NativeRecord
{
    ubyte kind;
    uint count;
}

// Packed layout is a controlled observation, not the default for Framework
// interfaces. A file encoder must still define byte order and field validity.
struct PackedRecord
{
    align(1):
    ubyte kind;
    uint count;
}

static assert(ubyte.sizeof == 1 && uint.sizeof == 4);
static assert(NativeRecord.kind.offsetof == 0);
static assert(NativeRecord.count.offsetof >= ubyte.sizeof);
static assert(NativeRecord.sizeof >= NativeRecord.count.offsetof + uint.sizeof);
static assert(PackedRecord.alignof == 1);
static assert(PackedRecord.count.offsetof == 1 && PackedRecord.sizeof == 5);

unittest
{
    NativeRecord native = NativeRecord(7, 0x01020304);
    PackedRecord packed = PackedRecord(native.kind, native.count);
    assert(packed.kind == native.kind && packed.count == native.count);
    uint[3] samples = [11, 22, 33];
    static assert(typeof(samples).sizeof == 12);
    assert(samples.length == 3 && samples[0].sizeof == 4);
    auto view = samples[];
    assert(view.length == 3 && view[1] == 22);
    // view.sizeof describes the slice value, not the bytes in its backing array.
    // No descriptor size is hard-coded because target pointer sizes can differ.
    assert(view.length * uint.sizeof == 12);
}

int main() @safe
{
    NativeRecord native = NativeRecord(7, 0x01020304);
    PackedRecord packed = PackedRecord(native.kind, native.count);
    if (packed.kind != native.kind || packed.count != native.count) return 1;
    uint[3] samples = [11, 22, 33];
    auto view = samples[];
    if (samples.sizeof != 12 || view.length != 3 || view[1] != 22) return 2;
    writeln("native bytes=", NativeRecord.sizeof, ", alignment=", NativeRecord.alignof,
        ", count offset=", NativeRecord.count.offsetof);
    writeln("packed bytes=", PackedRecord.sizeof, ", alignment=", PackedRecord.alignof,
        ", count offset=", PackedRecord.count.offsetof);
    writeln("array bytes=", samples.sizeof, ", elements=", samples.length,
        ", element bytes=", uint.sizeof);
    writeln("slice descriptor bytes=", view.sizeof, ", payload bytes=", view.length * uint.sizeof);
    writeln("fields agree; no raw record was saved");
    return 0;
}
