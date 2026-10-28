# Distributed Learning — Lesson 069: Compare public blockchain publication against controlled audit logs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **compare public blockchain publication against controlled audit logs** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

An open public chain increases external visibility and persistence at the cost of fees, latency, data-exposure risks and governance constraints. A signed enterprise audit log has simpler administration but relies on its operator and independent anchors. A permissioned DLT may help when several institutions need independent ordering authority. Start from the trust model rather than introducing a token to make a proof seem more valuable.

## Step-by-step worked example

A bank consortium needs to audit only checkpoint digests, while model update blobs remain encrypted off-chain. Compare a single bank audit, a three-bank permissioned service and a public chain.

## Practical task

Prepare a decision matrix for confidentiality, identity membership, independent finality, failure recovery and operational cost.

### Worked answer and reasoning

No one architecture dominates: the chosen trust and regulatory context determines the justified solution.

## Threat model and qualification limits

Publicly viewable data are not necessarily authorised for model-training reuse. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [FedAvg original research](https://arxiv.org/abs/1602.05629)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/069-compare-public-ledgers-and-private-audit-logs.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](068-keep-cancelled-worker-events-auditable.md)
- [Next lesson](070-measure-merkle-communication-cost-on-the-wan.md)

*Service to Many Leads to Greatness.*
