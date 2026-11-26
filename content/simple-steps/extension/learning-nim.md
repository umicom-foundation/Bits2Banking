<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-nim.md

PURPOSE:
Give learners an additional practical case for Learning Nim.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a borrowed C value inside its lifetime

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A Nim scratch function has a local cint slot set to 12 and a C function reads from a pointer during the call.

1. Use the interoperability lesson to identify the slot’s type and mark where the call borrows its address.
2. Draw the slot’s lifetime from creation to return. Check the call path has no assignment of that address to longer-lived storage.

**Check your result.** The C call reads 12 while the slot is live. The trace contains no pointer to the slot after the Nim function returns.

[Step-by-step course guide](../course-guides/learning-nim.md) · [Full course](../../courses/learning-nim/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-nim.md)
