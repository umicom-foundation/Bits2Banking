# Mathematics Unit 283 — Compute Merkle tree proof lengths

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **compute merkle tree proof lengths** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

For a perfect binary tree with 2^h leaves, a conventional inclusion path contains h sibling digests; leaf position data is additional.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For 1024 leaves, h=10. A SHA-256 inclusion path requires 10×32=320 bytes of sibling hashes, excluding leaf, root, directions and framing.

## Limitations and misconceptions

Odd-size tree conventions and domain tags vary by protocol.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** How many sibling digest bytes for 64 leaves?

<details><summary>Reveal the worked answer</summary>

log₂(64)=6 levels; 6×32=192 bytes.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](282-locate-binary-fields-without-native-structure-padding.md) | [Next](284-quantify-double-spend-accounting-errors.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
