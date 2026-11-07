<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-rust/03-represent-success-and-refusal.md

PURPOSE:
Explain the lesson: Represent success and refusal.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Represent success and refusal

A function can produce a useful value or explain why it could not. Rust's Result type makes those two possibilities visible to its caller. In this project, an activity count advances until it reaches a fixed capacity.

## Setup recap

Install a Rust toolchain and open the Bits2Banking repository. Run `rustc --version` in your terminal. The lab README explains the matching C compiler and Framework SDK needed to link this example.

You can study the source without building. Read activity.rs beside main.rs in labs/languages/rust-activity. The small C model already exists; Rust is another caller.

## 1. Read the return type

`Result<c_int, ActivityError>` means success contains an integer compatible with C int, while failure contains ActivityError. The two possibilities are written Ok(value) and Err(reason).

The wrapper translates a negative result from the existing C bridge into Err(ActivityError::Refused). A successful result becomes Ok(next).

This translation is necessary because the bridge represents refusal with a negative integer. The Rust-facing interface names that situation instead of asking every screen to remember the sentinel.

## 2. Handle both outcomes

main.rs uses match. One branch prints the next count; the other prints that the request was refused. Both branches are visible in the source.

For inputs 0, 41, 999 and 1000, predict the results before reading the tests. The expected successful results are 1, 42 and 1000; advancing from 1000 is refused.

A refusal is not a request to invent a new result. A user interface should retain its current value and explain the refusal.

## Exercise

Add a paper trace for -1 and 1001. Find where the bridge rejects them, then follow the returned value into the Rust wrapper.

Explain why storing every result as an ordinary integer would make it easier to display -1 as a real activity count. Result makes this distinction explicit, but callers must still choose useful messages.

## Recovery

An unresolved external symbol concerns linking, not Result syntax. Follow the lab README before changing the wrapper. The underlying application rule remains in the C model.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/rust-activity/activity.rs). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](04-review-a-c-language-boundary.md)


[Previous lesson: Borrow a title](02-borrow-a-title.md)
