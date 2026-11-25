<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/57-make-grouped-step-counts-reproducible.md

PURPOSE:
Make grouped step counts reproducible

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Make grouped step counts reproducible

A review preserves the order in which the interpreter recorded its steps. A short summary serves a different purpose. It groups steps that have the same kind. Give that summary a fixed key order so two readers can compare it line by line.

## Count by kind and sort the keys

A D associative array maps a key to a value. In `size_t[string] counts`, a step kind such as `"statement"` is the string key and its count has type `size_t`. The `get` call supplies zero when the group is first seen. The assignment then records the incremented count.

~~~d
import std.algorithm.sorting : sort;
import std.conv : to;

string[] summaryKinds(Review review)
{
    // Group the admitted steps without changing the execution sequence.
    size_t[string] counts;
    foreach (step; review.steps)
        counts[step.stepKind] = counts.get(step.stepKind, 0) + 1;

    // Sort the copied keys so the summary always uses the same order.
    auto keys = counts.keys;
    sort(keys);

    string[] entries;
    foreach (key; keys)
        entries ~= key ~ "=" ~ to!string(counts[key]);
    return entries;
}
~~~

D does not specify associative-array iteration order. The `keys` property gives the lesson a separate array to sort. Reading the counts back by key keeps each label attached to its own count. [D associative-array keys and iteration](https://dlang.org/spec/hash-map.html) · [Phobos sort](https://dlang.org/library/std/algorithm/sorting/sort.html)

## Trace the saved review

| Step ordinal | Kind | Count after this step |
| --- | --- | --- |
| 1 | `statement` | `statement` has 1 |
| 2 | `statement` | `statement` has 2 |
| 3 | `statement` | `statement` has 3 |
| 4 | `return` | `return` has 1 |

Before sorting, either key can appear first in `counts.keys`. After sorting by the characters in each key, `return` comes before `statement` because `r` comes before `s`. For the saved four-step review, the expected D array is `["return=1", "statement=3"]`.

1. Write two possible key arrays on paper, one with `statement` first and one with `return` first. Sort each and look up the two counts. Both yield the same pair of entries.
2. Compare the first and last steps in the original review. They still show statement 1 and return 4. Sorting the copied keys preserves those source observations in order.
3. Check that 1 plus 3 matches the four steps. Each entry counts a kind of step. The instruction total of 10 comes from the count carried by each step and checked in the previous lesson.

When a preview shows only its first two step details, use the full accepted review for these summary counts. Display limits belong to the presentation. The grouped numbers still describe the entire admitted trace.

[Course contents](index.md) · [Previous lesson · Match a final result with its producer status](56-match-a-final-result-with-its-producer-status.md) · [Next lesson · Send the summary and diagnostics to their own streams](58-send-summary-and-diagnostics-to-their-own-streams.md) · [Related lesson · Look up records without confusing storage with learning](28-look-up-records-with-associative-arrays.md) · [HTML edition](../../../courses/learning-d/lessons/57-make-grouped-step-counts-reproducible.html)
