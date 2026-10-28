# Mathematics for AI — Lesson 294: Count Merkle leaf, parent and root hash operations

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **count merkle leaf, parent and root hash operations** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A simple duplicate-last binary tree performs one leaf-domain hash per logical leaf, then one node-domain hash per pair at each level, then one count-bound root-domain hash. The number of internal parent hashes is the sum of the rounded-up level widths, not always n−1 for odd sizes. The SHA compression-block cost of each operation depends on input length and padding.

## Step-by-step worked example

For five leaves, internal widths are ceil(5/2)=3, ceil(3/2)=2, ceil(2/2)=1, giving six parent hashes. Add five leaf hashes and one root hash for 12 SHA-256 invocations.

## Practical task

Repeat for eight leaves.

### Worked answer and reasoning

Eight leaves produce seven parents, eight leaf hashes and one root hash: 16 invocations.

## Threat model and qualification limits

Hash invocations are not wall-clock timing samples and exclude producing original audit record digests. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/294-count-hash-operations-for-a-merkle-batch.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](293-calculate-merkle-proof-height.md)
- [Next lesson](295-calculate-a-proof-size-with-metadata.md)

*Service to Many Leads to Greatness.*
