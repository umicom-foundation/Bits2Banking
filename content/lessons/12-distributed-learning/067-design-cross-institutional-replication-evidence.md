# Distributed Learning — Lesson 067: Design cross-institutional evidence for matching snapshots

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **design cross-institutional evidence for matching snapshots** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Two organisations can compare independently authenticated snapshot roots and identifiers without revealing protected source records. This can detect divergence when both operate under the same canonical encoding. It is weaker than a distributed consensus protocol because it does not define how conflicting snapshots are resolved or when a transaction is final.

## Step-by-step worked example

Institution A publishes root X for round 7, B publishes root Y for round 7. Equality means their committed byte lists match under the hash assumptions; inequality means they disagree, but does not identify which is correct.

## Practical task

Design a reconciliation workflow that freezes release on mismatch and records both statements.

### Worked answer and reasoning

Do not overwrite one party’s history. Preserve each signed observation, investigate source/ordering differences and require an authorised resolution.

## Threat model and qualification limits

Two agreeing hashes can also reflect collusion or common compromise. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [FedAvg original research](https://arxiv.org/abs/1602.05629)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/067-design-cross-institutional-replication-evidence.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](066-detect-a-missing-audit-receipt-before-release.md)
- [Next lesson](068-keep-cancelled-worker-events-auditable.md)

*Service to Many Leads to Greatness.*
