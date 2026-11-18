/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/virtual_rules.d
 *
 * PURPOSE:
 *   Separate runtime interface dispatch from static type inspection and explicit object ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module virtual_rules;
import std.stdio : writeln;

interface BatchRule
{
    bool admit(uint items);
    uint limit();
}
abstract class BoundedRule : BatchRule
{
    private immutable uint bound;
    this(uint bound)
    {
        if (bound == 0 || bound > 64) throw new Exception("limit must be 1..64");
        this.bound = bound;
    }
    final uint limit() { return bound; }
    abstract bool admit(uint items);
}
final class PositiveRule : BoundedRule
{
    this(uint bound) { super(bound); }
    override bool admit(uint items) { return items > 0 && items <= limit(); }
}
final class EmptyAllowedRule : BoundedRule
{
    this(uint bound) { super(bound); }
    override bool admit(uint items) { return items <= limit(); }
}
static assert(is(PositiveRule : BatchRule));
static assert(is(EmptyAllowedRule : BatchRule));

void require(bool condition, string message)
{
    // Ordinary validation remains active even with release-mode assertion removal.
    if (!condition) throw new Exception(message);
}
void checkRules()
{
    BatchRule positive = new PositiveRule(4);
    BatchRule emptyAllowed = new EmptyAllowedRule(2);
    require(!positive.admit(0), "positive rule rejects zero");
    require(positive.admit(1) && positive.admit(4), "positive boundary");
    require(!positive.admit(5), "positive excess");
    require(emptyAllowed.admit(0) && emptyAllowed.admit(2), "empty boundary");
    require(!emptyAllowed.admit(3), "empty excess");
    require(positive.limit() == 4 && emptyAllowed.limit() == 2, "independent immutable limits");
    // typeof sees the declared interface reference. A checked runtime cast
    // inspects the referenced object and returns null on a mismatched class.
    static assert(is(typeof(positive) == BatchRule));
    require(cast(PositiveRule)positive !is null, "matching dynamic class");
    require(cast(EmptyAllowedRule)positive is null, "mismatched dynamic class");
    BatchRule aliasOfPositive = positive;
    require(aliasOfPositive is positive, "reference assignment preserves object identity");
    bool rejected = false;
    try { auto invalid = new PositiveRule(0); }
    catch (Exception error)
    {
        // Retain the initial broad check for review. Matching the message now
        // distinguishes the intended constructor refusal from another exception.
        version (none) { rejected = true; }
        rejected = error.msg == "limit must be 1..64";
    }
    require(rejected, "constructor validates its external input");
}
unittest { checkRules(); }
void main()
{
    checkRules();
    writeln("Umicom virtual rules: all checks passed");
}
