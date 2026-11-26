<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-rust.md

PURPOSE:
Give learners an additional practical case for Learning Rust.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Repeat a call after a refusal

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A demonstration C service reports 5 for capacity 12 and occupied count 7, and refuses an occupied count above capacity.

1. Use the independent calls lesson to trace three Rust wrapper calls with occupied counts 7, 13, and 7, keeping capacity at 12 for each call.
2. Record the result or error independently after each call and check that the middle refusal does not alter the next valid result.

**Check your result.** The first and third calls both report 5. The middle call reports refusal and supplies no seat count.

[Step-by-step course guide](../course-guides/learning-rust.md) · [Full course](../../courses/learning-rust/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-rust.md)
