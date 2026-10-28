# AI Research Frontiers — Lesson 043: Benchmark sparse inclusion against full audit replay

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **benchmark sparse inclusion against full audit replay** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

An inclusion proof is compact evidence that a digest was committed to a root. Full audit replay validates actual receipt semantics, signatures and possibly training arithmetic. The correct experiment reports the fraction of work verified and residual attack surface. Selective proofs should be combined with random audits only where the security-cost trade-off can be modelled and tested.

## Step-by-step worked example

One thousand records, one inclusion check versus full replay: a short proof saves digest transfer but does not re-execute 1,000 training updates. Record separate CPU time and uncovered risks.

## Practical task

Propose a budgeted verifier experiment varying audit sampling 1%, 10% and 100%.

### Worked answer and reasoning

State detection probability assumptions and actual measured verifier time; the Merkle primitive alone is insufficient.

## Threat model and qualification limits

Work-sampling challenges can miss cheating and cannot be described as complete correctness certification. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [LoRA original research](https://arxiv.org/abs/2106.09685)

## Continue learning

- [Browser lesson](../../courses/ai-research/lessons/043-benchmark-proof-cost-against-full-audit-replay.html)
- [Course study route](../../courses/ai-research/merkle-proof-and-finality-research.html)
- [Previous lesson](042-study-fraud-proofs-for-model-update-receipts.md)
- [Next lesson](044-compare-merkle-batching-to-bft-finality.md)

*Service to Many Leads to Greatness.*
