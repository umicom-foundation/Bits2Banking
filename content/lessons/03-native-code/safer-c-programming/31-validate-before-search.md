<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/31-validate-before-search.md

PURPOSE:
Check the count before searching the array

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check the count before searching the array

A watchlist is a collection of instruments that a trading screen follows. This module uses the real Framework watchlist to explain how an array, a count and a capacity work together. You can study every example without a broker connection or market data.

1. Open PowerShell and run `Set-Location C:\umicom\Umicom-Applications\framework`. In bash, use `cd /path/to/Umicom-Applications/framework`.
2. Open `include/umicom/trading/watchlist.h`, `src/trading/watchlist.c` and `tests/trading/test_watchlist_alerts.c` in your editor. A header declares the interface; a source file implements it; a test checks observable results.
3. No accounts or credentials are needed. Keep experiments in a separate learning copy. If you later run tests, first finish the normal configure and build for your checkout; a previous executable does not contain newly edited source.

## A read also needs a boundary

A buffer overflow is often described as writing beyond storage. Reading beyond an array is also invalid. It may reveal unrelated bytes, crash, or appear to work until a build changes memory layout. A check placed after the read cannot protect that earlier read.

The watchlist searches existing instruments before adding a new one. Searching is necessary to reject a duplicate. The corrected order is:

```text
validate the pointers and new instrument
reject count greater than capacity
search entries from index 0 up to count - 1
reject a new entry if the list is full
copy the entry and increase count
```

The count guard uses `>` rather than `>=`. A count equal to capacity describes a full but valid list. Searching that list is safe. A count above capacity describes an impossible state and must be rejected before the loop.

## Inspect the real guard

```c
if (watchlist->count > UMI_TRADING_MAX_WATCHLIST) {
    return UMI_STATUS_INVALID_ARGUMENT;
}
```

`if` executes its body when the expression is true. `return` ends the current function and supplies its result to the caller. The symbolic status communicates the category of failure without modifying the collection.

1. Locate this guard in `watchlist.c`.
2. Locate the loop below it. Its condition is `index < watchlist->count`; an empty list therefore reads no elements.
3. Trace count 64. The last possible read uses index 63.
4. Trace count 65. The guard returns before the first read.

## Extend the review

Look for other functions whose loops use a caller-owned count. Do not mechanically add the same check everywhere. Determine the real array length, whether the count is validated by an earlier boundary, and whether concurrent mutation is allowed. A guard is useful only when it matches the data representation.

## Expected result

You should be able to explain why the capacity check before insertion was insufficient on its own: insertion was not the first operation that accessed the array. This reasoning applies to message batches, document tabs and account result tables as well.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/trading/watchlist.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Understand count, capacity and array indices](30-count-capacity-and-index.md) · [Next: Keep duplicate and full-list results meaningful](32-full-list-and-duplicate-results.md)

[Written course contents](index.md)
