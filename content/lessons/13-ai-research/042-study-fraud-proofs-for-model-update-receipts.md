# AI Research Frontiers — Lesson 042: Study the boundary between fraud proofs and useful learning

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **study the boundary between fraud proofs and useful learning** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A fraud proof is compelling when a verifier can cheaply demonstrate a deterministic rule violation. Model quality is statistical and a supposedly “better” neural update may harm another distribution. Compare cheaply checkable protocol violations—wrong base hash, duplicate ticket, NaNs—with costly semantic quality checks on a hidden evaluation set.

## Step-by-step worked example

A worker submits a correct SHA-256 digest for an update that contains a NaN. Membership and identity may pass; the existing numerical aggregator must reject non-finite values before publishing a model update.

## Practical task

Design two attack classes: objectively invalid serialisation and statistically harmful but numerically finite deltas.

### Worked answer and reasoning

The former can be rejected deterministically; the latter requires independent evaluation and an explicit utility definition.

## Threat model and qualification limits

Do not call the second class cryptographically proven invalid without a defined proof system. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/ai-research/lessons/042-study-fraud-proofs-for-model-update-receipts.html)
- [Course study route](../../courses/ai-research/merkle-proof-and-finality-research.html)
- [Previous lesson](041-evaluate-hash-commitments-against-independent-signatures.md)
- [Next lesson](043-benchmark-proof-cost-against-full-audit-replay.md)

*Service to Many Leads to Greatness.*
