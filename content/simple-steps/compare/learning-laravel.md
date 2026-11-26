<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-laravel.md

PURPOSE:
Give learners an additional practical case for Learning Laravel.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a direct response and an escaped view

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local demo returns text Plain rooms directly on one route. An alternate route sends the value `Room <West>` into a Blade expression inside an HTML paragraph.

1. Use the route lesson to trace the first value straight into its response. In the view lesson trace the second value into the template slot.
2. Inspect the two response forms in a paper trace or local copy. Identify whether a template and an escaped value appear.

**Check your result.** The first body is Plain rooms. The second body is an HTML paragraph with the escaped text, and the displayed text is `Room <West>`.

[Step-by-step course guide](../course-guides/learning-laravel.md) · [Full course](../../courses/learning-laravel/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-laravel.md)
