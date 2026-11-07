<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-zig/06-check-the-interface-contract.md

PURPOSE:
Explain the lesson: Check the interface contract.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the interface contract

The test suite checks that the Zig interface reports the same behavior as the existing C model. This is especially useful when several applications call the same service.

## Setup recap

Open the tests in activity.zig. They use std.testing to compare successful values and expected errors. Run them only with the complete lab command, which includes both C source files.

The tests need no user account and do not contact a service.

## 1. Check success at the edge

The last valid advance starts at 999 and returns 1000. Testing this edge distinguishes an inclusive stored capacity from an extra allowed increment.

A test that starts at 1000 must expect error.Refused. Read both assertions together before changing the comparison in the model.

## 2. Check signed extremes

The bridge accepts c_int. The tests include the smallest and largest representable values of that type, plus -1 and ordinary values around capacity.

These checks help expose a misplaced signed-to-unsigned conversion. They do not prove that every possible integer was examined.

A reasoned boundary set is often more informative than thousands of repeated ordinary cases.

## 3. Check independent requests

The final test repeats a successful request after a refusal. Because the function has no persistent counter, the two successful results should match.

If a future version introduces stored state, its tests and documentation must change deliberately. Do not silently preserve a stateless claim around a stateful implementation.

## Exercise

Add a table with columns for input, C bridge result and Zig result. Populate 41, 999, 1000 and -1.

Now explain which tests would fail if the wrapper treated zero as refusal. The current model never returns zero on a successful advance, so that particular mistake needs another interface scenario to expose it. This shows why tests prove only the contracts they exercise.

## Troubleshooting

A compilation error is not a failed assertion, and a missing library means no test execution occurred. Keep those outcomes separate in your notes.

The next useful extension is a screen that displays success or refusal while retaining its current state on error. Reuse this wrapper rather than duplicating its sentinel conversion.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/zig-activity/activity.zig). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-build-a-mixed-language-program.md)

