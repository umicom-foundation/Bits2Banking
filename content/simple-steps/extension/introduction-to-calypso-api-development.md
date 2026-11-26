<!--
Umicom Bits2Banking
File: content/simple-steps/extension/introduction-to-calypso-api-development.md

PURPOSE:
Give learners an additional practical case for Introduction to Calypso API Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Limit a fake query to a single selected record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local fake repository contains row A10 for Port East and B11 and C12 for Port West. A training request asks for Port West in ID order with a one-row limit.

1. Filter the fake rows by portfolio, put the matching IDs in order, and enforce the limit on that result.
2. Record the returned ID and separately record that another matching row existed in the fixture.

**Check your result.** The result contains only B11. C12 is the second matching row, outside the one-row result.

[Step-by-step course guide](../course-guides/introduction-to-calypso-api-development.md) · [Full course](../../courses/introduction-to-calypso-api-development/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/introduction-to-calypso-api-development.md)
