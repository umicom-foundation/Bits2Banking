<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-rust/06-test-boundaries-and-independent-calls.md

PURPOSE:
Explain the lesson: Test boundaries and independent calls.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test boundaries and independent calls

A useful test checks a promise that could be broken. The activity wrapper promises to preserve the C model's results and to represent refusals clearly.

## Setup recap

The tests live in activity.rs inside a test-only module. Follow the lab README to compile a test executable linked to the same C bridge used by the example program.

A test-only module is included when Rust compiles with its test mode. It is not part of the normal demonstration executable.

## 1. Check normal and limiting values

The success test covers zero, an ordinary value and the last successful advance. Testing only 41 would miss an error at the limit.

The rejection test covers a negative input, the smallest signed integer, the capacity itself, a value above capacity and the largest signed integer.

These values exercise conversion and boundary decisions. They are not random numbers added merely to increase test count.

## 2. Check a sequence

Another test performs a success, then a refusal, then the same success again. The final result should agree with the first.

This checks that the wrapper does not retain an accidental error state between calls. It does not prove thread safety for a future implementation with mutable shared state.

The current function operates on values and has no stored counter. A user interface owns the current count.

## 3. Make a controlled prediction

Without changing the shared repository, copy the exercise into a practice branch or folder and change the wrapper's negative-result check in that practice copy. Predict which assertion would expose the error.

Restore the intended implementation before using the example elsewhere. A deliberately broken exercise belongs in an isolated practice copy, not in a published application.

## Expected result and recovery

All authored assertions are expected to pass with the matching source and toolchain. Record actual execution separately. A linker failure means no tests ran.

When an assertion fails, compare expected and actual values, then trace Rust wrapper, C bridge and C model in that order. Do not weaken an assertion solely to make the report green.

## Extend the lab

Add a presentation function that turns ActivityError into a short user message. Test that function separately from the arithmetic rule so wording changes do not obscure model regressions.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/rust-activity/activity.rs). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-link-a-rust-client-to-c.md)

