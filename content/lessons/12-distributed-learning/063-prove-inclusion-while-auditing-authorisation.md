# Distributed Learning — Lesson 063: Prove inclusion while independently auditing authorisation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **prove inclusion while independently auditing authorisation** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A valid inclusion proof demonstrates batch membership under a root. Permission to assign data shards is enforced by a policy/identity service and may change over time. Keep the policy revision in the signed receipt and retain revocation decisions, but do not declare that a historical proof overrides current authorisation.

## Step-by-step worked example

A worker was authorised in policy revision 4 and its receipt is in a root published yesterday. Policy revision 5 revokes training rights today. The historical receipt remains included; new work must be refused.

## Practical task

List three distinct time-bound questions: signed yesterday, authorised yesterday, authorised now.

### Worked answer and reasoning

Signature validity, historical policy and current policy are different predicates and need separate timestamps and evidence.

## Threat model and qualification limits

Revocation does not retroactively delete a hash from a public immutable ledger. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [FedAvg original research](https://arxiv.org/abs/1602.05629)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/063-prove-inclusion-while-auditing-authorisation.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](062-pin-a-base-checkpoint-in-every-proof-context.md)
- [Next lesson](064-separate-real-workers-from-synthetic-lab-records.md)

*Service to Many Leads to Greatness.*
