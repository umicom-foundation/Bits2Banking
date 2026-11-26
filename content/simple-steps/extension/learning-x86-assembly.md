<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-x86-assembly.md

PURPOSE:
Give learners an additional practical case for Learning x86 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a symbol a caller can link to

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch NASM object exposes a routine called venue_total. It also contains a data label room_count that callers do not use directly.

1. Use the course’s object-file lesson to put the routine in the code section, declare it global, and leave the data label local.
2. Inspect the object’s public defined symbols with the symbol tool from the lesson. Check both names in that listing.

**Check your result.** venue_total appears as a public defined symbol. room_count does not appear in the public defined list.

[Step-by-step course guide](../course-guides/learning-x86-assembly.md) · [Full course](../../courses/learning-x86-assembly/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-x86-assembly.md)
