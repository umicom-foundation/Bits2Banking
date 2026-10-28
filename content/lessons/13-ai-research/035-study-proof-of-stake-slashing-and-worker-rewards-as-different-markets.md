# Research Lesson 035 — Study proof-of-stake slashing and worker rewards as different markets

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **study proof-of-stake slashing and worker rewards as different markets** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

PoS incentivises validators to follow consensus rules by exposing stake to specified penalties. A useful-learning reward needs independent valuation of contributor work. A staked but adversarial trainer can still poison the model.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

If two workers spend the same 10 GPU-hours but one makes held-out loss worse, paying equal rewards by advertised effort may be economically irrational.

## Limitations and misconceptions

Contribution quality may be noisy, delayed and expensive to estimate.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Which metric should a scientific reward protocol optimise beyond claimed GPU-hours?

<details><summary>Reveal the worked answer</summary>

Quality-adjusted, independently evaluated marginal contribution with bounded verification and communication costs.

</details>

## Primary research or standard

- [Ethereum documentation: proof-of-stake and finality](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

## Continue learning

[Previous](034-study-permissionless-proof-of-work-as-a-security-economic-baseline.md) | [Next](036-evaluate-byzantine-consensus-and-poisoned-gradient-resistance-separately.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
