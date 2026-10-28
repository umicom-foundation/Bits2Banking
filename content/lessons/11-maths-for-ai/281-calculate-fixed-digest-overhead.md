# Mathematics Unit 281 — Calculate fixed digest overhead

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **calculate fixed digest overhead** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A SHA-256 digest occupies 32 bytes (256 bits), regardless of how long the input was. It commits to bytes but does not compress those bytes reversibly.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A record commits to six 32-byte digests. The digest section requires 6×32=192 bytes. With 32 bytes of fixed metadata the canonical audit payload is 224 bytes.

## Limitations and misconceptions

A 256-bit digest cannot by itself supply 256 bits of secrecy for predictable input.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** What is the digest-section size for eight SHA-256 commitments?

<details><summary>Reveal the worked answer</summary>

8×32=256 bytes, excluding labels, transport metadata and signatures.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Next](282-locate-binary-fields-without-native-structure-padding.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
