# LLM from Scratch — Lesson 462: Verify a bounded Merkle inclusion proof in native C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **verify a bounded merkle inclusion proof in native c23** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A proof is a path: leaf index, total leaf count, one sibling digest for every level, and a separately trusted root. Verification must reject impossible indices, missing siblings, surplus noncanonical data and wrong duplicated-last siblings. It then reconstructs parents in the exact left/right order dictated by each index bit. The result is compared with the anchored root only after the count-binding step.

## Step-by-step worked example

For 1,024 leaves, the height is 10 and an ordinary sibling array occupies 10×32=320 bytes. For five leaves the height is 3 and the sibling payload occupies 96 bytes, excluding metadata and the trusted root.

## Practical task

Test valid membership, wrong leaf index, one-bit changes, wrong root, wrong sibling count and changed unused proof bytes.

### Worked answer and reasoning

Valid evidence returns OK; malformed evidence returns INVALID_ARGUMENT and an otherwise well-shaped but nonmatching path returns INVALID_STATE.

## Threat model and qualification limits

The API proves inclusion of a *hash*; the application must verify the corresponding signed receipt, data rights and independent root authority. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/462-verify-bounded-merkle-inclusion-proofs.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](461-bind-leaf-count-to-avoid-padded-list-ambiguity.md)
- [Next lesson](463-keep-audit-publication-failure-atomic.md)

*Service to Many Leads to Greatness.*
