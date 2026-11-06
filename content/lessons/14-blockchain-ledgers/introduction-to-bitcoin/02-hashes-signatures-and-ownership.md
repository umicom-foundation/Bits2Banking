# Hashes, signatures and ownership

[Course contents](index.md) · [Previous: Payments and shared records](01-payments-and-shared-records.md) · [Next: Confirmations and a reading path](03-confirmations-and-a-reading-path.md)

## Three different questions

The previous lesson described amounts and outputs. Now ask: did the bytes change, was the required spending authorisation supplied, and is the spend still available? These are different checks.

A hash is a fixed-size digest calculated from bytes. The same bytes under the same algorithm produce the same digest. A hash is not encryption: there is no decryption key that recovers the message. A digital signature uses a private key to authorise a message and can be checked with a corresponding public key. A signature check is not a check that the payment has sufficient funds.

```text
data integrity        authorisation        ledger state
hash the bytes        check signature      input is unspent
      \                    |                    /
       \-------------------+-------------------/
                   all relevant rules
```

## Why bytes matter

The text 12 and the text 012 look like the same number to a person. They are different byte sequences. Before independent computers can hash or sign a record consistently, they need an exact encoding: field order, integer sizes, byte order and rules for omitted fields. This encoding is called serialization.

Use a simple paper exercise: write payment, recipient and amount on separate lines. Reorder the lines. The meaning might look similar, but the stored bytes changed. This is why later implementation lessons define an encoding instead of hashing an in-memory C structure, which can include padding bytes.

Never put a real private key or wallet recovery phrase into a lesson, screenshot or bug report. For reading exercises, labels such as key-A are enough. When practical wallet exercises arrive, use an isolated practice network and disposable keys.

## Exercise

A node receives a correctly signed transaction that spends an output already consumed by an earlier accepted transaction. Should it accept it? Does computing a SHA-256 digest change the answer?

## Explained answer

No. The signature may establish authorisation by the required key, but the output is unavailable. Hashing gives the transaction an identity; it does not change ledger state. In Umicom, reuse cryptographic primitives through Framework while keeping transaction rules explicit. An application must not label an item verified merely because a digest was calculated.

## Continue learning

[Course contents](index.md) · [Previous: Payments and shared records](01-payments-and-shared-records.md) · [Next: Confirmations and a reading path](03-confirmations-and-a-reading-path.md)

[Browser edition](../../../courses/introduction-to-bitcoin/lessons/02-hashes-signatures-and-ownership.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://bitcoin.org/bitcoin.pdf).
