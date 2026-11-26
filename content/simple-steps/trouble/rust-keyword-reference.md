<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/rust-keyword-reference.md

PURPOSE:
Give learners an additional practical case for Rust 2024 Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find why a value is unavailable after a move

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a local ownership exercise, a named value is assigned to a new owner, then the original name is used.

1. Mark the assignment that moved ownership. Locate the subsequent reference in the exercise.
2. Use the edition’s appropriate borrow example for a read-only operation and compare the compiled result.

**Check your result.** When a move consumes the original binding, the later use is refused. The borrowing exercise can leave the owner available.

[Step-by-step course guide](../course-guides/rust-keyword-reference.md) · [Full course](../../courses/rust-keyword-reference/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/rust-keyword-reference.md)
