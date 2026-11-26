<!--
Umicom Bits2Banking
File: content/simple-steps/apply/introduction-to-version-control.md

PURPOSE:
Give learners an additional practical case for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make a local review trail for one file

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice repository already tracks instructions.md. A change updates the first setup instruction while leaving the rest of the file alone.

1. Use git diff -- instructions.md to locate the single edit and git log -1 -- instructions.md to find the previous recorded revision.
2. Write a review note with the file name, previous commit ID, and the instruction being changed.

**Check your result.** The review note points to one tracked file and one changed instruction, and includes the previous commit ID.

[Step-by-step course guide](../course-guides/introduction-to-version-control.md) · [Full course](../../courses/introduction-to-version-control/index.html) · [Small projects by course](index.md) · [First practice case](../practice/introduction-to-version-control.md)
