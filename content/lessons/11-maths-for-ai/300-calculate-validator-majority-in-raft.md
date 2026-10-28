# Mathematics for AI — Lesson 300: Calculate a majority for crash-fault-tolerant Raft

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **calculate a majority for crash-fault-tolerant raft** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A replicated log with N voting members requires a strict majority floor(N/2)+1 for decisions under its protocol. Intersecting majorities help prevent two different leaders from both committing a conflicting entry under the same configuration assumptions. Counting matching hash strings without an implemented Raft protocol is not the same as establishing these guarantees.

## Step-by-step worked example

For five voting nodes, floor(5/2)+1=3. If two nodes are unavailable, three can still form a majority; with three unavailable, the remaining two cannot.

## Practical task

Find the majority for seven voters and maximum tolerated unavailable voters while remaining available.

### Worked answer and reasoning

Majority is 4; up to 3 unavailable nodes may be tolerated for quorum availability, given the required conditions.

## Threat model and qualification limits

Raft addresses crash failures under its protocol, not arbitrary Byzantine forgeries. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/300-calculate-validator-majority-in-raft.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](299-estimate-random-hash-collision-probability.md)
- [Next lesson](301-derive-bft-validator-thresholds.md)

*Service to Many Leads to Greatness.*
