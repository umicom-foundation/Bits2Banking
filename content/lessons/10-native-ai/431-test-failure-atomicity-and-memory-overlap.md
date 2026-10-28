# LLM from Scratch — Lesson 431: Test failure atomicity and memory overlap

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Cover capacity, aliasing, invalid inputs and tampering without weakening existing source contracts.

## Concept and mechanism

A C23 native boundary must handle caller-controlled capacities. Reading beyond a frame is not permissible merely because the digest will later fail. Returning partial decoded arrays is also unacceptable: the caller may already rely on their previous values. Tests should snapshot both record structs and output scalars, submit malformed inputs, and compare buffers byte-for-byte.

## Guided reasoning

1. Exercise short output capacity.
2. Exercise a forged authenticated frame with malformed inner checksum.
3. Exercise overlapping input and output buffers.
4. Confirm stale epoch and wrong key do not alter outputs.
5. Use sanitizers to inspect bounded stack and integer operations.

## Worked example

A valid two-float frame is decoded into a destination with capacity one. The decoder returns CAPACITY_EXCEEDED and preserves the output float sentinel -11 rather than writing only its first scalar.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

A sanitizer pass is evidence for tested inputs only, not a formal proof of memory safety across the entire program.

## Test your understanding

**Question:** What should a C23 function do if it cannot write its complete declared vector?

<details><summary>Reveal the worked answer</summary>

Reject the request with an appropriate capacity error and leave every caller-owned output unchanged. Partial publication cannot be treated as success.

</details>

## Reading and source

- [RFC 4231, HMAC-SHA-256 test vectors](https://www.rfc-editor.org/rfc/rfc4231.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
