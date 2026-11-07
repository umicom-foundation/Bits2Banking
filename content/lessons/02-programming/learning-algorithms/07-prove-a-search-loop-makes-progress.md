<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/07-prove-a-search-loop-makes-progress.md

PURPOSE:
Explain the lesson: Prove a search loop makes progress.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Prove a search loop makes progress

A loop must eventually stop for the inputs it promises to handle. Binary search achieves this by shrinking a finite interval every time it repeats.

## Prepare

Read BtbListFindSorted in collections.c. The interval is [first, last): positions from first up to, but excluding, last. Its length is last - first.

No code execution is required for the first exercise.

## Inspect both branches

When the middle value is smaller than the target, first becomes middle + 1. Otherwise last becomes middle.

Because first is smaller than last when the loop starts, middle lies inside the interval. Either update removes at least one candidate.

For a one-element interval [3,4), middle is 3. The next interval is either [4,4) or [3,3). Both are empty.

## Try the faulty update on paper

Suppose the first branch used first = middle instead. With [3,4), first would remain 3. If the comparison took the same branch again, nothing would change.

This is why the +1 is part of correctness, not a formatting preference.

## Exercise

Trace searches for a value below every element and above every element. Write the interval length after each step. It must decrease until zero.

For eight candidates, the lengths might be 8, 4, 2, 1, 0 depending on the branch choices. Do not claim every search takes exactly the same number of comparisons.

## Apply the method elsewhere

For a parser, the progress measure may be unread bytes. For a queue consumer it may be pending jobs. Identify the quantity that decreases, and identify any branch that can repeat without decreasing it.

A bounded loop can still compute a wrong result. Termination and result correctness need separate arguments and checks.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/collections.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-find-the-first-duplicate.md) · [Next lesson](08-check-duplicates-survive-sorting.md)

