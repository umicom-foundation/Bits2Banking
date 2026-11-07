<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/06-find-the-first-duplicate.md

PURPOSE:
Explain the lesson: Find the first matching duplicate.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the first matching duplicate

A search can return any match or the first match. These are different promises when a collection contains duplicates.

## Prepare

Open search_trace.c in the collections lab. Its sorted catalogue is -4, 0, 0, 7, 9. Array positions begin at zero, so the two zeroes occupy positions 1 and 2.

BtbListFindSorted promises the first matching position.

## Trace the interval

Write first = 0 and last = 5. The active search interval includes first and excludes last.

For target zero, middle is 2. The value there is equal to the target, so the algorithm moves last to 2 rather than returning immediately.

Now middle is 1. Equality again moves last to 1. Then middle is 0; -4 is smaller, so first becomes 1.

The interval is empty when first equals last. Position 1 is the earliest location where zero could appear.

## Confirm membership

The final candidate could be the end of the list or could contain another value. The function checks both conditions before publishing the output index.

A lower bound is a candidate position, not automatically proof of a match.

## Run the example

Use WORKFLOWS.md to build. Run btb-search_trace and find the output for zero. Expect first index 1.

The program also compares the binary result with the existing linear search across present and absent targets.

## Exercise

Change the catalogue to 0, 0, 0, 7, 9 and predict the result for zero. Then search for 6: the insertion candidate lies before 7, but the reported result must be BTB_NOT_FOUND.

Keep the sorted-input promise. Rearranging values randomly invalidates the assumptions that make this search correct.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/search_trace.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-choose-search-for-a-workload.md) · [Next lesson](07-prove-a-search-loop-makes-progress.md)

