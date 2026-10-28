# Blockchain Technology and Distributed Ledgers — Lesson 013: Build a Merkle tree from transaction digests

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **build a merkle tree from transaction digests** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

An ordered group of transactions can be represented by a single root digest. Hash each transaction into a leaf node, combine neighbouring nodes into parents, and repeat until one digest remains. Real blockchains specify their own precise byte encodings; the Umicom learning algorithm uses domain-separated SHA-256 on already-hashed record digests. A Merkle root is an authenticated-data-structure commitment only when obtained from a trusted block/header/anchor.

## Step-by-step worked example

For transactions A,B,C,D, compute four leaf-domain hashes, then parents P0=H(nodeDomain||LA||LB), P1=H(nodeDomain||LC||LD), and bind the top with count four.

## Practical task

Draw the exact path from transaction C to the final root and identify the sibling digest at each level.

### Worked answer and reasoning

C needs sibling D at its leaf level and sibling P0 at the next level; the final count-bound digest is computed after combining.

## Threat model and qualification limits

Bitcoin, Ethereum and this native educational implementation do not share identical tree encodings. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/blockchain-ledgers/lessons/013-build-a-merkle-tree-from-transaction-digests.html)
- [Course study route](../../courses/blockchain-ledgers/proof-evidence-and-consensus.html)
- [Next lesson](014-handle-an-odd-number-of-records.md)

*Service to Many Leads to Greatness.*
