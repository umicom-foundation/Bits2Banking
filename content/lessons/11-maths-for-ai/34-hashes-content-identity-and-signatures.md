# Mathematics for AI — Unit 34: Hashes, Content Identity and Signatures

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Begin with a simple identifier

Suppose two pupils submit documents containing exactly the same text. We might compare every byte to confirm equality, but that becomes expensive for a large library. A cryptographic hash function calculates a short, fixed-length **digest** of the supplied bytes. SHA-256 returns 256 bits, traditionally displayed as 64 hexadecimal characters.

A hexadecimal digit encodes four bits. Thus `64 × 4 = 256` bits. Since eight bits make one byte, the raw digest occupies `256 ÷ 8 = 32` bytes.

## What a digest can tell us

If two byte sequences are different, a cryptographic hash is designed so their digests will overwhelmingly likely differ. This supports accidental-change detection and exact content identification, but collisions are theoretically possible. A digest is **not** encrypted content: it is a one-way derived identifier, not a reversible storage format.

A Framework snapshot contains the digest of its original frozen decoder checkpoint. If even one original weight bit changes, the digest should almost certainly change, so an adapter paired with the old model must not be accepted as matching the new one.

## What a digest cannot tell us

Anyone can run SHA-256. If someone substitutes a different file, they can also substitute a freshly calculated digest. Therefore `file + hash` is not proof of trusted authorship. Digital signatures use a cryptographic key and a trusted verification policy to establish a separate authenticity claim.

The Framework's existing signed-release and publisher-trust services remain the relevant authority for external model provenance. An adapter checkpoint's own SHA-256 serves integrity only.

## Separate three identities

The **frozen-model digest** identifies the original decoder weights. The **adapter snapshot digest** identifies the trained low-rank weights and step count. The **dataset digest** identifies the ordered collection of approved training examples and their partitions. All three must agree with the intended experiment when resuming it.

## Practise

1. How many bytes occupy a 256-bit digest? 2. Why can't an ordinary digest prove a supplier was authorised? 3. Why are the adapter and base-model digests separate?

<details><summary>Show the worked answers</summary>

1. `256 ÷ 8 = 32` bytes. 2. Anyone able to replace bytes can recompute the unsigned digest. 3. An adapter can change while the frozen model remains identical; they are distinct owned objects and must be identified separately.

</details>

**Continue:** [portable snapshots](../10-native-ai/96-build-portable-snapshot-records.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
