<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/30-count-capacity-and-index.md

PURPOSE:
Understand count, capacity and array indices

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand count, capacity and array indices

A watchlist is a collection of instruments that a trading screen follows. This module uses the real Framework watchlist to explain how an array, a count and a capacity work together. You can study every example without a broker connection or market data.

1. Open PowerShell and run `Set-Location C:\umicom\Umicom-Applications\framework`. In bash, use `cd /path/to/Umicom-Applications/framework`.
2. Open `include/umicom/trading/watchlist.h`, `src/trading/watchlist.c` and `tests/trading/test_watchlist_alerts.c` in your editor. A header declares the interface; a source file implements it; a test checks observable results.
3. No accounts or credentials are needed. Keep experiments in a separate learning copy. If you later run tests, first finish the normal configure and build for your checkout; a previous executable does not contain newly edited source.

## Three numbers with different jobs

An array is a consecutive set of storage slots. `UmiWatchlist` contains an array of `UmiInstrument` values and a `size_t count`. A structure groups these fields into one value. `size_t` is an unsigned integer type used for sizes and array positions. The capacity comes from `UMI_TRADING_MAX_WATCHLIST`, currently 64 in `trading/types.h`.

Capacity means space exists for that many entries. Count means that many entries have been added. An index identifies one entry, starting at zero. When count is 3, the occupied indices are 0, 1 and 2. Index 3 is the next free slot, provided capacity exceeds 3.

```text
capacity = 6
slots    = [A][B][C][ ][ ][ ]
indices  =  0  1  2  3  4  5
count    = 3
```

The essential rule is `0 <= count <= capacity`. C does not enforce this relationship for a public structure. Code can assign 500 to count even though only 64 slots exist. This assignment alone may be legal C, but using that count as a loop bound can lead to invalid memory access.

## Read the implementation

1. Find `umi_watchlist_init`. It sets count to zero. It does not need to erase every unused slot because valid operations read only occupied slots.
2. Find `watchlist->instruments[watchlist->count]`. The arrow accesses a member through a pointer. The square brackets select an array element.
3. Find the increment after the assignment. The element becomes part of the logical collection only after its value has been written.

## Try on paper

Draw a four-slot array. Add three different instruments, then identify count, last occupied index and next free index. After the fourth insertion there is no free index. The answer is count 4, last index 3; index 4 is outside the array.

## Check your understanding

An empty initialized list has count zero and still has full capacity. It does not contain 64 valid instruments. Keeping this distinction explicit prevents reading uninitialized storage and confusing empty-state UI displays.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/trading/watchlist.h).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Next: Check the count before searching the array](31-validate-before-search.md)
