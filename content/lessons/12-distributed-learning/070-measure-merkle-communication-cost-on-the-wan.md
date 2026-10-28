# Distributed Learning — Lesson 070: Measure proof traffic separately from learning updates

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **measure proof traffic separately from learning updates** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Merkle inclusion proofs can reduce audit traffic but do not shrink the raw model updates required for FedAvg. The two payload types must be measured separately: data/model-transfer bytes and audit/reconciliation bytes. Network latency, retransmissions and root anchoring can dominate small theoretical proof sizes.

## Step-by-step worked example

A LoRA delta upload is 2 MiB while a batch membership proof has 320 sibling bytes. Reducing the 320-byte proof cannot materially eliminate the 2 MiB update upload.

## Practical task

Build a network cost table for 10, 100 and 1,000 audits and separate them from training rounds.

### Worked answer and reasoning

Total cost must include transferred model deltas, validation results, roots, proofs, signatures and protocol framing.

## Threat model and qualification limits

A byte-count calculation is not a measured end-to-end WAN benchmark. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/070-measure-merkle-communication-cost-on-the-wan.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](069-compare-public-ledgers-and-private-audit-logs.md)
- [Next lesson](071-preserve-data-sovereignty-in-distributed-ledger-evidence.md)

*Service to Many Leads to Greatness.*
