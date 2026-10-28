# Video script — The native federated wire protocol

**Bits to Banking · Sammy Hegab · Umicom Foundation**
**Companion:** LLM Lessons 409–412 · **Format:** narrated walkthrough and storyboard · **Target:** 5–7 minutes

## Opening visual — Why is a C structure not a message?

Narration: A pointer into one process is a meaningless address in another.
Even a simple count may be eight bytes on one platform and four on another.
To exchange information, we need a *wire contract*: an agreed order, format
and maximum size. The first version has a fixed 184-byte header, an optional
FP32 result vector, and a 32-byte SHA-256 trailer.

Storyboard: Draw two computer icons with distinct memory maps. Place a red
cross over a pointer arrow. Replace it with a blue framed sequence of bytes,
labelled `UMFW | schema | kind | length | round | worker | payload | SHA`.

## Show the numerical representation

Narration: Big-endian encodes the most significant byte first. The number
0x01020304 becomes bytes 01, 02, 03, 04. The binary32 number 1.0 is
3F 80 00 00. These are byte representations, not native structure dumps.
A result with one scalar requires 184 + 4 + 32, or 220 bytes.

Storyboard: Animate the hexadecimal groups appearing in their fixed positions.
Show a 4,096-element upper bound, never an unbounded input length.

## Explain the limit of a hash

Narration: If one byte changes after hashing, the digest will no longer
match. But SHA-256 has no secret key. A dishonest sender can replace the
message and compute a fresh hash. For authentication, we must use a trusted
identity, a verified signature or authenticated channel. Even then, we have
not proven the worker trained honestly or improved a model.

Storyboard: Use four separate ticks labelled *bytes*, *sender*, *computation*
and *quality*. Only the first is ticked for the bare checksum exercise.

## Learner prompt

Ask: Why are the coordinator's internal ticket fields absent from the wire?
Invite learners to answer before revealing: those fields are process-local
capabilities and must be mapped to the public round and sequence by the
coordinator, not transmitted to a worker.

Closing: Next, inspect failure-atomic decoding and the native message envelope.
