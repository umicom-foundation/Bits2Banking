<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-rust.md

PURPOSE:
Give learners an additional practical case for Learning Rust.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a Rust link against two C fixtures

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch Rust declaration refers to a C function named room_limit returning a C int. One C fixture defines room_limit to return 12. The other only defines room_total.

1. Use the linking lesson to list the Rust declaration and the exported C symbol in the first fixture. Expect a matching link and check the returned value.
2. Make the same link plan while supplying the second fixture. Keep the Rust declaration fixed and compare the names.

**Check your result.** The first fixture resolves the symbol and can return 12. The second leaves room_limit unresolved and runs no call.

[Step-by-step course guide](../course-guides/learning-rust.md) · [Full course](../../courses/learning-rust/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-rust.md)
