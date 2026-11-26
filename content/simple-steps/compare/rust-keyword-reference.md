<!--
Umicom Bits2Banking
File: content/simple-steps/compare/rust-keyword-reference.md

PURPOSE:
Give learners an additional practical case for Rust 2024 Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a shared read with an updating borrow

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice value begins at 4. A shared read observes it, then a separately scoped updating borrow adds 1.

1. Identify the read’s scope and the scope permitted to update. Record the value after each.
2. Compare the ownership rules used by both operations using the course examples.

**Check your result.** The read observes 4. The separate allowed update changes the value to 5.

[Step-by-step course guide](../course-guides/rust-keyword-reference.md) · [Full course](../../courses/rust-keyword-reference/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/rust-keyword-reference.md)
