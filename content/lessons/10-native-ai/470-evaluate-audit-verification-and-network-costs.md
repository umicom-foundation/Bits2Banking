# LLM from Scratch — Lesson 470: Evaluate verification cost against proof size and transport overhead

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **evaluate verification cost against proof size and transport overhead** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A proof may save transfer bytes without saving total system work. A proper benchmark separately reports root construction time, proof creation time, proof verification time, payload retrieval, network overhead and independent checkpoint distribution. For one-off auditing of a tiny history, directly reading a few records may be cheaper. For repeated sparse membership checks against a large fixed batch, compact proofs become more attractive.

## Step-by-step worked example

A 1,024-leaf tree has 10 sibling hashes (320 bytes). If the application adds 48 bytes of protocol framing and sends a 32-byte claimed leaf digest, the immediate proof payload is 400 bytes; the trusted root delivery and signatures must be accounted for separately.

## Practical task

Form two scenarios: one auditor checks one entry, and 100 auditors check distinct entries. Compare network bytes and number of root builds without claiming a measured speedup.

### Worked answer and reasoning

One shared root can support many proofs, but the total bytes scale with proof count; report the root anchoring and batch build costs separately.

## Threat model and qualification limits

SHA operation counts are cost models, not measured CPU energy, wall-clock latency or security certifications. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/470-evaluate-audit-verification-and-network-costs.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](469-protect-sensitive-financial-and-training-metadata.md)
- [Next lesson](471-design-an-ai-ledger-evidence-qualification-matrix.md)

*Service to Many Leads to Greatness.*
