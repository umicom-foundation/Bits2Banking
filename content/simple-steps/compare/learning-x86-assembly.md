<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-x86-assembly.md

PURPOSE:
Give learners an additional practical case for Learning x86 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare repeating a constant with including fixture bytes

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch NASM header needs three identical padding bytes and a separate three-byte stamp supplied by a local fixture.

1. Use the repetition lesson to trace three copies of byte 0x20. Then use the include lesson to trace a fixture with bytes 0x11, 0x22, and 0x33.
2. Read the predicted output sequences in order. Note which sequence depends on the external fixture content even though the lengths match.

**Check your result.** Repetition emits 20 20 20. Including the fixture emits 11 22 33 in hexadecimal. Both sequences contain three bytes.

[Step-by-step course guide](../course-guides/learning-x86-assembly.md) · [Full course](../../courses/learning-x86-assembly/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-x86-assembly.md)
