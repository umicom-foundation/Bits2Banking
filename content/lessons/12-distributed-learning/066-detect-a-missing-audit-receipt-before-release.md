# Distributed Learning — Lesson 066: Detect an incomplete decision batch at publication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **detect an incomplete decision batch at publication** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

An attacker can remove the last record and present a valid root for the shorter list unless the verifier independently knows the expected complete root and the logical count. The application should check both the session finalisation state and independently anchored expected checkpoint. A local hash recomputation without expected completeness is insufficient.

## Step-by-step worked example

A source published root R for five receipts. An export contains four entries and a newly computed R4. R4 may be internally consistent but is not the published five-item root.

## Practical task

Explain why the verifier needs expected root AND accepted publication policy.

### Worked answer and reasoning

The expected root supplies an independent integrity anchor; policy states which batch should have existed.

## Threat model and qualification limits

Even complete receipt history does not establish that the underlying training data were lawful. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/distributed-learning/lessons/066-detect-a-missing-audit-receipt-before-release.html)
- [Course study route](../../courses/distributed-learning/verifiable-batch-evidence.html)
- [Previous lesson](065-reconstruct-batch-roots-after-reception.md)
- [Next lesson](067-design-cross-institutional-replication-evidence.md)

*Service to Many Leads to Greatness.*
