<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-react.md

PURPOSE:
Give learners an additional practical case for Learning React.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read an updated value from props

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice component copies the initial heading North room into local state. Its parent later supplies South room.

1. Trace the component’s render with both prop values. Find which value the heading is actually reading.
2. Render the current heading prop in the scratch component. Repeat the two renders while keeping the component mounted.

**Check your result.** The stale copy displays North room twice. Reading the current prop displays North room and then South room.

[Step-by-step course guide](../course-guides/learning-react.md) · [Full course](../../courses/learning-react/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-react.md)
