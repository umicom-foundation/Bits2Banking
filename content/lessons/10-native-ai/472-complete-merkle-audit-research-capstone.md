# LLM from Scratch — Lesson 472: Complete the native Merkle audit and blockchain research capstone

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **complete the native merkle audit and blockchain research capstone** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A reproducible capstone records the exact Framework source revision, declared digest order, batch size, root, proof index, test mutations, compiler and native test output. It also documents the system’s real trust boundary: who signed the original receipt and where the expected root came from. Extend the lab by comparing a hash-linked append stream with a committed batch snapshot, without equating either to consensus.

## Step-by-step worked example

Create a five-leaf synthetic batch. The inclusion path has three 32-byte siblings (96 bytes). Verify one member; flip a leaf bit and reject it; then change the declared count and reject the proof.

## Practical task

Write a two-paragraph research conclusion: what your test establishes and what would require an independently authenticated two-machine ledger experiment.

### Worked answer and reasoning

The evidence establishes local correctness of bounded membership checks under SHA-256 assumptions; it does not establish distributed finality, real worker authentication or useful learning.

## Threat model and qualification limits

Publish negative test results and unperformed checks, rather than filling gaps with claims. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/472-complete-merkle-audit-research-capstone.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](471-design-an-ai-ledger-evidence-qualification-matrix.md)

*Service to Many Leads to Greatness.*
