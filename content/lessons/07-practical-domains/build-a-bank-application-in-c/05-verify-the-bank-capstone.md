<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-bank-application-in-c/05-verify-the-bank-capstone.md

PURPOSE:
Use an explicit table to separate evidence from a feature description.

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

# Verify the banking capstone and plan its next feature

[Course contents](index.md) · [Previous · Design a durable journal and statement view](04-design-a-durable-statement.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/05-verify-the-bank-capstone.html)

Use an explicit table to separate evidence from a feature description.

## Write your test rows

```text
Case       Start          Action       Expected balances   Accepted rows
first      3000,1000      #71 600      2400,1600           1
repeat     2400,1600      #71 600      2400,1600           1
collision  2400,1600      #71 650      2400,1600           1
too large  2400,1600      #72 2401     2400,1600           1
```

Use the included C23 console to compare its starter outcomes. Then choose one additional case, such as signed overflow in the destination or a full journal. Keep the original tests as evidence.

## Make your next Umicom change

Write an enhancement note for a read-only training statement in Umicom Bank. Identify the journal source, ordering key, reason for each displayed status and whether a missing row should be shown. Include the expected result for an empty journal. Apply the same known-answer test in Umicom Automated Testing.

- [Download the complete C23 training ledger](../../../labs/native/bank-transfer-workshop/bank_transfer.c)
- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)

## Continue in another course

- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)
- [Umicom development workflow](../../../umicom/development-path.md)

[Course contents](index.md) · [Previous · Design a durable journal and statement view](04-design-a-durable-statement.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/05-verify-the-bank-capstone.html)
