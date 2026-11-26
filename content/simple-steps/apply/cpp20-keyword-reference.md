<!--
Umicom Bits2Banking
File: content/simple-steps/apply/cpp20-keyword-reference.md

PURPOSE:
Give learners an additional practical case for C++20 Keyword and Token Reference.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Create a compile-time unit note

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper expense program stores 100 cents per currency unit. Its developer wants the compiler to check that two units equal 200 cents.

1. Write the constexpr cents_per_unit declaration from the compile-time lesson. Add static_assert(2 * cents_per_unit == 200).
2. Trace the compiler check and draft a runtime output for two units using the same constant.

**Check your result.** The assertion condition is true and the runtime calculation displays 200.

[Step-by-step course guide](../course-guides/cpp20-keyword-reference.md) · [Full course](../../courses/cpp20-keyword-reference/index.html) · [Small projects by course](index.md) · [First practice case](../practice/cpp20-keyword-reference.md)
