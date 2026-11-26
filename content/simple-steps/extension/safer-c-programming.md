<!--
Umicom Bits2Banking
File: content/simple-steps/extension/safer-c-programming.md

PURPOSE:
Give learners an additional practical case for Safer C Programming.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a counted output without relying on padding

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice buffer uses eight bytes. The output needs five bytes including its terminator.

1. Write the required byte count and compare it to capacities 4, 5 and 8. Use the course’s bounded-write pattern.
2. Keep the previous buffer in a separate record and trace which cases are allowed to replace it.

**Check your result.** Capacity 4 refuses. Capacities 5 and 8 fit. Refusal leaves the previous buffer available for the exercise.

[Step-by-step course guide](../course-guides/safer-c-programming.md) · [Full course](../../courses/safer-c-programming/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/safer-c-programming.md)
