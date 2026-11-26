<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-javascript.md

PURPOSE:
Give learners an additional practical case for Learning JavaScript.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Enable a button after a module is ready

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice screen has a button that opens a local report through a module which starts in a loading state.

1. Use the native module readiness lesson to trace a click before the module signals readiness. Keep a tally of calls sent to it.
2. Trace the readiness signal and one further click. Record both the button state and call tally at each point.

**Check your result.** The loading button is disabled and sends zero calls. After readiness the enabled button sends exactly one call.

[Step-by-step course guide](../course-guides/learning-javascript.md) · [Full course](../../courses/learning-javascript/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-javascript.md)
