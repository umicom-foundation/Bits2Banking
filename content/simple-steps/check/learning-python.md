<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-python.md

PURPOSE:
Give learners an additional practical case for Learning Python.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a bounded read before decoding

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch note reader allows at most 16 bytes. Its ten-byte JSON text is [{"id":1}] with no line ending.

1. Make two fixtures from the given text, one with six trailing ASCII spaces and the other with seven. Use a bounded read that can detect the extra byte.
2. Trace both lengths to the decoder without publishing the decoded records. Count decoder calls for each input.

**Check your result.** The 16-byte fixture reaches decoding once. The 17-byte fixture is refused before decoding and makes zero decoder calls.

[Step-by-step course guide](../course-guides/learning-python.md) · [Full course](../../courses/learning-python/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-python.md)
