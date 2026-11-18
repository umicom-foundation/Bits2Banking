/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/explicit_job_states.d
 *
 * PURPOSE:
 *   Teach named states, explicit byte admission, compile-time enumeration and exhaustive labels.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module explicit_job_states;
import std.stdio : writeln;
import std.traits : EnumMembers;

// Assigned bytes are an example wire contract; unnamed gaps stay invalid.
enum JobState : ubyte { queued=0, running=2, complete=5, failed=9 }
enum supportedStateCount=EnumMembers!JobState.length;
static assert(supportedStateCount==4);
static assert(JobState.init==JobState.queued);

bool decodeState(ubyte raw, ref JobState result) @safe pure nothrow @nogc
{
    // External integers are admitted explicitly before becoming a named state.
    switch(raw) {
        case 0: result=JobState.queued;return true;
        case 2: result=JobState.running;return true;
        case 5: result=JobState.complete;return true;
        case 9: result=JobState.failed;return true;
        default: return false;
    }
}
string label(JobState state) @safe pure nothrow @nogc
{
    // A new enum member requires a deliberate update to this exhaustive map.
    final switch(state) {
        case JobState.queued: return "queued";
        case JobState.running: return "running";
        case JobState.complete: return "complete";
        case JobState.failed: return "failed";
    }
}
unittest
{
    foreach(uint raw;0..256) {
        JobState state=JobState.failed;
        bool accepted=decodeState(cast(ubyte)raw,state);
        bool expected=raw==0 || raw==2 || raw==5 || raw==9;
        assert(accepted==expected);
        if(accepted) {
            assert(cast(uint)state==raw);
            assert(label(state).length>0);
        } else {
            assert(state==JobState.failed);
        }
    }
}
void main()
{
    writeln("Declared states: ",supportedStateCount);
    static foreach(state;EnumMembers!JobState)
        writeln(cast(uint)state," ",label(state));
    JobState selected=JobState.failed;
    assert(!decodeState(3,selected));
    writeln("Refused byte 3; preserved: ",label(selected));
}
