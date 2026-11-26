<!--
Umicom Bits2Banking
File: content/simple-steps/apply/build-a-bank-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Banking Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Draft a statement from accepted journal rows

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toy ledger starts with 600 and 400 cents. Transfer 51 moves 100 from account 0 to 1, its identical repeat arrives, and transfer 52 moves 40 back independently.

1. Trace each call in order and write an accepted journal row only when the native rule applies a transfer.
2. Create a read-only statement for account 0 from the two accepted rows. Include their order, direction and balance after each.

**Check your result.** The statement contains 51 for -100, then 52 for +40. Account 0 finishes with 540 cents and account 1 with 460 cents.

[Step-by-step course guide](../course-guides/build-a-bank-application-in-c.md) · [Full course](../../courses/build-a-bank-application-in-c/index.html) · [Small projects by course](index.md) · [First practice case](../practice/build-a-bank-application-in-c.md)
