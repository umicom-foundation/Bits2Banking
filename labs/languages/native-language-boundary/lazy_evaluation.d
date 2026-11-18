/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/lazy_evaluation.d
 *
 * PURPOSE:
 *   Observe zero, repeated and single evaluation of a D lazy argument.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module lazy_evaluation;
import std.stdio : writeln;

int nextValue(ref int calls)
{
    ++calls;
    return calls;
}
int ignoreCandidate(lazy int candidate)
{
    // The caller expression has no work to do because candidate is never read.
    return 40;
}
int readTwice(lazy int candidate)
{
    // Two separate statements make the observation order explicit.
    const int first = candidate;
    const int second = candidate;
    return first + second;
}
int snapshotOnce(lazy int candidate)
{
    // A local value is deliberate caching, unlike repeated lazy access.
    const int value = candidate;
    return value + value;
}
unittest
{
    int calls = 0;
    assert(ignoreCandidate(nextValue(calls)) == 40 && calls == 0);
    assert(readTwice(nextValue(calls)) == 3 && calls == 2);
    calls = 0;
    assert(snapshotOnce(nextValue(calls)) == 2 && calls == 1);
}
void main()
{
    int calls = 0;
    const int ignored = ignoreCandidate(nextValue(calls));
    assert(ignored == 40 && calls == 0);
    writeln("ignored: result=", ignored, " evaluations=", calls);
    const int repeated = readTwice(nextValue(calls));
    assert(repeated == 3 && calls == 2);
    writeln("repeated: result=", repeated, " evaluations=", calls);
    calls = 0;
    const int snapshot = snapshotOnce(nextValue(calls));
    assert(snapshot == 2 && calls == 1);
    writeln("snapshot: result=", snapshot, " evaluations=", calls);
}
