<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/32-full-list-and-duplicate-results.md

PURPOSE:
Keep duplicate and full-list results meaningful

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep duplicate and full-list results meaningful

A watchlist is a collection of instruments that a trading screen follows. This module uses the real Framework watchlist to explain how an array, a count and a capacity work together. You can study every example without a broker connection or market data.

1. Open PowerShell and run `Set-Location C:\umicom\Umicom-Applications\framework`. In bash, use `cd /path/to/Umicom-Applications/framework`.
2. Open `include/umicom/trading/watchlist.h`, `src/trading/watchlist.c` and `tests/trading/test_watchlist_alerts.c` in your editor. A header declares the interface; a source file implements it; a test checks observable results.
3. No accounts or credentials are needed. Keep experiments in a separate learning copy. If you later run tests, first finish the normal configure and build for your checkout; a previous executable does not contain newly edited source.

## An error result is part of the interface

A function's contract describes accepted inputs, output values and effects. For `umi_watchlist_add`, a duplicate is different from a new instrument that cannot fit. A trading screen can select the existing item when it receives `UMI_STATUS_ALREADY_EXISTS`. It can explain the limit when it receives `UMI_STATUS_CAPACITY_EXCEEDED`.

A tempting change is to reject `count >= capacity` before searching. That stops invalid reads, but changes the result for a duplicate in a full list. The corrected implementation first rejects impossible counts, then searches valid occupied entries, then refuses insertion when no room remains.

| Collection | Requested instrument | Expected result |
|---|---|---|
| Empty | Valid new item | OK; count becomes 1 |
| Partly filled | Existing item | ALREADY_EXISTS; unchanged |
| Full | Existing item | ALREADY_EXISTS; unchanged |
| Full | New item | CAPACITY_EXCEEDED; unchanged |
| Count above capacity | Valid item | INVALID_ARGUMENT; unchanged |

## Follow the regression fixture

1. Open `check_watchlist_boundaries` in the test source.
2. Find the loop that creates unique identifiers with `snprintf`. The identifier is the stable identity; display text alone is not enough to distinguish instruments.
3. Check that each successful addition increases count by exactly one.
4. Read the final candidate again. It is the last inserted item and must be recognized as a duplicate.
5. Replace the candidate with the original fixture instrument. That different identifier cannot be added to the full list.

`snprintf` receives the destination's capacity. Its return value is checked because truncating an identifier could accidentally create a duplicate. A nonnegative return is the length that would have been written, excluding the ending zero byte. It must also be smaller than the destination capacity.

## Exercise

Write a short UI message for each status in the table. Avoid reporting a duplicate as a broker rejection: this operation is local list maintenance and sends no order. The lesson is complete when your messages preserve the distinction between invalid input, an existing item and exhausted local storage.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/trading/test_watchlist_alerts.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Check the count before searching the array](31-validate-before-search.md) · [Next: Verify that rejection leaves the collection unchanged](33-prove-failure-keeps-state.md)
