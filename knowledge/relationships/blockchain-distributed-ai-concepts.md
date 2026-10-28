# Relationship map — blockchain and distributed-learning fundamentals

| Concept | Canonical lesson | Framework/research boundary |
|---|---|---|
| What is a ledger? | [Lesson 1](../../content/lessons/14-blockchain-ledgers/001-understand-why-people-maintain-ledgers.md) | Trusted storage, authorisation and domain-specific accounting |
| Hash chains | [Lesson 3](../../content/lessons/14-blockchain-ledgers/003-use-hashes-to-detect-ledger-record-alteration.md) | `umicom/record_chain/chain.h` |
| Signatures and MACs | [Lesson 4](../../content/lessons/14-blockchain-ledgers/004-differentiate-encryption-hashes-macs-and-signatures.md) | `umicom/security/hmac_sha256.h` and signature/identity services |
| Merkle trees | [Lesson 6](../../content/lessons/14-blockchain-ledgers/006-explain-blocks-merkle-trees-and-inclusion-proofs.md) | Research explanation only; not a new Framework Merkle service |
| Network consensus | [Lesson 7](../../content/lessons/14-blockchain-ledgers/007-understand-peer-networking-forks-and-finality.md) | Research explanation; record-chain API does not do consensus |
| PoW and PoS | [Lesson 8](../../content/lessons/14-blockchain-ledgers/008-derive-proof-of-work-difficulty-and-expected-attempts.md) | Conceptual security economics; no token implementation |
| Permissioned ordering | [Lesson 10](../../content/lessons/14-blockchain-ledgers/010-contrast-permissioned-consensus-raft-and-bft.md) | Study Hyperledger Fabric; no local orderer |
| ML provenance | [Lesson 443](../../content/lessons/10-native-ai/443-use-the-existing-framework-record-chain-for-learning-provenance.md) | New opt-in federated audit adapter using record-chain |

A hash linked log is not an authenticated or replicated blockchain, and any model score must be separately evaluated.
