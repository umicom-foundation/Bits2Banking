# Canonical encoding and bounded numeric representations

**Umicom Foundation · Public educational note · 2026**

## Why a C struct cannot be the protocol

Field padding, alignment, native `size_t`, pointer width and endianness can
differ by compiler and machine. A structure's in-memory layout is not a
portable interchange standard. Encode explicit widths in a documented order,
using checked arithmetic for total length. The C23 learning codec requires an
IEEE-754 binary32 environment and rejects non-finite weight-space deltas.

## Fully worked framing

- Fixed header: 184 bytes.
- Domain-separated, unkeyed SHA-256 trailer: 32 bytes.
- Empty assignment payload: 0 bytes, total 216 bytes.
- One-scalar result: 4 bytes, total 220 bytes.
- 4,096-scalar result: 16,384 payload bytes, total 16,600 bytes.

Example network-order 32-bit integer: `0x01020304` -> bytes `01 02 03 04`.
Example IEEE-754 binary32: `1.0` -> bits `0x3f800000` -> bytes
`3f 80 00 00`. The digest includes the schema, round, contributor, policy
and complete numerical payload. An attacker capable of replacing data can
also recompute an *unkeyed* checksum, so channel identity and signatures
require independent mechanisms.

## Numerical exercise

At 10 Mbps, a 16,600-byte result takes at least
`16,600 × 8 / 10,000,000 = 0.01328 s = 13.28 ms` to serialise on a link.
This does not include network framing, TLS, RTT, congestion or compute.
For the toy 220-byte result, the mathematical lower bound is 0.176 ms.

Further study: review the IETF's normative network-byte-order conventions and
IEEE-754 binary interchange. A checksum proves byte consistency under its
assumptions, not a signed identity or statistical correctness of learning.
