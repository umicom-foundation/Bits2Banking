# Distributed Learning — Lesson 068: Keep cancellation events in the audit without granting rewards

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **keep cancellation events in the audit without granting rewards** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A cancelled federated assignment may need a record for operational accountability. However, it must not be counted as a completed numerical contribution or rewarded for useful learning. Separate event kinds and acceptance criteria in the ledger schema. The FederatedJob process-local ticket cannot be reconstructed from a public Merkle membership proof.

## Step-by-step worked example

Worker C receives round 14 assignment and cancels before producing any update. Its cancellation receipt belongs in a decision history; its accepted sample count remains zero.

## Practical task

Describe ledger states for admitted, cancelled, completed, verified and rejected work.

### Worked answer and reasoning

Only completed and validated work contributes a delta; cancellation remains an operational event.

## Threat model and qualification limits

A ledger entry does not prove CPU/GPU-seconds were spent honestly. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/068-keep-cancelled-worker-events-auditable.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](067-design-cross-institutional-replication-evidence.md)
- [Next lesson](069-compare-public-ledgers-and-private-audit-logs.md)

*Service to Many Leads to Greatness.*
