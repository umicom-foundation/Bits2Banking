# LLM from Scratch — Lesson 460: Construct Merkle trees when a level has an odd node count

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **construct merkle trees when a level has an odd node count** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A binary tree requires a deterministic policy for a trailing unpaired node. The educational library duplicates the last node at that particular level; it does not invent a phantom record. A proof contains that duplicated value as its sibling so that every verifier reconstructs the same parent. Other protocols may use different odd-node conventions, so exchanging a proof without declaring the convention is unsafe.

## Step-by-step worked example

For five leaves A,B,C,D,E, the first layer has H(A,B), H(C,D), H(E,E); the next has H(P0,P1), H(P2,P2); finally combine the two. The proof for E contains its own leaf digest at the first level and its parent at the next level.

## Practical task

Trace the proof indices for leaf index four (zero-based) and explain when a sibling is a duplicate rather than another real record.

### Worked answer and reasoning

At the first level the sibling index is 4, at the second level the sibling is the parent at index 2, then the index becomes 0 at the root.

## Threat model and qualification limits

A duplicate-last construction must bind the original leaf count, otherwise histories with different lengths can become ambiguous. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/460-construct-merkle-trees-with-odd-batch-sizes.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](459-use-domain-separation-in-merkle-hash-operations.md)
- [Next lesson](461-bind-leaf-count-to-avoid-padded-list-ambiguity.md)

*Service to Many Leads to Greatness.*
