# Mathematics Unit 284 — Quantify double-spend accounting errors

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **quantify double-spend accounting errors** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A ledger balance depends on exactly-once application of accepted transitions. Counting the same event twice is a logic error even when the bytes and signature are valid.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Initial 250 units; spend 80; receive 20 -> 190. Replaying the spend again produces 110, an 80-unit error.

## Limitations and misconceptions

A transaction hash detects duplication but does not automatically reject a repeated application.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** What is the final balance if the spend of 80 is incorrectly applied three times?

<details><summary>Reveal the worked answer</summary>

250−3×80+20=30 units, which is 160 less than the correct 190.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](283-compute-merkle-tree-proof-lengths.md) | [Next](285-estimate-toy-proof-of-work-success-probability.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
