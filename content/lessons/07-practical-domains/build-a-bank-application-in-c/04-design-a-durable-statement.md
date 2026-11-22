<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-bank-application-in-c/04-design-a-durable-statement.md

PURPOSE:
Put database changes behind one transaction and build a read-only statement from accepted rows.

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

# Design a durable journal and statement view

[Course contents](index.md) · [Previous · Compare a retry with a changed request](03-compare-a-retry-and-a-conflict.md) · [Next · Verify the banking capstone and plan its next feature](05-verify-the-bank-capstone.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/04-design-a-durable-statement.html)

Put database changes behind one transaction and build a read-only statement from accepted rows.

## Decide what must survive

The current program keeps its synthetic journal in memory. A transaction is a group of database changes treated as one unit. For a durable practice adapter, place both balance changes and the journal insertion in one write transaction, using a unique reference and bound parameters. A bound parameter supplies a value without joining it into the SQL command text.

```text
BEGIN IMMEDIATE on the SQLite practice file
LOOK UP reference and compare the normalized request
WRITE debit, credit and accepted row if all checks pass
COMMIT once; handle failure and regain known state
READ ordered accepted rows into the statement view
```

Define how busy and failed commits are handled and check the transaction’s actual state before retrying. The SQLite transaction reference explains these return cases. Use an empty learning database and locally invented rows.

## Trace a partial failure

Suppose the journal-insert step fails after the first database update. Roll back the transaction and read the old account rows. If a later restart finds reference 71 already committed, load its stored result and avoid another movement.

- [SQLite transaction control](https://www.sqlite.org/lang_transaction.html)
- [SQLite atomic commit](https://www.sqlite.org/atomiccommit.html)
- [Native statement calculations](../../../courses/native-statement-calculations/index.html)

For product integration, inspect the existing Framework statement, reconciliation and Bank workspace exercises. Keep validation and persistence in reusable services and leave the window as a client. These learning files use no real accounts.

## Continue in another course

- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)
- [Umicom development workflow](../../../umicom/development-path.md)

[Course contents](index.md) · [Previous · Compare a retry with a changed request](03-compare-a-retry-and-a-conflict.md) · [Next · Verify the banking capstone and plan its next feature](05-verify-the-bank-capstone.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/04-design-a-durable-statement.html)
