<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-codeigniter.md

PURPOSE:
Give learners an additional practical case for Learning CodeIgniter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that a local list also handles no rows

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A view fixture for /supplies displays No supplies listed when its controller supplies an empty list. Another fixture supplies Paper filters and Spare cup.

1. Load the empty fixture through the course controller and check the message and list item count.
2. Load the populated fixture and check both its item labels and whether the empty message is shown.

**Check your result.** The empty view shows No supplies listed and has zero items. The populated view shows two supplies and no empty message.

[Step-by-step course guide](../course-guides/learning-codeigniter.md) · [Full course](../../courses/learning-codeigniter/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-codeigniter.md)
