# Mathematics for AI — Lesson 298: Compare bandwidth for full lists and inclusion proofs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **compare bandwidth for full lists and inclusion proofs** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Sending all digest values costs 32n bytes. A compact binary proof needs 32 ceil(log2(n)) sibling bytes, excluding index, count, leaf digest, root and security envelope. The reduction is attractive when a recipient already has an authenticated root and checks only a small number of leaves.

## Step-by-step worked example

For 1024 digests, complete list=1024×32=32768 bytes. A single membership path=10×32=320 bytes, exactly 1/102.4 the bytes of that list; the ratio is not a full protocol speed ratio.

## Practical task

Estimate two hundred distinct proof sibling payloads without sharing nodes.

### Worked answer and reasoning

200×320=64000 bytes, now exceeding the complete 32768-byte digest list; batching proofs could change the comparison.

## Threat model and qualification limits

Do not assume all users request one inclusion proof or that transport cost is the only cost. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/298-compare-full-digest-lists-and-membership-paths.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](297-bind-logical-count-to-a-root.md)
- [Next lesson](299-estimate-random-hash-collision-probability.md)

*Service to Many Leads to Greatness.*
