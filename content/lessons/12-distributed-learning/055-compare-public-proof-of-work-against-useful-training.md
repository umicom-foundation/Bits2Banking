# Distributed Learning Lesson 055 — Compare public proof-of-work against useful training

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **compare public proof-of-work against useful training** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

PoW has a cheap objective verification predicate while model updates depend on a dataset, checkpoint and stochastic optimisation. Proof-of-learning research studies this asymmetry rather than assuming it disappears.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A 16-bit toy target expects 65,536 hash attempts and one cheap verification. A 1,000-step training claim cannot be certified just by hashing the final model.

## Limitations and misconceptions

Training on unauthorised or poisoned data can still produce real gradients.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** What must useful-learning verification assess beyond update byte identity?

<details><summary>Reveal the worked answer</summary>

The base state, authorised data, execution assumptions and held-out quality/economic value.

</details>

## Primary research or standard

- [Proof of Learning: useful work and consensus research](https://arxiv.org/abs/2007.15145)

## Continue learning

[Previous](054-use-merkle-inclusion-for-batch-evidence.md) | [Next](056-compare-proof-of-stake-with-data-quality-governance.md) | [Course route](../../courses/distributed-learning/ledger-coordination-and-evidence.html)

*Service to Many Leads to Greatness.*
