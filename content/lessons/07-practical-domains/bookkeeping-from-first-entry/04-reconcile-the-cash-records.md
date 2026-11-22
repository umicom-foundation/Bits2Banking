<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/bookkeeping-from-first-entry/04-reconcile-the-cash-records.md

PURPOSE:
Compare two dated cash records and distinguish timing differences from entries that need review.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Reconcile the cash book with a statement

[Course contents](index.md) · [Previous lesson — Prepare a trial balance and find its limits](03-trial-balance-and-error-checks.md) · [Next course — Pricing Financial Instruments from Cash Flows](../pricing-from-cashflows/index.md)

## What you will learn

Compare two dated cash records and distinguish timing differences from entries that need review.

## Compare the same amount on the same date

**Reconciliation** explains differences between two records that should agree once their timing and scope agree. A **statement** is the bank's record for a period. The workshop’s **cash book** is its own record. A payment or receipt may reach the two records on different days.

## Work it through

At month end, the workshop ledger shows 10000 cents. The bank statement shows 9750 cents. The workshop already recorded a 400-cent deposit that is still in transit to the bank. A 150-cent service fee appears on the statement but has yet to be recorded by the workshop.

1. Compare dates, then match both sets of rows using references and amounts. Put unmatched items in separate groups.
2. Add the verified 400-cent deposit in transit to the statement balance for comparison: 9750 + 400 = 10150 cents.
3. Subtract the verified 150-cent bank fee from the workshop ledger for comparison: 10000 − 150 = 9850 cents.
4. The difference is 300 cents. The unmatched-item list is incomplete. Continue matching and confirm the evidence before changing a balance.
5. A second review finds a valid 300-cent payment already in the workshop ledger that will clear at the bank next month. Subtract it from the statement side: 10150 − 300 = 9850 cents. The adjusted sides now agree.

## Try it and check

Which item requires a new journal entry in the workshop’s records, and which two appear only as differences to track until they clear?

**Check:** After review, record the service fee as an expense debit and a cash credit. Keep the deposit in transit and the outstanding payment on the reconciliation list. Those two transactions already appear in the cash book. If you record another copy, your cash book changes even though the original evidence describes one event.

## Apply it to an Umicom project

Extend the synthetic Umicom Bank exercise into a reconciliation report. Use distinct states such as matched, timing difference and needs review. Link each item back to its source row and retain the prior reported balance separately from the reviewed changes. The [SQL reconciliation course](../../../courses/sql-statement-reconciliation/index.html) gives database practice with similar ideas.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/bookkeeping-from-first-entry/lessons/04-reconcile-the-cash-records.html)

[Course contents](index.md) · [Previous lesson — Prepare a trial balance and find its limits](03-trial-balance-and-error-checks.md) · [Next course — Pricing Financial Instruments from Cash Flows](../pricing-from-cashflows/index.md)
