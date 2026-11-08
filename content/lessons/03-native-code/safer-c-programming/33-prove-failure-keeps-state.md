<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/33-prove-failure-keeps-state.md

PURPOSE:
Verify that rejection leaves the collection unchanged

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Verify that rejection leaves the collection unchanged

A watchlist is a collection of instruments that a trading screen follows. This module uses the real Framework watchlist to explain how an array, a count and a capacity work together. You can study every example without a broker connection or market data.

1. Open PowerShell and run `Set-Location C:\umicom\Umicom-Applications\framework`. In bash, use `cd /path/to/Umicom-Applications/framework`.
2. Open `include/umicom/trading/watchlist.h`, `src/trading/watchlist.c` and `tests/trading/test_watchlist_alerts.c` in your editor. A header declares the interface; a source file implements it; a test checks observable results.
3. No accounts or credentials are needed. Keep experiments in a separate learning copy. If you later run tests, first finish the normal configure and build for your checkout; a previous executable does not contain newly edited source.

## Observe both the result and the state

Checking an error code proves only that the function reported failure. A failed call could still change count, overwrite an entry or clear a selection. A useful regression test checks the externally visible state too.

The watchlist test copies the complete initialized fixture before a rejected operation:

```c
memcpy(&before, &watchlist, sizeof(before));
assert(umi_watchlist_add(&watchlist, &candidate) ==
       UMI_STATUS_CAPACITY_EXCEEDED);
assert(memcmp(&before, &watchlist, sizeof(before)) == 0);
```

`memcpy` copies a known number of bytes between separate storage regions. `sizeof(before)` gives the storage size of this object. `memcmp` compares those bytes and returns zero when they match. This fixture uses static storage, which begins zero-initialized, and snapshots the same live object before the call. The check tests that rejection did not change its representation. Do not use byte comparisons as a universal equality operation for separately constructed C structures; padding bytes may differ even when their fields are logically equal.

## Trace the damaged-count case

1. The test fills a valid list first.
2. It assigns a deliberately impossible count: capacity plus one, then `SIZE_MAX`, the largest `size_t` value.
3. It snapshots the damaged object.
4. It expects INVALID_ARGUMENT and exactly the same bytes afterward.
5. It reinitializes the list and proves a valid insertion works again.

These inputs exercise the public boundary. They do not attempt to read arbitrary memory or submit malformed data to a real broker.

## Recovery belongs to the caller

Rejecting the invalid count is preferable to silently clamping it. Clamping would disguise an earlier defect and might hide entries from the user. An application can show a recoverable error, reload a trusted saved list or let the user create a fresh one. It must make that choice explicitly.

## Practice

Add a test for a null instrument pointer in your learning copy. Assert INVALID_ARGUMENT and compare the list with its snapshot. If the test executable was built before your source edit, rebuild that target before interpreting its result.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/trading/test_watchlist_alerts.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Keep duplicate and full-list results meaningful](32-full-list-and-duplicate-results.md) · [Next: Understand what a copied watchlist entry owns](34-values-pointers-and-serial-access.md)

[Written course contents](index.md)
