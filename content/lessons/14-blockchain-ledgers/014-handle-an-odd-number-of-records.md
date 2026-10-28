# Blockchain Technology and Distributed Ledgers — Lesson 014: Handle a Merkle level containing an odd number of records

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **handle a merkle level containing an odd number of records** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

When a layer has an odd number of nodes, a deterministic tree rule must specify the unpaired node. The educational Umicom module duplicates the last node, while other systems may use different append-only tree rules. This affects both the root and the proof. The number of logical records remains unchanged.

## Step-by-step worked example

For three leaves A,B,C, first parents are H(A,B) and H(C,C). The second hash combines the parents; the final root binds count=3. A four-leaf list [A,B,C,C] must produce a different final count-bound root.

## Practical task

Write the first two levels for five records and count internal SHA invocations.

### Worked answer and reasoning

Five leaves produce three first-level parents, then two, then one: six internal hashes, excluding leaf and root-domain hashing.

## Threat model and qualification limits

Never re-use a proof across protocols with different odd-node policies. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/blockchain-ledgers/lessons/014-handle-an-odd-number-of-records.html)
- [Course study route](../../courses/blockchain-ledgers/proof-evidence-and-consensus.html)
- [Previous lesson](013-build-a-merkle-tree-from-transaction-digests.md)
- [Next lesson](015-check-merkle-membership-without-sharing-a-block.md)

*Service to Many Leads to Greatness.*
