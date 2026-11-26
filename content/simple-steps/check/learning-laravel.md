<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-laravel.md

PURPOSE:
Give learners an additional practical case for Learning Laravel.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a defined route and a missing route

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local exercise registers GET /venue and contains no fallback or /veneu route.

1. Use the routing lesson to write a case that requests the exact registered path. Expect the fixture body Venue information.
2. Write a second case requesting /veneu. Compare the status and body before attributing the failure to a template.

**Check your result.** The defined path returns a successful response containing Venue information. The misspelled path returns 404 without that body.

[Step-by-step course guide](../course-guides/learning-laravel.md) · [Full course](../../courses/learning-laravel/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-laravel.md)
