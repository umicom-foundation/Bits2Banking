<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-wt.md

PURPOSE:
Give learners an additional practical case for Learning Wt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a resource request with a widget event

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local Wt trace shows a stylesheet request and a form submission that runs a name check.

1. Use the transport and event lesson to follow the stylesheet through resource handling. Record whether it calls the form’s validation code.
2. Follow the form submission from the session widget to the C check. Compare the number of validation calls made by the two paths.

**Check your result.** The stylesheet request makes zero validator calls. The form submission makes one.

[Step-by-step course guide](../course-guides/learning-wt.md) · [Full course](../../courses/learning-wt/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-wt.md)
