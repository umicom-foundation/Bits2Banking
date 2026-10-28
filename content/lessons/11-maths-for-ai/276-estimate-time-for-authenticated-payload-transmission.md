# Mathematics for AI — Unit 276: Estimate time for authenticated payload transmission

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

One-way serialization time is bytes×8 divided by data rate in bit/s; it excludes latency, acknowledgements and cryptography.

## Concept and mechanism

One-way serialization time is bytes×8 divided by data rate in bit/s; it excludes latency, acknowledgements and cryptography.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

For 16,652 bytes on a 10 Mbps link, serialization time = 16,652×8/10,000,000 = 0.0133216 seconds = 13.3216 ms. An RTT of 100 ms is a separate network property.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** What is serialization time for a 268-byte frame at 1 Mbps?

<details><summary>Reveal the worked answer</summary>

268×8/1,000,000=0.002144 seconds, or 2.144 ms.

</details>

## Reading and source

- [RFC 9846, TLS 1.3 (2026 revision)](https://www.rfc-editor.org/rfc/rfc9846.html)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
