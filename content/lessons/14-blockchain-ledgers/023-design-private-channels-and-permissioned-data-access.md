# Blockchain Technology and Distributed Ledgers — Lesson 023: Design permissioned channels and selective disclosure

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **design permissioned channels and selective disclosure** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A consortium ledger often serves institutions with different data entitlements. Membership, read access, write permissions and transaction validation must be enforced independently of hashes. Channels and private-data mechanisms can limit visibility, but metadata and commitments may still leak information. Use protected off-chain document stores when deletion, confidentiality or regulatory sovereignty requires them.

## Step-by-step worked example

Bank A and B share a settlement-status hash while customer identifiers and underlying payment details remain under their existing data-governance controls. A third auditor sees only the authorised non-sensitive evidence.

## Practical task

List which parties can read, propose, endorse and order events in this scenario.

### Worked answer and reasoning

Permissions differ by role and governance contract; a hashing function is not an access-control engine.

## Threat model and qualification limits

Any ledger architecture requires an explicit legal/privacy assessment before live financial deployment. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

- [Browser lesson](../../courses/blockchain-ledgers/lessons/023-design-private-channels-and-permissioned-data-access.html)
- [Course study route](../../courses/blockchain-ledgers/proof-evidence-and-consensus.html)
- [Previous lesson](022-explain-hyperledger-fabric-endorse-order-validate.md)
- [Next lesson](024-choose-a-ledger-for-banking-payments-and-ai-provenance.md)

*Service to Many Leads to Greatness.*
