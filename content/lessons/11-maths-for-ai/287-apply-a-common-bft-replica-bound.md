# Mathematics Unit 287 — Apply a common BFT replica bound

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **apply a common bft replica bound** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

In a common BFT model with n≥3f+1, a system with n replicas can tolerate at most floor((n−1)/3) Byzantine participants.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For n=10, f≤floor(9/3)=3. A tenth replica does not let this model tolerate four Byzantine replicas.

## Limitations and misconceptions

Protocol specifics, synchrony and availability assumptions matter; the bound is not universal to every protocol.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** How many replicas are required for f=2?

<details><summary>Reveal the worked answer</summary>

n≥3×2+1=7 replicas.

</details>

## Primary research or standard

- [Hyperledger Fabric: ordering service, endorsement and commitment](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

[Previous](286-calculate-simple-stake-vote-thresholds.md) | [Next](288-calculate-receipts-under-replication.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
