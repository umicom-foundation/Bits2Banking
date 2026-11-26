<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-nim.md

PURPOSE:
Give learners an additional practical case for Learning Nim.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare the integer types at a C boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A Nim declaration uses plain int for a field while the companion C header declares an int. The sample’s type-size table says Nim int is 64 bits and C int is 32 bits.

1. Place the two declarations beside the C contract lesson. Identify which value crosses the interface.
2. Change only the binding for that argument to the course’s cint type. Keep native Nim values separate where the input is still being prepared.

**Check your result.** The binding entry now matches the C int position, 32 bits in the stated type-size table.

[Step-by-step course guide](../course-guides/learning-nim.md) · [Full course](../../courses/learning-nim/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-nim.md)
