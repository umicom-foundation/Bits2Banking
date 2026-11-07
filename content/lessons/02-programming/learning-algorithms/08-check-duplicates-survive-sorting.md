<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/08-check-duplicates-survive-sorting.md

PURPOSE:
Explain the lesson: Check that duplicates survive sorting.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that duplicates survive sorting

Sorted output is not enough to prove a sort is correct. A broken function could discard every value and still leave an apparently ordered empty sequence.

## Prepare

Open sort_records.c. The input contains five integers: 4, -2, 4, 0, -2. Before reading the expected array, write your own ordered result.

A correct result preserves both the number of values and how often each value occurs.

## Build an independent expectation

Count two -2 values, one zero and two 4 values. The expected order is -2, -2, 0, 4, 4.

The program checks count equals five and compares each position with this explicit expectation.

These checks answer different questions: count checks size; the sequence checks order and the retained values for this case.

## Follow insertion sort

In collections.c, each outer iteration saves one value. It shifts larger preceding values right, then places the saved value into the gap.

The saved variable prevents that value from being overwritten during the shifts. Equal values are not shifted by the greater-than comparison.

## Exercise

Trace the first three outer iterations with five boxes. Mark the sorted prefix after every iteration. Do not erase a value until you have shown where its replacement copy lives.

Then use the boundary suite's frequency-count approach to design another case with duplicates.

## Run and recover

Build using WORKFLOWS.md and run btb-sort_records. Expected output lists indices zero through four and the ordered values above.

If a value is missing, inspect the shift and final insertion separately. If count changed, investigate state corruption: this sorting function should not change the number of active elements.

In an application catalogue, losing a duplicate record may mean losing a distinct item that happens to share a sort key.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/sort_records.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-prove-a-search-loop-makes-progress.md) · [Next lesson](09-use-idempotence-as-an-extra-check.md)

