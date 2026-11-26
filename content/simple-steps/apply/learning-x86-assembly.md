<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-x86-assembly.md

PURPOSE:
Give learners an additional practical case for Learning x86 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Describe a byte fixture and its reserved space

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local NASM lab needs three initialized stamp bytes 0x11, 0x22, and 0x33 and an independent four-byte scratch area.

1. Use the initialized-data lesson to describe the stamp bytes in order. Reserve the scratch area using the uninitialized storage lesson.
2. Make a small object inspection record with the stamp byte order and the reserved size in separate entries.

**Check your result.** The initialized stamp is 11 22 33 in hexadecimal, and the separate scratch size is four bytes.

[Step-by-step course guide](../course-guides/learning-x86-assembly.md) · [Full course](../../courses/learning-x86-assembly/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-x86-assembly.md)
