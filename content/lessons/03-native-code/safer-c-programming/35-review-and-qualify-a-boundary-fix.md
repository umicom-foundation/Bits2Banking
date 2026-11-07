<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/35-review-and-qualify-a-boundary-fix.md

PURPOSE:
Turn a boundary fix into a repeatable review

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Turn a boundary fix into a repeatable review

A watchlist is a collection of instruments that a trading screen follows. This module uses the real Framework watchlist to explain how an array, a count and a capacity work together. You can study every example without a broker connection or market data.

1. Open PowerShell and run `Set-Location C:\umicom\Umicom-Applications\framework`. In bash, use `cd /path/to/Umicom-Applications/framework`.
2. Open `include/umicom/trading/watchlist.h`, `src/trading/watchlist.c` and `tests/trading/test_watchlist_alerts.c` in your editor. A header declares the interface; a source file implements it; a test checks observable results.
3. No accounts or credentials are needed. Keep experiments in a separate learning copy. If you later run tests, first finish the normal configure and build for your checkout; a previous executable does not contain newly edited source.

## A small fix needs a precise claim

The watchlist guard repairs one out-of-bounds read path caused by an invalid stored count. It does not establish that an entire trading application is memory-safe. Review the changed contract, the tests and the build that actually contains the fix.

## Source review checklist

1. Identify the first read or write controlled by each input. Place validation before that operation.
2. Check empty, one-item, full and impossible states.
3. Preserve documented duplicate and capacity results.
4. Verify that refusal leaves caller-owned data unchanged.
5. Check pointer lifetime and whether callbacks or other threads can change state.
6. Review the actual destination size rather than repeating a numeric constant.

## Run the focused regression when a build is available

From the Framework checkout in PowerShell or bash:

```text
cmake --build build/windows-ucrt64-debug --target umicom-trading-watchlist-alerts-test --parallel 2
ctest --test-dir build/windows-ucrt64-debug -R "^framework[.]trading_watchlist_alerts$" --output-on-failure --no-tests=error
```

Use the build directory created by your own configuration; the example is the standalone Windows directory. In the parent Applications build, use its `build/windows-ucrt64-all-debug` directory instead. `--target` requests the named executable and its dependencies. `-R` selects the exact test name. A nonzero exit code means the command failed. Read the output before continuing.

A passing result confirms these executed cases on that source and environment. It is not proof about every possible input. Sanitizers are compiler-supported runtime checks that can catch invalid accesses during exercised paths. Use a supported sanitizer configuration as an additional check; enabling one does not replace bounds reasoning or guarantee full coverage.

## Record a useful result

Record the source revision, local changes, compiler, build directory, command and result. Keep a skipped or missing test separate from a pass. If an executable was quarantined or could not launch, investigate that environment failure rather than treating the test as successful.

## Exercise

Write a review note containing the original unsafe ordering, the new ordering, the cases added and what remains unverified. Another contributor should be able to reproduce the check without needing the conversation that led to the fix.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/trading/test_watchlist_alerts.c).

## Continue learning

[Course contents](../../../courses/safer-c-programming/index.html) · [Previous: Understand what a copied watchlist entry owns](34-values-pointers-and-serial-access.md)
