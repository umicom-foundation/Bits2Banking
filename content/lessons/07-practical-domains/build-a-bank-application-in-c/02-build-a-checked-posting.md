<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-bank-application-in-c/02-build-a-checked-posting.md

PURPOSE:
Check both resulting balances and the journal capacity before committing a change in memory.

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

# Build one checked posting

[Course contents](index.md) · [Previous · Write the smallest ledger contract](01-write-the-smallest-ledger-contract.md) · [Next · Compare a retry with a changed request](03-compare-a-retry-and-a-conflict.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/02-build-a-checked-posting.html)

Check both resulting balances and the journal capacity before committing a change in memory.

## Protect both sides

A caller gives the ledger and a transfer. Look up the two balances only after validating the account indexes. Require positive cents. Check that the source can cover the amount and that the target addition fits before changing either balance.

```text
VALIDATE both account indexes, distinct accounts, reference and positive cents
CHECK available source cents and representable destination cents
CHECK that a new journal row fits
WRITE both resulting balances and the accepted journal row
```

- [Download the complete C23 training ledger](../../../labs/native/bank-transfer-workshop/bank_transfer.c)

In the linked file, locate the `post` helper. With a C compiler that supports C23, open a terminal in a learning copy and use `gcc -std=c23 -Wall -Wextra -Wpedantic bank_transfer.c -o bank_transfer`. Compile the single file without other project inputs.

## Expected console result

```text
Balances: 2400, 1600 cents
Accepted transfers: 1
```

Run the generated program in your own configured practice environment. In Windows PowerShell with GCC, use `-o bank_transfer.exe` and then `./bank_transfer.exe`. If your compiler reports a missing file, confirm that the downloaded source is in the current folder.

## Exercise

Before running anything, predict whether 3,001 cents would be accepted from the initial 3,000. The source is short by one cent. A refused request keeps both balances and the journal size intact.

## Continue in another course

- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)
- [Umicom development workflow](../../../umicom/development-path.md)

[Course contents](index.md) · [Previous · Write the smallest ledger contract](01-write-the-smallest-ledger-contract.md) · [Next · Compare a retry with a changed request](03-compare-a-retry-and-a-conflict.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/02-build-a-checked-posting.html)
