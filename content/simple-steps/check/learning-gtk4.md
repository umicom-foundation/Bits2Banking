<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-gtk4.md

PURPOSE:
Give learners an additional practical case for Learning GTK4.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a found control that cannot be activated

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two practice GTK controls have the stable names report-submit and report-cancel. Submit is disabled and Cancel is enabled and visible.

1. Use the found-versus-usable lesson to check lookup success for each name. Record those two results independently of activation readiness.
2. Check sensitivity and visibility before sending either action in a trace. Add one count to an action route only if it can run.

**Check your result.** Both controls are found. Submit produces no action count and visible, enabled Cancel produces one.

[Step-by-step course guide](../course-guides/learning-gtk4.md) · [Full course](../../courses/learning-gtk4/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-gtk4.md)
