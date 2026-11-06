# Inputs, outputs and data types

[Course contents](index.md) · [Previous: A source map and a fixed version](01-a-source-map-and-a-fixed-version.md) · [Next: Reading rejection paths](03-reading-rejection-paths.md)

## Give every symbol a plain-language meaning

Open src/primitives/transaction.h at v28.0. Find COutPoint, CTxIn and CTxOut. An outpoint identifies an earlier transaction output. An input refers to earlier output data; an output describes an amount and spending condition. Read the actual declaration before assuming every field is a simple integer.

Use this original simplified drawing, which omits real fields and is not a wire-format specification:

```text
transaction
  inputs  -> [earlier transaction identity, output position, authorisation data]
  outputs -> [amount, spending condition]
```

A collection, such as a vector, stores a sequence of items. Its position is not the same as a globally unique identifier. A reference to output position 1 means an output within a particular earlier transaction; it does not mean the second output in the entire network.

## Trace an example

1. Draw an earlier transaction T with two outputs, numbered 0 and 1.
2. Give output 0 a value of 30 and output 1 a value of 10.
3. Draw a new input referencing T, position 1.
4. Confirm that this input refers to 10, not 30 or the total 40.
5. Record that this drawing alone does not establish whether the output is unspent or authorised.

When translating an idea into C, do not flatten away ownership and bounds. Every collection needs a length; every index must be checked; every reference needs a clear lifetime. The linked Umicom hashing header demonstrates explicit byte counts and fixed digest sizes, a useful contrast with unbounded text copying.

## Exercise

A parser receives an output index of 3 for a transaction containing three outputs. Is the index valid? Why can a correct hash not repair the problem?

## Explained answer

No: positions are 0, 1 and 2. The parser or validation layer must reject the reference according to its contract. Hashing identifies the invalid bytes as readily as valid bytes; it does not make an out-of-range access safe.

## Next step

Keep the data diagram beside you when reading CheckTransaction. Distinguish checks that use only this transaction from those needing previous ledger state. Avoid treating a lesson diagram as a replacement for the upstream serialization rules.

## Continue learning

[Course contents](index.md) · [Previous: A source map and a fixed version](01-a-source-map-and-a-fixed-version.md) · [Next: Reading rejection paths](03-reading-rejection-paths.md)

[Browser edition](../../../courses/introduction-to-bitcoin-source-code/lessons/02-inputs-outputs-and-data-types.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://github.com/bitcoin/bitcoin/tree/v28.0).
