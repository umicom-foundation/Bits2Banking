# Research Lesson 037 — Develop a replay-verification cost model for learning receipts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **develop a replay-verification cost model for learning receipts** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A verification protocol must define which training steps can be recomputed, which entropy is fixed and which hardware-dependent nondeterminism is tolerated. Honest training can vary numerically across accelerators.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

If full training costs 1,000 CPU-seconds and sampling verification costs 50 CPU-seconds, verification is 5% of claimed training cost. This alone says nothing about cheating detection probability or false positives.

## Limitations and misconceptions

An attacker may adapt to known challenge distributions; no universal proof follows from one experiment.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** What else must be reported besides the 5% verification cost?

<details><summary>Reveal the worked answer</summary>

Detection rate against specified attacks, false rejection of honest work, quality of accepted updates and trust assumptions.

</details>

## Primary research or standard

- [Proof of Learning: useful work and consensus research](https://arxiv.org/abs/2007.15145)

## Continue learning

[Previous](036-evaluate-byzantine-consensus-and-poisoned-gradient-resistance-separately.md) | [Next](038-compare-audit-logging-with-dlt-under-financial-privacy-constraints.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
