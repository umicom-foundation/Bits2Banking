# Mathematics for AI — Unit 270: Compute the size of an authenticated assignment frame

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

A schema-1 UMFW assignment is 184 header bytes plus 32 checksum bytes. UMFA adds a 20-byte header plus 32-byte MAC.

## Concept and mechanism

A schema-1 UMFW assignment is 184 header bytes plus 32 checksum bytes. UMFA adds a 20-byte header plus 32-byte MAC.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

Total = (184+32)+(20+32)=268 bytes. The inner length field must equal 216; the total input must equal 268. A 269-byte input is invalid under exact-size framing.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** What is the total transmitted byte count for one assignment with no FP32 delta?

<details><summary>Reveal the worked answer</summary>

268 bytes. Its separate length field still says 216 inner bytes.

</details>

## Reading and source

- [RFC 4231, HMAC-SHA-256 test vectors](https://www.rfc-editor.org/rfc/rfc4231.html)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
