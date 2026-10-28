# Mathematics Unit 289 — Distinguish network propagation from consensus delay

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **distinguish network propagation from consensus delay** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

An event may be broadcast rapidly yet remain uncommitted until consensus conditions are satisfied. A simple latency budget adds serialization, network, processing and waiting components.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

At 10 Mbps, a 10,000-byte frame contains 80,000 bits and takes 8 ms to serialise before RTT and verification. A 40 ms RTT and 5 ms checking yield at least 53 ms along this simplified sequential path.

## Limitations and misconceptions

Multiple hops, contention, retries, TLS and batching change measured latency.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** At 20 Mbps, how long to serialise 10,000 bytes?

<details><summary>Reveal the worked answer</summary>

80,000 bits / 20,000,000 bits/s =0.004 s=4 ms.

</details>

## Primary research or standard

- [Hyperledger Fabric: ordering service, endorsement and commitment](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

[Previous](288-calculate-receipts-under-replication.md) | [Next](290-compare-audit-receipt-and-model-update-bandwidth.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
