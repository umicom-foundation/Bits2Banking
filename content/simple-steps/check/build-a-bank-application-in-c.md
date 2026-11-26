<!--
Umicom Bits2Banking
File: content/simple-steps/check/build-a-bank-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Banking Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a transfer with and without available journal space

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two independent teaching ledgers each start with balances of 100 and 70 cents. One has seven prior accepted rows and the other has eight. Both receive a fresh reference that moves 20 cents from 0 to 1.

1. Check the workshop's capacity of eight. Confirm the new ID differs from every prior row and trace the account checks.
2. Record the status, resulting balances and final journal count for both cases.

**Check your result.** The seven-row book returns TRANSFER_APPLIED, with balances 80 and 90 and eight rows. The eight-row book returns TRANSFER_FULL, with balances 100 and 70 and eight rows.

[Step-by-step course guide](../course-guides/build-a-bank-application-in-c.md) · [Full course](../../courses/build-a-bank-application-in-c/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/build-a-bank-application-in-c.md)
