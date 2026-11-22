<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/banking-technology-foundations/03-reconcile-with-stable-identities.md

PURPOSE:
Use a small comparison to find matches, missing rows and disagreements.

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

# Reconcile amounts by reference and currency

[Course contents](index.md) · [Previous · Follow an instruction from entry to settlement](02-follow-a-payment-through-systems.md) · [Next · Keep a payment retry from changing the balance twice](04-explain-retries-at-machine-level.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/03-reconcile-with-stable-identities.html)

Use a small comparison to find matches, missing rows and disagreements.

## Compare two records

Reconciliation means checking two independent sets of records and explaining their differences. Use the reference and currency as the identity in this example. Two equal amounts can describe different payments.

```text
Local P71 USD 600   Statement P71 USD 600   Match
Local P72 USD 600   No corresponding row   Missing
Local P73 USD 300   Statement P73 USD 350   Amount mismatch
```

## Read the C rule

```c
#include <stdbool.h>
#include <stdint.h>

bool amounts_equal(int64_t local_cents, int64_t reported_cents)
{
    return local_cents == reported_cents;
}
```

Call the arithmetic rule only after finding the same reference and currency in both records. An absent row never appears as zero. A row with zero can be real.

## Practise

Add local and reported P74 equal to zero. It is a fourth, matching row. Then remove the reported P74 row. The new result is missing. Use these two cases in a Umicom Bank statement comparison exercise.

- [Framework and finance](../../../courses/framework-and-finance/index.html)
- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)

## Continue in another course

- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)

[Course contents](index.md) · [Previous · Follow an instruction from entry to settlement](02-follow-a-payment-through-systems.md) · [Next · Keep a payment retry from changing the balance twice](04-explain-retries-at-machine-level.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/03-reconcile-with-stable-identities.html)
