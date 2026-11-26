<!--
Umicom Bits2Banking
File: content/simple-steps/compare/building-linux-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Linux from Scratch Using C Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare the running root with the build sysroot

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The existing development VM builds a utility for a separate teaching guest. A draft diagram shows a guest configuration file inside the compiler's sysroot with no copy available to the running guest.

1. Draw the two directory views used during compilation and during guest runtime.
2. Place target headers, linker inputs and the practice configuration file in the view that needs them.

**Check your result.** Headers and linker inputs belong in the target build view. The installed configuration must be accessible in the guest's running root filesystem.

[Step-by-step course guide](../course-guides/building-linux-from-scratch.md) · [Full course](../../courses/building-linux-from-scratch/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/building-linux-from-scratch.md)
