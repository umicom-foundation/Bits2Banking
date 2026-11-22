<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/bookkeeping-from-first-entry/02-double-entry-journal-and-ledger.md

PURPOSE:
Post one debit and one credit to a journal, then summarise the movements in a ledger.

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

# Record both sides of a transaction

[Course contents](index.md) · [Previous lesson — Trace a receipt into accounts](01-receipts-and-accounts.md) · [Next lesson — Prepare a trial balance and find its limits](03-trial-balance-and-error-checks.md)

## What you will learn

Post one debit and one credit to a journal, then summarise the movements in a ledger.

## Use left and right consistently

A **journal** stores transactions in the order they happened. A **ledger** groups the posted effects by account. A **debit** is the left side of an account and a **credit** is the right side. The account type tells you what an increase looks like. In this lesson an asset such as Cash increases with a debit. Capital and Loan Payable increase with a credit.

A transaction can affect several accounts. The total debits must equal the total credits within that transaction. Our three training transactions each have two lines.

## Work it through

| Reference | Account to debit | Debit in cents | Account to credit | Credit in cents |
| --- | --- | ---: | --- | ---: |
| C-01 | Cash | 10000 | Owner Capital | 10000 |
| E-01 | Equipment | 2500 | Cash | 2500 |
| L-01 | Cash | 3000 | Loan Payable | 3000 |

1. Read the first row left to right. Cash increases on the debit side. Owner Capital increases on the credit side. Both entries record the same event.
2. Find each Cash row in the ledger. Cash debits are 10000 + 3000 = 13000 cents. Its credit is 2500 cents. The Cash debit balance is 10500 cents.
3. Inventory the other balances. Equipment has a 2500-cent debit balance, Owner Capital has a 10000-cent credit balance, and Loan Payable has a 3000-cent credit balance.
4. Keep both lines under the same reference when you design a source record. A reader should be able to view the two sides together.

## Try it and check

The workshop returns 500 cents of the borrowed money. Write the debit and credit and find the new Cash and Loan Payable balances.

**Check:** Debit Loan Payable by 500 cents to reduce the liability. Credit Cash by 500 cents to reduce the asset. The new Cash balance is 10000 cents debit and Loan Payable is 2500 cents credit. If borrowing and repayment have the same account directions on your sheet, compare the direction of cash first.

## Apply it to an Umicom project

For a proposed Bank journal-import exercise, keep each transaction ID and signed side distinct. A review should reject an unequal pair before any practice row is accepted. Begin with a fixture that includes a valid entry and one missing credit line.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/bookkeeping-from-first-entry/lessons/02-double-entry-journal-and-ledger.html)

[Course contents](index.md) · [Previous lesson — Trace a receipt into accounts](01-receipts-and-accounts.md) · [Next lesson — Prepare a trial balance and find its limits](03-trial-balance-and-error-checks.md)
