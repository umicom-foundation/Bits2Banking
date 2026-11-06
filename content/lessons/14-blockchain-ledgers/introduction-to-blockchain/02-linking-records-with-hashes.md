# Linking records with hashes

[Course contents](index.md) · [Previous: A ledger and a state](01-a-ledger-and-a-state.md) · [Next: Agreement is more than counting](03-agreement-is-more-than-counting.md)

## A link that depends on content

In an ordinary list, each item can refer to the previous item's number. In a hash-linked list, each record includes the digest of previous content. Altering old content changes its digest and breaks the next recorded link, unless an attacker can replace the later history too.

```text
record A bytes -> hash A
record B includes hash A -> hash B
record C includes hash B -> hash C
```

This is tamper evidence relative to a trusted reference, not magical immutability. If one person can rewrite every file and every reference digest, a local chain alone cannot prove which history was originally accepted. External checkpoints, permissions, signatures and distributed agreement address different parts of that threat model.

## Define the exact bytes

Suppose a record has a sequence number and amount. Decide the integer width, signedness and byte order. Signedness tells whether negative values are allowed. Byte order says which byte of a multi-byte number comes first. Hashing raw C structure memory is unsuitable: compilers can insert padding between fields, and machines can store integer bytes differently.

Read Framework's SHA-256 header. The update operation takes a pointer plus a byte count. That count makes the boundary explicit. Do not use strlen for arbitrary binary records; a zero byte inside a record is valid data and would make a string-length calculation stop early.

## Exercise

Two writers encode the amount 1 as the text 1 and as four bytes 01 00 00 00. Should you expect their digests to match? If not, what must the design specify?

## Explained answer

No. A human can interpret both as the same value, but hashing operates on exact bytes. Specify one encoding and validate it at every boundary. Text may be a legitimate format if its grammar is exact; binary may be legitimate if widths and ordering are exact. Neither is automatically safe without rules.

## Continue

The construction course begins with an original small record format and invalid-input checks. The existing blockchain-ledgers library provides deeper work on Merkle proofs and append-only histories after these foundations.

## Continue learning

[Course contents](index.md) · [Previous: A ledger and a state](01-a-ledger-and-a-state.md) · [Next: Agreement is more than counting](03-agreement-is-more-than-counting.md)

[Browser edition](../../../courses/introduction-to-blockchain/lessons/02-linking-records-with-hashes.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.
