# AI Research Frontiers — Lesson 047: Study ledger and ISO 20022 interoperability as distinct layers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **study ledger and iso 20022 interoperability as distinct layers** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Financial messages specify rich business semantics; ledger technologies specify state replication and finality under their own protocols. A payment’s ISO 20022 representation does not tell a blockchain how to settle across jurisdictions. Research a minimal canonical transaction-reference commitment, separate from customer details, while comparing permissioned DLT and existing settlement infrastructures.

## Step-by-step worked example

Bank A sends an authorised payment instruction, Bank B acknowledges it, and an audit digest is included in a ledger. The digest proves existence in a snapshot; it does not prove funds moved or final legal settlement occurred.

## Practical task

Build a seven-column research matrix: syntax, authentication, permission, messaging, clearing, settlement, audit finality.

### Worked answer and reasoning

Use the correct system owner and independent evidence for each property; do not substitute a single chain hash for all seven.

## Threat model and qualification limits

A prototype should use synthetic payment data and no live SWIFT credentials or client records. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [LoRA original research](https://arxiv.org/abs/2106.09685)

## Continue learning

- [Browser lesson](../../courses/ai-research/lessons/047-study-cross-bank-ledger-interoperability-evidence.html)
- [Course study route](../../courses/ai-research/merkle-proof-and-finality-research.html)
- [Previous lesson](046-investigate-selective-disclosure-and-predictable-hash-leakage.md)
- [Next lesson](048-write-a-falsifiable-native-merkle-research-protocol.md)

*Service to Many Leads to Greatness.*
