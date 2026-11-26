<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-iphone-development.md

PURPOSE:
Give learners an additional practical case for Learning iPhone Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Prepare the exact bytes for a Swift adapter

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional editing screen sends the precomposed Swift text Café to a C interface that takes a pointer and a byte count.

1. Write down the byte count from the UTF-8 span lesson. Mark the scope that temporarily lends the bytes to the C call.
2. Add a follow-up step that stores the owned result rather than storing the borrowed pointer. Draw what survives the scope.

**Check your result.** The adapter supplies five bytes. The result may remain in screen state while the temporary pointer ends at the call boundary.

[Step-by-step course guide](../course-guides/learning-iphone-development.md) · [Full course](../../courses/learning-iphone-development/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-iphone-development.md)
