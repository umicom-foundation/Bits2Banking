<!--
Umicom Bits2Banking
File: content/simple-steps/practice/safer-c-programming.md

PURPOSE:
Give learners an additional practical case for Safer C Programming.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the terminator before storing text

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice buffer has six bytes and must end with a zero byte.

1. Count the space occupied by the string `venue` and its terminator. Trace whether it fits.
2. Try `venues` in a separate copy of the input. Identify the failure point before overwriting any accepted data.

**Check your result.** `venue` fits in six bytes including its terminator. `venues` needs seven bytes and is refused.

[Step-by-step course guide](../course-guides/safer-c-programming.md) · [Full course](../../courses/safer-c-programming/index.html) · [Practice by course](index.md)
