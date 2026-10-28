# Mathematics for AI — Lesson 301: Derive the classic 3f+1 Byzantine quorum model

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **derive the classic 3f+1 byzantine quorum model** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Classical partially synchronous BFT designs often use at least 3f+1 replicas to tolerate up to f Byzantine faults, with commit evidence around 2f+1 votes. This is a *model-specific* requirement, not a universal rule for every blockchain. Safety relies on authenticated members, protocol messages, view changes and quorum intersection.

## Step-by-step worked example

For f=2, N≥3×2+1=7 and a 2f+1=5-vote quorum. Two size-five subsets of a seven-node set overlap in at least three nodes, exceeding the two Byzantine members and forcing at least one honest intersection.

## Practical task

Compute the classic lower bound for f=3 and required quorum.

### Worked answer and reasoning

N≥10; a 2f+1 quorum has seven votes.

## Threat model and qualification limits

Ledger proof inclusion and majority observation tally do not implement BFT consensus. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/301-derive-bft-validator-thresholds.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](300-calculate-validator-majority-in-raft.md)
- [Next lesson](302-estimate-epoch-attestation-fraction.md)

*Service to Many Leads to Greatness.*
