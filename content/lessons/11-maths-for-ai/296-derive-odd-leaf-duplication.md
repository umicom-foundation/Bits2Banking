# Mathematics for AI — Lesson 296: Derive the duplicate-last rule for odd numbers of leaves

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **derive the duplicate-last rule for odd numbers of leaves** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

For a level with an odd number of nodes, the final node is paired with itself to make a binary parent. Its sibling path can therefore include a digest equal to the node at that level. This is a documented tree convention, not an extra business record, and is distinct from adding a duplicate input leaf.

## Step-by-step worked example

Five logical leaves become three parents, then two parents, then one root node; the last leaf follows E→H(E,E)→H(P2,P2)→root.

## Practical task

Explain the first sibling for index 4 in a five-leaf input.

### Worked answer and reasoning

It is the hash of that same leaf node because index 5 is out of range at that level.

## Threat model and qualification limits

Different Merkle designs make different choices for odd nodes; importing proofs without scheme identification is unsafe. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/296-derive-odd-leaf-duplication.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](295-calculate-a-proof-size-with-metadata.md)
- [Next lesson](297-bind-logical-count-to-a-root.md)

*Service to Many Leads to Greatness.*
