<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/34-values-pointers-and-serial-access.md

PURPOSE:
Understand what a copied watchlist entry owns

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand what a copied watchlist entry owns

A watchlist is a collection of instruments that a trading screen follows. This module uses the real Framework watchlist to explain how an array, a count and a capacity work together. You can study every example without a broker connection or market data.

1. Open PowerShell and run `Set-Location C:\umicom\Umicom-Applications\framework`. In bash, use `cd /path/to/Umicom-Applications/framework`.
2. Open `include/umicom/trading/watchlist.h`, `src/trading/watchlist.c` and `tests/trading/test_watchlist_alerts.c` in your editor. A header declares the interface; a source file implements it; a test checks observable results.
3. No accounts or credentials are needed. Keep experiments in a separate learning copy. If you later run tests, first finish the normal configure and build for your checkout; a previous executable does not contain newly edited source.

## Copying a value is different from borrowing a pointer

The assignment `watchlist->instruments[count] = *instrument` copies one `UmiInstrument` value into the array. `*instrument` means the value at the supplied address. Inspect `UmiInstrument` in `trading/types.h`: its identifier, symbol, venue and currency are fixed-size fields rather than separately allocated text pointers. The caller may later change its original instrument variable without changing the stored copy.

If a structure instead contained `char *name`, ordinary structure assignment would copy that address, not the characters it points to. Freeing or replacing the pointed-to text could leave a dangling pointer: an address whose former object no longer exists. This is why you must inspect the actual type before claiming a copy is independent.

## A lifetime exercise

```text
caller variable: candidate ── value copied ──> watchlist slot
caller changes candidate.symbol
stored slot keeps its earlier symbol
```

1. Find every field of `UmiInstrument`.
2. Classify it as an inline value or a pointer.
3. Check `umi_instrument_valid` before assuming a fixed array contains a terminated string.
4. Read `umi_instrument_same`: the identifier determines duplicate identity.

## Serial access

Serial access means one operation uses the collection at a time. The watchlist does not contain a lock. If another thread changes count while an addition is searching, a count check at the beginning does not make the whole sequence safe. A GTK application commonly owns its UI model on the main thread and delivers background results through a controlled message boundary. Document which thread owns the list instead of relying on timing.

## Application design

Trader, Bank or a portfolio viewer can use the same Framework contract. A thin client converts user input into a validated instrument, calls the service, then redraws from the resulting state. It should not duplicate the capacity or identity rules in each button handler.

## Check your understanding

Setting one local pointer to NULL after freeing storage does not clear other aliases to that storage. In this watchlist, inline value storage avoids that particular text-ownership problem, but the caller must still keep the watchlist object itself alive during every operation.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/trading/types.h).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Verify that rejection leaves the collection unchanged](33-prove-failure-keeps-state.md) · [Next: Turn a boundary fix into a repeatable review](35-review-and-qualify-a-boundary-fix.md)

[Written course contents](index.md)
