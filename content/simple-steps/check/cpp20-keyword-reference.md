<!--
Umicom Bits2Banking
File: content/simple-steps/check/cpp20-keyword-reference.md

PURPOSE:
Give learners an additional practical case for C++20 Keyword and Token Reference.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a type constraint with and without a field

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A short lesson uses `HasCents<T>` to ask whether item.cents is a valid expression. The first practice type offers a public int cents member. The second offers a public int id only.

1. Use the requires-expression to substitute the two type names separately.
2. Write two static assertions that record the expected yes and no results under those declarations.

**Check your result.** HasCents is true for the type with cents and false for the type with only id. Both correctly written static assertions hold.

[Step-by-step course guide](../course-guides/cpp20-keyword-reference.md) · [Full course](../../courses/cpp20-keyword-reference/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/cpp20-keyword-reference.md)
