# LLM from Scratch — Lesson 463: Keep root and proof publication failure-atomic

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **keep root and proof publication failure-atomic** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

In a native systems API, success must not be half-visible. The implementation calculates a root and proof in private fixed-size workspace, validates size and aliasing, and publishes both outputs only after all underlying SHA operations succeed. Output pointers cannot overlap the digest input or each other. This contract matters when an application presents verifiable evidence to an auditor: an earlier root must not be partially overwritten by a failed new request.

## Step-by-step worked example

If the requested leaf index equals the leaf count, there is no record at that position. The function rejects the request before modifying either a caller-owned 32-byte root or the proof structure.

## Practical task

Initialise output buffers to fixed nonzero patterns; call the proof operation with an out-of-range index; compare every output byte before and afterwards.

### Worked answer and reasoning

The outputs are identical after rejection; this is tested in the native regression suite.

## Threat model and qualification limits

Failure atomicity inside one process does not imply atomic persistence to a database or multi-party finality. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Umicom native Framework SHA-256](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/463-keep-audit-publication-failure-atomic.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](462-verify-bounded-merkle-inclusion-proofs.md)
- [Next lesson](464-distinguish-merkle-inclusion-from-ledger-consistency.md)

*Service to Many Leads to Greatness.*
