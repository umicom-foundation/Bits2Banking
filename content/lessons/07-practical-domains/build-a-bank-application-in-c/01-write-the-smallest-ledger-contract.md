<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-bank-application-in-c/01-write-the-smallest-ledger-contract.md

PURPOSE:
Define the two balances and the exact inputs that a posting will accept.

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

# Write the smallest ledger contract

[Course contents](index.md) · [Next · Build one checked posting](02-build-a-checked-posting.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/01-write-the-smallest-ledger-contract.html)

Define the two balances and the exact inputs that a posting will accept.

## Choose an exact unit

Use whole cents, stored as signed 64-bit integers. Account 0 starts with 3,000 cents and account 1 starts with 1,000. The transfer reference identifies the request; it does not describe a position in the journal.

```c
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint64_t id;
    size_t from;
    size_t to;
    int64_t cents;
} Transfer;
```

## Draw the accepted result

For reference 71, move 600 from account 0 to account 1. One balance decreases by 600 and the other increases by 600. The total remains 4,000. A journal is a record of accepted changes. Add the reference and fields to it together with a successful update.

## Practice checks

- Reference zero, a negative amount and a self-transfer are refused.
- A success produces 2,400 and 1,600 cents.
- The private practice ledger has one currency and two accounts.

Use these requirements to make a small Studio IDE project with a console entry and data owned by one C module.

## Continue in another course

- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)
- [Umicom development workflow](../../../umicom/development-path.md)

[Course contents](index.md) · [Next · Build one checked posting](02-build-a-checked-posting.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/01-write-the-smallest-ledger-contract.html)
