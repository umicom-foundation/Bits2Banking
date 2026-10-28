# Research Lesson 039 — Model ledger throughput versus training improvement

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **model ledger throughput versus training improvement** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A faster block producer does not necessarily accelerate WAN local SGD. Training performance is determined by data, optimiser, communication, model quality and verification; ledger ordering is just one potential overhead.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A round takes 60 s of training and 5 s of finality: removing the finality wait saves at most 5/65≈7.7% of this serial toy path, not a 7.7% improvement in model accuracy.

## Limitations and misconceptions

Benchmark actual traces and account for overlapping stages and p95 delays.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** What principal model metric remains necessary alongside ledger TPS?

<details><summary>Reveal the worked answer</summary>

Held-out validation quality and time-to-target quality at matched computation and data budget.

</details>

## Primary research or standard

- [Douillard et al., Distributed Low-Communication Training of Language Models](https://arxiv.org/abs/2311.08105)

## Continue learning

[Previous](038-compare-audit-logging-with-dlt-under-financial-privacy-constraints.md) | [Next](040-write-a-reproducible-cross-institutional-ledger-research-plan.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
