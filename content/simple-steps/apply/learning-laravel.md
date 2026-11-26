<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-laravel.md

PURPOSE:
Give learners an additional practical case for Learning Laravel.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Render a route-driven room summary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local practice page needs the heading Room summary and a count of 3 for /room-summary.

1. Use the route lesson to map GET /room-summary to a handler. Pass the heading and count as two named values to a Blade view.
2. Render each value through its own template expression and inspect the local output or trace the data map by hand.

**Check your result.** The page heading reads Room summary and the body reads 3 rooms. Both values arrive from the handler.

[Step-by-step course guide](../course-guides/learning-laravel.md) · [Full course](../../courses/learning-laravel/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-laravel.md)
