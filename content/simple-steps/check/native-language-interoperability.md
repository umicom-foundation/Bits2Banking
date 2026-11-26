<!--
Umicom Bits2Banking
File: content/simple-steps/check/native-language-interoperability.md

PURPOSE:
Give learners an additional practical case for Native languages working together through C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the same output state after two calls

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice C boundary has one allowed and one refused input. The caller initializes its result storage to a known value first.

1. Record what the output contract permits for each case. Trace the caller’s return check before accessing the value.
2. Run or trace the same cases in a secondary language binding and compare the retained output state.

**Check your result.** A successful call admits its new value. A refused call follows the documented preservation rule in both bindings.

[Step-by-step course guide](../course-guides/native-language-interoperability.md) · [Full course](../../courses/native-language-interoperability/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/native-language-interoperability.md)
