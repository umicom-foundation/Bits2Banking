# AI Research Frontiers — Lesson 25: Study HMAC and digital signatures as separate evidence families

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

A shared-key MAC is excellent for efficient permissioned message authentication, but its public audit properties differ from digital signatures.

## Concept and mechanism

With HMAC, the verifier may generate the same tag as the sender. In a public dispute that weakens attribution. Detached signatures provide a verification key that need not generate signatures, but depend on trustworthy key enrolment and algorithm-specific assumptions.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

A research paper should report exactly which key management and dispute assumptions apply before ranking proof schemes.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** Why cannot an independently untrusted third party verify an HMAC without learning the secret?

<details><summary>Reveal the worked answer</summary>

A third party requires the shared secret to recompute the MAC, which would also let that party forge accepted tags.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/ai-research/trust-verification-research.html)

*Service to Many Leads to Greatness.*
