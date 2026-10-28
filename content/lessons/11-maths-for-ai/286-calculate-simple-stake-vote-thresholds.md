# Mathematics Unit 286 — Calculate simple stake-vote thresholds

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **calculate simple stake-vote thresholds** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Weighted agreement percentages refer to voting power or stake, not necessarily the number of validator nodes. A threshold is reached only when the corresponding weighted sum meets it.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

If validators control 35, 25, 20 and 20 units of 100, a 2/3 threshold requires at least 66⅔. The two largest have 60 and fail; adding either 20 yields 80 and passes.

## Limitations and misconceptions

Ethereum finality has specific checkpoint voting and slashing rules beyond this arithmetic.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** Can validators holding 35+25 units alone satisfy a two-thirds threshold of 100?

<details><summary>Reveal the worked answer</summary>

No. Their combined voting weight is 60, below 66⅔.

</details>

## Primary research or standard

- [Ethereum documentation: proof-of-stake and finality](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

## Continue learning

[Previous](285-estimate-toy-proof-of-work-success-probability.md) | [Next](287-apply-a-common-bft-replica-bound.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
