<!--
Umicom Bits2Banking
File: content/simple-steps/compare/native-language-interoperability.md

PURPOSE:
Give learners an additional practical case for Native languages working together through C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare by-value and result-buffer contracts

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two classroom C interfaces produce the same value. One returns it directly and one writes it to provided storage upon success.

1. Draw both declarations using the lesson’s terminology. Mark where the value appears and where to check status.
2. Trace a refusal in the result-buffer example and compare which object can legally be read.

**Check your result.** The direct interface returns its described value. The output-buffer contract makes the returned status part of deciding whether a new value exists.

[Step-by-step course guide](../course-guides/native-language-interoperability.md) · [Full course](../../courses/native-language-interoperability/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/native-language-interoperability.md)
