/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/exhaustive_states.d
 *
 * PURPOSE:
 *   Keep external state admission separate from exhaustive internal state dispatch.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


import std.stdio : writeln;
import std.traits : EnumMembers;

enum LaunchState : uint { queued = 10, created = 20, ready = 30, failed = 40 }

// Wire numbers are explicit protocol values, not raw enum storage or ordinals.
// An unknown value does not overwrite the caller's previously accepted state.
bool tryDecodeState(uint raw, ref LaunchState output) @safe pure nothrow @nogc
{
    LaunchState candidate;
    switch (raw) {
        case 10: candidate = LaunchState.queued; break;
        case 20: candidate = LaunchState.created; break;
        case 30: candidate = LaunchState.ready; break;
        case 40: candidate = LaunchState.failed; break;
        default: return false;
    }
    output = candidate;
    return true;
}

// This is an exhaustive mapping over admitted states. A new enumerator requires
// a conscious display decision; there is no fallback that conceals it.
string labelFor(LaunchState state) @safe pure nothrow @nogc
{
    final switch (state) {
        case LaunchState.queued: return "request queued";
        case LaunchState.created: return "process created; readiness unknown";
        case LaunchState.ready: return "application readiness acknowledged";
        case LaunchState.failed: return "startup failed";
    }
}

unittest {
    LaunchState current = LaunchState.ready;
    assert(!tryDecodeState(0, current) && current == LaunchState.ready);
    assert(!tryDecodeState(11, current) && current == LaunchState.ready);
    assert(!tryDecodeState(uint.max, current) && current == LaunchState.ready);
    static foreach (member; EnumMembers!LaunchState) {
        assert(tryDecodeState(cast(uint)member, current));
        assert(current == member);
        assert(labelFor(current).length != 0);
    }
    assert(labelFor(LaunchState.created) != labelFor(LaunchState.ready));
}

void main() {
    LaunchState state = LaunchState.queued;
    if (!tryDecodeState(20, state)) return;
    writeln("Umicom D state example: ", labelFor(state));
}
