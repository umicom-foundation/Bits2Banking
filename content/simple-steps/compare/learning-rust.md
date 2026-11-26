<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-rust.md

PURPOSE:
Give learners an additional practical case for Learning Rust.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare copying a C-compatible value with borrowing text

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch Rust adapter sends a small signed C int of 7 and separately passes a view of a local label to a synchronous call.

1. Use the language boundary lesson to distinguish the copied number from the borrowed text storage. Mark the caller’s ownership in both paths.
2. End the local label’s scope on the diagram and compare which kinds of returned value can be used at that point.

**Check your result.** A copied numeric result can still be used. A retained borrow into the ended label storage cannot.

[Step-by-step course guide](../course-guides/learning-rust.md) · [Full course](../../courses/learning-rust/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-rust.md)
