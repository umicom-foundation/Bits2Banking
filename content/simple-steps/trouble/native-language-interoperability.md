<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/native-language-interoperability.md

PURPOSE:
Give learners an additional practical case for Native languages working together through C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find who owns a returned value

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A demonstration caller uses a result even though its C bridge returned a refusal status.

1. Open the shared function declaration and the caller’s return check. Mark where the output is first treated as valid.
2. Repeat with the lesson’s allowed value and compare when each result is read.

**Check your result.** Only the accepted call supplies a new result. The refused call stays in its own status branch.

[Step-by-step course guide](../course-guides/native-language-interoperability.md) · [Full course](../../courses/native-language-interoperability/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/native-language-interoperability.md)
