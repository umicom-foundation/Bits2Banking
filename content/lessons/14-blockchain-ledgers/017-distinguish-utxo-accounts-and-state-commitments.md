# Blockchain Technology and Distributed Ledgers — Lesson 017: Distinguish UTXO, account state and state commitments

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **distinguish utxo, account state and state commitments** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A UTXO model tracks discrete unspent outputs; an account-based model tracks balances and contract state. Both need transaction validation and consensus rules. A state commitment can summarise a state snapshot, but it is not an ordinary transaction inclusion proof. Application designers must know which root commits transaction history and which commits executable state.

## Step-by-step worked example

Alice owns two unspent outputs worth 4 and 6 units. A proposed 7-unit payment spends the 4+6 outputs, creates 7 for the recipient and 3 as change, ignoring fees. The state is updated only after validity/consensus policy.

## Practical task

Explain why a history Merkle root alone cannot tell whether Alice’s balance is spendable.

### Worked answer and reasoning

The system must validate unspent status, signatures, conservation, fees and finality of the accepted state; a history hash does not execute these rules.

## Threat model and qualification limits

Financial settlement law and bank accounting are different from cryptocurrency transaction representation. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/blockchain-ledgers/lessons/017-distinguish-utxo-accounts-and-state-commitments.html)
- [Course study route](../../courses/blockchain-ledgers/proof-evidence-and-consensus.html)
- [Previous lesson](016-understand-append-only-histories-and-consistency.md)
- [Next lesson](018-compare-replication-and-consensus-after-network-partition.md)

*Service to Many Leads to Greatness.*
