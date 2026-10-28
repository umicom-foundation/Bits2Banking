# LLM from Scratch — Lesson 430: Verify the MAC before decoding untrusted floating-point data

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Defend the parser’s trust boundary and preserve caller-owned output buffers on failure.

## Concept and mechanism

Attackers can corrupt lengths, float encodings, participant identifiers and checksum trailers. A robust receiving path first enforces a public maximum frame length, then validates the authenticated header and MAC against an enrolled key. Only after that does it invoke the existing canonical wire decoder. The decoder still checks its own SHA checksum and finite-FP32 constraints.

## Guided reasoning

1. Reject null pointers and underlength frames before offset access.
2. Check epoch and constant-work MAC comparison.
3. Decode into staged storage.
4. Publish only after every check succeeds.
5. Keep returned float-buffer lifetimes explicit for the downstream job owner.

## Worked example

An attacker flips one byte in the encoded contributor ID. The existing wire checksum fails unless recalculated; irrespective of that checksum, the surrounding HMAC now differs. The receiving API rejects the frame without overwriting an existing output delta of -7.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

Authentication does not make a finite malicious gradient safe. Norm limits and independent evaluation remain necessary.

## Test your understanding

**Question:** Why is updating the decoded output array before verifying the tag a failure-atomicity defect?

<details><summary>Reveal the worked answer</summary>

An attacker could cause partially published model-update data even though the enclosing authentication fails. Nothing caller-visible should change until validation is complete.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
