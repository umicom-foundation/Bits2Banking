<!--
Umicom Bits2Banking
File: content/simple-steps/check/framework-and-finance--data-and-messaging.md

PURPOSE:
Give learners an additional practical case for Learning Data and Messaging Services.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check rollback and completed commit from the same starting row

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toy transaction moves 70 units from A = 200 to B = 50. The first trial fails before the journal insert. The second completes both balances, the audit row and commit.

1. Trace the declared atomic transaction in Keep related changes together. Put the failure immediately before the journal step in trial one.
2. Write the expected account balances and committed audit count after each trial.

**Check your result.** The first trial rolls back to 200 and 50 with zero audit rows. The second commits 130 and 120 with one audit row.

[Step-by-step course guide](../course-guides/framework-and-finance--data-and-messaging.md) · [Full course](../../courses/framework-and-finance/data-and-messaging/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/framework-and-finance--data-and-messaging.md)
