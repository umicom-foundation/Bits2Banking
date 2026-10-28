# LLM from Scratch — Lesson 427: Qualify an HMAC implementation with published vectors

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Use independently published test vectors rather than circular tests that recompute expected results with the same implementation.

## Concept and mechanism

Conformance tests supply a fixed key, message and expected MAC. RFC 4231 covers short keys, long keys, repeated bytes and large payloads. A test is stronger when its expected result comes from an external standard and the candidate engine uses the project’s production SHA-256 implementation, not a copy pasted answer.

## Guided reasoning

1. Read one RFC 4231 case completely.
2. Verify key length and message bytes.
3. Compare every one of the 32 output bytes.
4. Flip one bit of the expected MAC to test rejection.
5. Test a key longer than the SHA block to exercise the prehash path.

## Worked example

For RFC 4231 case 1, key=0x0b repeated 20 times and message="Hi There". The first eight MAC hex digits must be b0344c61. The exact 32-byte reference is required; comparing only eight digits would be a weak regression.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

Passing one vector does not establish constant-time behaviour, sound key management or a full protocol security review.

## Test your understanding

**Question:** Why is hashing the expected MAC and comparing hashes a poor substitute for a direct complete MAC comparison?

<details><summary>Reveal the worked answer</summary>

It adds an unnecessary transform and still requires checking all 32 expected bytes. A fixed-length, value-independent comparison directly verifies the output with fewer moving parts.

</details>

## Reading and source

- [RFC 4231, HMAC-SHA-256 test vectors](https://www.rfc-editor.org/rfc/rfc4231.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
