/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/inspect_umc_header.d
 *
 * PURPOSE:
 *   Teach a no-GC bounded wire-envelope function while keeping full bytecode admission in Umicom C.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module inspect_umc_header;
import std.stdio : writeln;

struct EnvelopeInfo
{
    ubyte profile;
    ushort instructionCount;
    size_t encodedBytes;
}

/* ref deliberately preserves the caller's previous value on refusal. An out
 * parameter would initialize it on entry and would break that contract.
 * The byte slice is borrowed for this call; no pointer or view is retained. */
bool inspectEnvelope(scope const(ubyte)[] bytes, ref EnvelopeInfo result)
    @safe pure nothrow @nogc
{
    if (bytes.length < 8 || bytes.length > 2312) return false;
    if (bytes[0] != 0x55 || bytes[1] != 0x4D || bytes[2] != 0x43 || bytes[3] != 0x42) return false;
    if (bytes[4] < 1 || bytes[4] > 6 || bytes[5] != 0) return false;
    const count = cast(uint)bytes[6] | (cast(uint)bytes[7] << 8);
    if (count == 0 || count > 256) return false;
    const size_t needed = 8 + cast(size_t)count * 9;
    if (bytes.length != needed) return false;
    const candidate = EnvelopeInfo(bytes[4], cast(ushort)count, needed);
    result = candidate;
    return true;
}

immutable ubyte[26] fixture = [
    0x55, 0x4D, 0x43, 0x42, 1, 0, 2, 0,
    1, 42, 0, 0, 0, 0, 0, 0, 0,
    7, 0, 0, 0, 0, 0, 0, 0, 0];

void requireRefusal(scope const(ubyte)[] bytes) @safe
{
    const sentinel = EnvelopeInfo(99, 77, 66);
    auto result = sentinel;
    assert(!inspectEnvelope(bytes, result));
    assert(result == sentinel);
}

unittest
{
    EnvelopeInfo result;
    assert(inspectEnvelope(fixture[], result));
    assert(result == EnvelopeInfo(1, 2, 26));
    foreach (length; 0 .. fixture.length) requireRefusal(fixture[0 .. length]);
    ubyte[27] trailing;
    trailing[0 .. fixture.length] = fixture[];
    requireRefusal(trailing[]);
    foreach (caseNumber; 0 .. 7) {
        ubyte[26] damaged;
        damaged[] = fixture[];
        switch (caseNumber) {
        case 0: damaged[0] = 0; break;
        case 1: damaged[4] = 0; break;
        case 2: damaged[4] = 7; break;
        case 3: damaged[5] = 1; break;
        case 4: damaged[6] = 0; break;
        case 5: damaged[6] = 1; damaged[7] = 1; break;
        case 6: damaged[6] = 3; break;
        default: assert(0);
        }
        requireRefusal(damaged[]);
    }
    ubyte[26] invalidProgram;
    invalidProgram[] = fixture[];
    invalidProgram[8] = 255;
    assert(inspectEnvelope(invalidProgram[], result)); // Intentionally only an envelope check.
}

void main()
{
    EnvelopeInfo result;
    if (!inspectEnvelope(fixture[], result)) throw new Exception("Literal envelope refused");
    writeln("Envelope facts: profile ", result.profile,
        ", instructions ", result.instructionCount, ", bytes ", result.encodedBytes);
    writeln("The inspector is @safe pure nothrow @nogc; this console program uses the normal D runtime.");
    writeln("Full opcode, stack and profile validation remains owned by the Umicom C runtime.");
}
