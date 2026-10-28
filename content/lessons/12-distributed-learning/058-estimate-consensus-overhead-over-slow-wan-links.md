# Distributed Learning Lesson 058 — Estimate consensus overhead over slow WAN links

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **estimate consensus overhead over slow wan links** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Independent validation and ordering add message transfers and potentially quorum waits. Time-to-quality of the model remains the primary objective, not raw ledger throughput.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A 5 KB receipt is 40 kilobits; at 10 Mbps its ideal serialisation takes 4 ms. A 100 ms RTT may dominate that cost even before finality or database commits.

## Limitations and misconceptions

Network simulations must distinguish RTT, throughput, loss, batching and actual node heterogeneity.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** What dominates the toy link when 4 ms transfer and 100 ms RTT are sequential?

<details><summary>Reveal the worked answer</summary>

RTT contributes the larger component; the two together already total 104 ms before protocol processing.

</details>

## Primary research or standard

- [Geographically distributed model training: GeoMesh, Findings EMNLP 2026](https://aclanthology.org/2026.findings-emnlp.720/)

## Continue learning

[Previous](057-learn-permissioned-ledger-ordering.md) | [Next](059-plan-a-privacy-aware-model-history.md) | [Course route](../../courses/distributed-learning/ledger-coordination-and-evidence.html)

*Service to Many Leads to Greatness.*
