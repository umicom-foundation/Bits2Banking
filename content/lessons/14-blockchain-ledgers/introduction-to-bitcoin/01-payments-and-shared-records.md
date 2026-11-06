# Payments and shared records

[Course contents](index.md) · [Next: Hashes, signatures and ownership](02-hashes-signatures-and-ownership.md)

## What are we trying to record?

Begin with a list of payments, not a price chart. Imagine a digital record that says one participant can spend 12 units. Copying the file does not create another legitimate 12 units. The hard question is how independent computers agree that those same units have not already been spent elsewhere.

A node is a program participating in a network. A ledger is a record of accepted changes. A transaction proposes a change. In Bitcoin, transactions consume previous outputs and create new outputs. An output is an amount with a spending condition. It is not a bank account row.

```text
previous output: 12 units
           |
           v
transaction: consume that output once
           |
           +--> recipient output: 7
           +--> change output:    4
           +--> difference:       1 fee
```

The numbers are fictional teaching units. Bitcoin amounts are commonly expressed in satoshis, with 100,000,000 satoshis per bitcoin. Use whole-number units for transaction accounting rather than rounding binary floating-point values.

## Follow a payment on paper

1. Give the previous output a label, such as output-A.
2. Cross it off the unspent list when the transaction is accepted.
3. Add the new outputs to that list.
4. Try a second transaction spending output-A. It conflicts with the first because the output has already been consumed.

A wallet helps manage keys, construct payments and display relevant history. A node validates rules and exchanges data. They can be combined in one software product, but they have different responsibilities. Downloading wallet software does not establish that a payment has been accepted.

## Exercise

A previous output contains 20 units. A transaction creates 11 units for one recipient and 8 units of change. What is the fee? Could a transaction create 21 units from the same input under ordinary spending rules?

## Explained answer

20 - 11 - 8 = 1. Creating 21 from 20 would create an unsupported extra unit. Bitcoin also has special coinbase transactions governed by separate issuance rules; they are not permission for ordinary payments to create value.

## Source connection

Framework's SHA-256 header exposes a hashing primitive. Hashes help identify data, but hashing a payment does not prove ownership or decide whether it may be spent. Keep these separate as the course introduces signatures and consensus.

## Continue learning

[Course contents](index.md) · [Next: Hashes, signatures and ownership](02-hashes-signatures-and-ownership.md)

[Browser edition](../../../courses/introduction-to-bitcoin/lessons/01-payments-and-shared-records.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://bitcoin.org/bitcoin.pdf).
