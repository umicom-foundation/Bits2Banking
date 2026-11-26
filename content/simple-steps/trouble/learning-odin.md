<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-odin.md

PURPOSE:
Give learners an additional practical case for Learning Odin.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read the result only after success

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A caller prints output value 77 after the practice C function refuses an argument and leaves the output slot unchanged.

1. Read the binding’s status and the output slot as two separate values. Mark which one the course uses to decide whether the call succeeded.
2. Trace the refused call with the output slot set to 77. Branch on the status before reading any successful result.

**Check your result.** The call reports refusal and leaves 77 in caller storage. The display shows the refusal without displaying 77 as a new result.

[Step-by-step course guide](../course-guides/learning-odin.md) · [Full course](../../courses/learning-odin/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-odin.md)
