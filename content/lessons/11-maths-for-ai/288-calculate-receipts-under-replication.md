# Mathematics Unit 288 — Calculate receipts under replication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **calculate receipts under replication** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Replicating an archive multiplies raw storage, not necessarily trust. Transport, database indexing, signatures and encryption add further bytes.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

1,000 receipts × (224-byte payload +156-byte canonical record encoding) =380,000 bytes per complete replica. Four full copies consume 1,520,000 raw bytes.

## Limitations and misconceptions

Replicas without consensus can legitimately disagree about their current head during failures.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** How many raw bytes for 250 receipts replicated five times?

<details><summary>Reveal the worked answer</summary>

250×380×5=475,000 bytes, excluding ancillary metadata.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Previous](287-apply-a-common-bft-replica-bound.md) | [Next](289-distinguish-network-propagation-from-consensus-delay.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
