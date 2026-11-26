<!--
Umicom Bits2Banking
File: content/simple-steps/check/java-keyword-reference.md

PURPOSE:
Give learners an additional practical case for Java SE 25 keyword reference.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check access through a method and direct field access

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A Java exercise has a top-level Stock class with private integer field remaining, set to 4, and a public getter. A separate top-level reader uses it.

1. Build the reader fixture that calls the getter and print its result.
2. In a separate scratch copy, try direct access to the private field from the reader and check the compiler result.

**Check your result.** The getter version prints 4. The direct-access fixture is rejected for accessing a private member.

[Step-by-step course guide](../course-guides/java-keyword-reference.md) · [Full course](../../courses/java-keyword-reference/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/java-keyword-reference.md)
