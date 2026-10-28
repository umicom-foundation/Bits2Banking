# Mathematics for AI — Unit 272: Calculate MAC transport overhead

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Overhead ratio is extra framing bytes divided by a chosen total; clearly declare the denominator.

## Concept and mechanism

Overhead ratio is extra framing bytes divided by a chosen total; clearly declare the denominator.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

One two-float result has 184+8+32=224 inner bytes and 276 total bytes. Outer share of total = 52/276≈18.8406%; outer relative to original = 52/224≈23.2143%.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** What percentage of the total two-float authenticated frame is the outer wrapper? Round to two decimal places.

<details><summary>Reveal the worked answer</summary>

(52/276)×100≈18.84%.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
