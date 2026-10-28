# Mathematics Unit 292 — Assess total useful-work economics

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **assess total useful-work economics** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Use an explicit cost model instead of equating ledger transactions with achieved learning. Separate training, communication, evaluation, audit and consensus costs.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Suppose per round: training 40 s, WAN 12 s, verification 8 s, and ledger finality 5 s, all serial and non-overlapping. Total is 65 s. Removing ledger finality leaves 60 s, an approximate 7.69% reduction from 65 s, without saying model quality changed.

## Limitations and misconceptions

Actual pipeline stages can overlap, so this is a lower-level teaching budget rather than measured deployment speed.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** If verification doubles from 8 s to 16 s with all else fixed, what is total time?

<details><summary>Reveal the worked answer</summary>

40+12+16+5=73 s.

</details>

## Primary research or standard

- [SoK: Blockchain-based Decentralized AI](https://arxiv.org/abs/2411.17461)

## Continue learning

[Previous](291-compute-independent-verification-workload.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
