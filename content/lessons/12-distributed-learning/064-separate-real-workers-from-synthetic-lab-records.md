# Distributed Learning — Lesson 064: Separate synthetic proof fixtures from actual worker training

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **separate synthetic proof fixtures from actual worker training** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Educational C23 labs can create deterministic 32-byte digest arrays without executing a neural training step. Such tests are valuable for binary parsing, inclusion and failure atomicity but provide no performance or model-quality evidence. A real distributed experiment must run a Framework learner with approved data and record the exact checkpoint and held-out evaluation.

## Step-by-step worked example

Three synthetic digests are enough to test proof formation; three independently trained models are needed to test convergence. A passing hash test cannot be counted as three successful training workers.

## Practical task

Write an evidence label for each of these results: static proof test, local training, and independent WAN training.

### Worked answer and reasoning

Each report should describe the actual operation performed, compiler/runtime, worker topology and unperformed validations.

## Threat model and qualification limits

A digest generated from synthetic bytes is not a real worker signature. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/064-separate-real-workers-from-synthetic-lab-records.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](063-prove-inclusion-while-auditing-authorisation.md)
- [Next lesson](065-reconstruct-batch-roots-after-reception.md)

*Service to Many Leads to Greatness.*
