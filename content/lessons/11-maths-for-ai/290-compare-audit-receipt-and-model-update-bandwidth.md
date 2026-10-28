# Mathematics Unit 290 — Compare audit receipt and model-update bandwidth

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **compare audit receipt and model-update bandwidth** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Control receipts are much smaller than many model-update tensors. Reducing receipt bytes does not necessarily dominate WAN training performance.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A 4096-FP32-value update consumes 4096×4=16,384 bytes. An illustrative 224-byte audit payload is about 1.37% of that update. Other security and transport overhead is excluded.

## Limitations and misconceptions

A small receipt cannot replace the full update needed by the existing aggregator.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** What is the size ratio for 224 bytes of receipt data to a 8192-byte update?

<details><summary>Reveal the worked answer</summary>

224/8192≈0.02734375, or about 2.734375%.

</details>

## Primary research or standard

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Previous](289-distinguish-network-propagation-from-consensus-delay.md) | [Next](291-compute-independent-verification-workload.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
