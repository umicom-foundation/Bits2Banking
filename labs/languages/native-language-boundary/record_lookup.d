/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/record_lookup.d
 *
 * PURPOSE:
 *   Separate D dictionary lookup, independent copies and deterministic output from model training.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

module record_lookup;
import std.stdio : writeln;
import std.algorithm.sorting : sort;

int main()
{
    // This is an in-memory label-to-count map, not a vector index or model.
    uint[string] reviewed;
    reviewed["alpha"] = 2;
    reviewed["beta"] = 0;
    assert(reviewed.length == 2);

    if (auto count = "alpha" in reviewed)
        ++*count;
    else
        return 1;
    // A present zero differs from a missing entry. Do not read a missing key.
    assert(("beta" in reviewed) !is null);
    assert(("missing" in reviewed) is null);

    auto sharedView = reviewed;
    sharedView["alpha"] = 4;
    assert(reviewed["alpha"] == 4);
    auto independent = reviewed.dup;
    independent["alpha"] = 9;
    assert(reviewed["alpha"] == 4);
    assert(independent.remove("beta"));
    assert(("beta" in reviewed) !is null);

    // Hash traversal has no required insertion order. Sort copied keys for
    // reproducible presentation; this is not a general serialization codec.
    auto orderedKeys = reviewed.keys;
    sort(orderedKeys);
    foreach (key; orderedKeys)
        writeln(key, "=", reviewed[key]);
    writeln("independent alpha=", independent["alpha"]);
    return 0;
}
