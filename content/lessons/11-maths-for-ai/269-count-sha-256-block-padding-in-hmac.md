# Mathematics for AI — Unit 269: Count SHA-256 block padding in HMAC

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

SHA-256 processes 64-byte message blocks; HMAC adds a 64-byte inner pad and a 64-byte outer pad before the respective hash computations.

## Concept and mechanism

SHA-256 processes 64-byte message blocks; HMAC adds a 64-byte inner pad and a 64-byte outer pad before the respective hash computations.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

For a 12-byte message, inner hash processes an initial 64-byte key pad followed by 12 data bytes plus SHA padding. The outer hash processes 64 pad bytes plus the 32-byte inner digest plus its SHA padding. Count the distinct inner/outer message streams rather than claiming that HMAC is one hash.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** How many raw pad bytes are mixed into the two HMAC passes before including message or digest bytes?

<details><summary>Reveal the worked answer</summary>

128 bytes: one 64-byte ipad block and one 64-byte opad block.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
