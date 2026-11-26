/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/inherited_members.d
 *
 * PURPOSE:
 *   Compare immediate and inherited class members through D compile-time reflection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import std.meta : staticIndexOf;
import std.stdio : writeln;

class BaseProbe
{
    int threshold;
}

final class WaterProbe : BaseProbe
{
    int sampleCount;
}

/* Ask about named members rather than relying on the order of the trait's
 * sequence. allMembers can also discover other inherited declarations. */
alias DirectMembers = __traits(derivedMembers, WaterProbe);
alias AllMembers = __traits(allMembers, WaterProbe);

enum directThreshold = staticIndexOf!("threshold", DirectMembers) >= 0;
enum allThreshold = staticIndexOf!("threshold", AllMembers) >= 0;
enum directSampleCount = staticIndexOf!("sampleCount", DirectMembers) >= 0;

static assert(!directThreshold && allThreshold && directSampleCount);

void main()
{
    /* Print three compile-time observations without creating Probe objects. */
    writeln("direct threshold: ", directThreshold ? "yes" : "no");
    writeln("all threshold: ", allThreshold ? "yes" : "no");
    writeln("direct sampleCount: ", directSampleCount ? "yes" : "no");
}
