# Scope, bytes and compatibility

[Course contents](index.md) · [Next: A bounded little-endian reader](02-a-bounded-little-endian-reader.md)

## Decide what building means

Bitcoin is a protocol and ecosystem, not a single hashing loop. A full validating implementation needs exact encodings, transaction and script rules, networking, storage and chain handling. We start with a header reader and byte helpers. These are educational components; they cannot send payments or participate as a complete node.

Read the Bitcoin concept and source courses, then C pointers, arrays and integer operations. Start with paper traces. Do not connect unfinished parsers to public peers or give them real wallet secrets.

The standard Bitcoin block header is 80 bytes. Its fields are version (4), previous block hash (32), Merkle root (32), time (4), compact target (4) and nonce (4). Scalar fields use little-endian encoding; hash fields have their documented internal byte ordering. Displayed hash text requires care and is not a licence to reverse every field blindly.

```text
offset 0     4              36              68   72   76   80
       |ver | previous hash | Merkle root    |time|bits|nonce|
```

## Make a byte worksheet

1. Draw 80 numbered boxes, starting at zero.
2. Mark the six field boundaries.
3. Copy a future published test vector into the boxes without changing order.
4. Record the source and expected digest alongside it.
5. Keep parsing and hash display as separate functions with separate checks.

A compatible implementation needs known-answer vectors and rejection cases. Producing the correct byte count alone does not establish consensus compatibility. The course will reuse Framework cryptographic primitives rather than invent a new hash algorithm.

## Exercise

At which offset does the nonce begin? If a buffer has 79 bytes, should the parser read the final field anyway?

## Explained answer

The nonce begins at offset 76 and occupies bytes 76 through 79. A 79-byte buffer is too short. Reject before any out-of-bounds access; never assume an absent byte is zero. The next lesson implements a smaller bounded read so this rule becomes concrete.

## Continue learning

[Course contents](index.md) · [Next: A bounded little-endian reader](02-a-bounded-little-endian-reader.md)

[Browser edition](../../../courses/building-bitcoin-in-c/lessons/01-scope-bytes-and-compatibility.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://developer.bitcoin.org/reference/block_chain.html).
