# Mathematics for AI — Lesson 304: Construct a Merkle audit cost and assurance table

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **construct a merkle audit cost and assurance table** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Proof sizes, arithmetic operations, elapsed latency and trust assumptions are different measurement columns. A research table should distinguish a signed local audit, replicated record archive, permissioned BFT ledger and public proof-of-stake chain at equivalent workload. Record what is verified, who can rewrite history, what independent anchor exists, and how much data is published.

## Step-by-step worked example

A 1,024-leaf proof has 320 sibling bytes. At 100 kB/s hypothetical bandwidth, that sibling payload alone takes 3.2 ms to transmit; the root/signature, round trips and hashing add separate terms.

## Practical task

Design a comparison row for an independently anchored local audit and another for a permissioned ledger; state assumptions explicitly.

### Worked answer and reasoning

The local audit proves committed bytes against an anchor; a permissioned ledger can add independently governed ordering only when its actual consensus and membership protocol are specified.

## Threat model and qualification limits

A performance comparison without controlled measurement and an identical privacy policy is not a release-grade result. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/304-build-a-cost-evidence-comparison.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](303-model-ledger-latency-versus-training-time.md)

*Service to Many Leads to Greatness.*
