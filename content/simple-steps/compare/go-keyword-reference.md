<!--
Umicom Bits2Banking
File: content/simple-steps/compare/go-keyword-reference.md

PURPOSE:
Give learners an additional practical case for Go Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a Go array copy with a slice of the original

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An array starts with the three values 4, 8 and 12. One variable receives the whole array by assignment and another receives a slice of the original array.

1. Change the second element of the array copy to 9 and read the second element through the slice.
2. Set the second element through the slice to 11 and read the original array and the copy.

**Check your result.** After changing the copy, the slice still reads 8. After changing through the slice, the original reads 11 and the copy still reads 9.

[Step-by-step course guide](../course-guides/go-keyword-reference.md) · [Full course](../../courses/go-keyword-reference/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/go-keyword-reference.md)
