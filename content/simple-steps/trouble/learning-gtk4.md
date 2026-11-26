<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-gtk4.md

PURPOSE:
Give learners an additional practical case for Learning GTK4.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a duplicated button connection

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice window calls a rule twice for one click. Its source connects the same callback to the same button in two setup functions.

1. Give the callback a counter in a practice copy. Start at zero and trace the signal from one click to both registered callbacks.
2. Choose the setup function that owns the connection. Remove the extra connection from the scratch design and trace one click again.

**Check your result.** The original trace reaches the callback twice. The corrected trace reaches it once.

[Step-by-step course guide](../course-guides/learning-gtk4.md) · [Full course](../../courses/learning-gtk4/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-gtk4.md)
