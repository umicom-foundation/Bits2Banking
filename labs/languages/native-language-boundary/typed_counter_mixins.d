/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/typed_counter_mixins.d
 *
 * PURPOSE:
 *   Teach parameterized D template mixins with bounded independent state and normal runtime refusal.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module typed_counter_mixins;
import std.stdio : writeln;

// One typed declaration pattern supplies independent state and operations to
// each receiving structure. It is not a superclass, shared global or string
// of downloaded code. Explicit parameters keep the limit visible at the use.
mixin template BoundedCount(uint Limit)
{
    static assert(Limit > 0U, "A counter needs a positive limit");
    private uint count_;

    uint value() const @safe pure nothrow @nogc { return count_; }
    uint remaining() const @safe pure nothrow @nogc { return Limit - count_; }
    bool tryAdd(uint amount) @safe pure nothrow @nogc
    {
        if (amount > Limit - count_) return false;
        count_ += amount;
        return true;
    }
}

struct PreviewCount { mixin BoundedCount!3; }
struct ExportCount { mixin BoundedCount!6; }

unittest
{
    PreviewCount small;
    ExportCount large;
    assert(small.tryAdd(2U));
    assert(!small.tryAdd(2U));
    assert(small.value() == 2U && small.remaining() == 1U);
    assert(large.value() == 0U && large.tryAdd(6U));
    assert(!large.tryAdd(uint.max));
    assert(large.value() == 6U && large.remaining() == 0U);
    auto copy = small;
    assert(copy.tryAdd(1U));
    assert(copy.value() == 3U && small.value() == 2U);
}

int main()
{
    PreviewCount preview;
    ExportCount exportCount;
    if (!preview.tryAdd(2U) || preview.tryAdd(2U)) return 1;
    if (preview.value() != 2U || preview.remaining() != 1U) return 2;
    if (exportCount.value() != 0U || !exportCount.tryAdd(6U)) return 3;
    if (exportCount.tryAdd(uint.max) || exportCount.value() != 6U) return 4;
    auto copy = preview;
    if (!copy.tryAdd(1U) || copy.value() != 3U || preview.value() != 2U) return 5;
    writeln("preview=", preview.value(), " remaining=", preview.remaining());
    writeln("export=", exportCount.value(), " remaining=", exportCount.remaining());
    writeln("copy=", copy.value(), "; preview stays ", preview.value());
    return 0;
}
