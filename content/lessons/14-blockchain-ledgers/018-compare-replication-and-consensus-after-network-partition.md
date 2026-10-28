# Blockchain Technology and Distributed Ledgers — Lesson 018: Compare replication and consensus after a network partition

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **compare replication and consensus after a network partition** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

Replicating identical files to several computers increases availability and disaster recovery but does not automatically ensure that conflicting writes are ordered consistently. Under a network partition, two sides may see different transactions. A consensus protocol specifies which side can commit and what happens on reconnection, under declared safety and liveness assumptions.

## Step-by-step worked example

A three-node Raft group partitions one node away from two. A correctly configured majority group can continue, while the isolated node cannot independently commit new majority-backed entries.

## Practical task

Why does copying the isolated node’s latest file over the majority log violate the protocol?

### Worked answer and reasoning

The isolated copy lacks a majority-backed commit history; overwrite could destroy valid ordered entries.

## Threat model and qualification limits

The example is for crash-fault Raft assumptions, not malicious or Byzantine replicas. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Ethereum proof of stake](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

## Continue learning

- [Browser lesson](../../courses/blockchain-ledgers/lessons/018-compare-replication-and-consensus-after-network-partition.html)
- [Course study route](../../courses/blockchain-ledgers/proof-evidence-and-consensus.html)
- [Previous lesson](017-distinguish-utxo-accounts-and-state-commitments.md)
- [Next lesson](019-explain-raft-elections-and-commit-majorities.md)

*Service to Many Leads to Greatness.*
