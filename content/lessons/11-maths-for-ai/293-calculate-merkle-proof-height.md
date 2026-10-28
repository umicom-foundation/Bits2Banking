# Mathematics for AI — Lesson 293: Calculate Merkle proof height from leaf count

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **calculate merkle proof height from leaf count** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

For a binary tree with duplicate-last padding, the number of sibling levels is the number of times the node count must be rounded up after dividing by two until one node remains. This is ceil(log2(n)) for n≥1, with n=1 giving zero sibling levels. The index and count are needed to determine left/right orientation.

## Step-by-step worked example

Starting from n=13: 13→7→4→2→1. The chain has four transitions, so a membership proof has four sibling hashes or 128 hash bytes.

## Practical task

Calculate the height for n=8 and n=9 without rounding n down.

### Worked answer and reasoning

8 needs 3 levels; 9 needs 4 levels.

## Threat model and qualification limits

The trusted root, leaf digest, index, count and network framing are additional bytes. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/293-calculate-merkle-proof-height.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Next lesson](294-count-hash-operations-for-a-merkle-batch.md)

*Service to Many Leads to Greatness.*
