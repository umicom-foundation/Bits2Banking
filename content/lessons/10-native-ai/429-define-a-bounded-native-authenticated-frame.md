# LLM from Scratch — Lesson 429: Define a bounded native authenticated frame

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Explain a binary envelope with explicit sizes and portable integer representation.

## Concept and mechanism

A safe envelope cannot be a native struct dumped to disk: native alignment, pointer values and host byte order would differ. The experimental UMFA wrapper uses a 20-byte header, an unchanged UMFW frame and a 32-byte HMAC. Its length field counts the inner frame, while the outer exact size is checked before any decoding or copying.

## Guided reasoning

1. Check magic and schema revision.
2. Read the nonzero key epoch as eight network-order bytes.
3. Reject unsupported flags.
4. Compare the declared inner length to the exact input size.
5. Verify the MAC before the embedded wire parser is called.

## Worked example

An assignment UMFW frame occupies 184 + 32 = 216 bytes. UMFA adds 20 + 32 bytes, so the authenticated assignment occupies 268 bytes. A two-element FP32 result occupies 184 + 8 + 32 + 52 = 276 bytes.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

A bounded header and length check protects memory allocation; it does not provide confidentiality or authorise the task.

## Test your understanding

**Question:** How many bytes does the wrapper add independently of the inner delta length?

<details><summary>Reveal the worked answer</summary>

It adds 52 bytes: 20 bytes of authenticated framing metadata plus a 32-byte HMAC tag.

</details>

## Reading and source

- [RFC 4231, HMAC-SHA-256 test vectors](https://www.rfc-editor.org/rfc/rfc4231.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
