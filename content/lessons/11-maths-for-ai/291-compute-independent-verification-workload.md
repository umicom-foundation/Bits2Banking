# Mathematics Unit 291 — Compute independent verification workload

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **compute independent verification workload** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Probabilistic sampling can reduce expected verifier cost but weakens detection guarantees. Under independent uniform sampling of m distinct bad positions out of N, choose exact hypergeometric reasoning when sampling without replacement.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For a toy workload with 100 independent checks and a verifier selecting 5 samples uniformly with replacement, if 10% are corrupted then the probability of detecting at least one is 1−(0.9)^5≈40.951%. The cost is 5 checks.

## Limitations and misconceptions

Assumptions of independence and the corruption distribution may fail against an adaptive malicious contributor.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** What is the detection probability for two independent 10%-hit samples?

<details><summary>Reveal the worked answer</summary>

1−0.9²=0.19, or 19%.

</details>

## Primary research or standard

- [Proof of Learning: useful work and consensus research](https://arxiv.org/abs/2007.15145)

## Continue learning

[Previous](290-compare-audit-receipt-and-model-update-bandwidth.md) | [Next](292-assess-total-useful-work-economics.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
