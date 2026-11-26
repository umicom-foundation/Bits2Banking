<!--
Umicom Bits2Banking
File: content/simple-steps/extension/build-a-bank-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Banking Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refuse a credit that would exceed its range

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice ledger has 100 cents in account 0 and INT64_MAX - 3 cents in account 1. An empty journal receives a request to move 4 cents from 0 to 1.

1. Find the target-range guard in bank_transfer.c. Compare INT64_MAX - 3 with the guard's upper bound for a 4-cent transfer.
2. Trace the return status and all three pieces of state before any addition is performed.

**Check your result.** The guard returns TRANSFER_INVALID. The balances remain 100 and INT64_MAX - 3 cents and the journal stays empty.

[Step-by-step course guide](../course-guides/build-a-bank-application-in-c.md) · [Full course](../../courses/build-a-bank-application-in-c/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/build-a-bank-application-in-c.md)
