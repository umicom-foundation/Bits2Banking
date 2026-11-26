<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-gtk4.md

PURPOSE:
Give learners an additional practical case for Learning GTK4.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a preview control after a caption edit

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch GTK preview has a button identified as venue-apply. Its caption changes from Apply to Confirm.

1. Use the control discovery lesson to keep the stable identifier in the window’s logical tree and change only the visible caption.
2. Look up venue-apply in the correct window scope before and after the caption change. Check the lookup status before reading the returned control.

**Check your result.** Both lookups succeed for the same control. Its visible caption changes to Confirm.

[Step-by-step course guide](../course-guides/learning-gtk4.md) · [Full course](../../courses/learning-gtk4/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-gtk4.md)
