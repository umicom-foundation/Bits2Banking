<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/build-a-bank-application-in-c.md

PURPOSE:
Give learners an additional practical case for Build a Banking Application in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refuse a transfer to its own account

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local proposed transfer sends 200 cents from account index 0 to account index 0. The opening balances are 3,000 and 1,000 cents.

1. Find the distinct-account check in Build one checked posting. Use the source and destination indexes to trace it on paper.
2. Record the balances and journal size after the refusal, starting with an empty journal.

**Check your result.** The transfer is refused at the account checks. The balances remain 3,000 and 1,000 cents, and the journal stays empty.

[Step-by-step course guide](../course-guides/build-a-bank-application-in-c.md) · [Full course](../../courses/build-a-bank-application-in-c/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/build-a-bank-application-in-c.md)
