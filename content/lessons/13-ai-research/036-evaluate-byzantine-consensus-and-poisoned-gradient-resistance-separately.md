# Research Lesson 036 — Evaluate Byzantine consensus and poisoned-gradient resistance separately

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **evaluate byzantine consensus and poisoned-gradient resistance separately** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Byzantine agreement considers arbitrarily faulty messages under specified membership and synchrony assumptions. Robust aggregation considers adversarial gradient vectors and their statistical effects. Success in one area does not imply success in the other.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Four replicas can meet the n≥3f+1 lower bound for f=1 in a common BFT model, yet a legitimately admitted malicious training worker may still submit a poisonous numerical delta.

## Limitations and misconceptions

Secure aggregation hides individual deltas and may limit anomaly inspection.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Does BFT ordering prevent model poisoning?

<details><summary>Reveal the worked answer</summary>

No. It can agree on a sequence containing malicious-but-well-formed updates; robust evaluation needs separate methods.

</details>

## Primary research or standard

- [Bonawitz et al., Practical Secure Aggregation for Privacy-Preserving Machine Learning](https://arxiv.org/abs/1611.04482)

## Continue learning

[Previous](035-study-proof-of-stake-slashing-and-worker-rewards-as-different-markets.md) | [Next](037-develop-a-replay-verification-cost-model-for-learning-receipts.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
