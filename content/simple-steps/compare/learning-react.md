<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-react.md

PURPOSE:
Give learners an additional practical case for Learning React.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare stored state with an ordinary local variable

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice component begins with count 2. One version holds count in view state and the other declares a fresh local value of 2 each render.

1. In the first trace, use the state setter to change the count to 3 and follow the next render.
2. In the second trace, mutate the local variable and draw a parent-triggered render that creates it again.

**Check your result.** The state-backed version renders 3. The ordinary local version initializes count to 2 on the next render.

[Step-by-step course guide](../course-guides/learning-react.md) · [Full course](../../courses/learning-react/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-react.md)
