# Replication, Raft, BFT and proof-of-stake — comparative references

**Authors:** Sammy Hegab / Umicom Foundation · **Licence:** MIT

- [Raft consensus paper](https://raft.github.io/raft.pdf) — leader election, log replication, crash-fault safety and membership changes; the 51% quorum arithmetic is not the whole algorithm.
- [Hyperledger Fabric ordering](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html) — permissioned orderers, deterministic block ordering, Raft and BFT implementations, endorsement separated from ordering and peer validation.
- [Ethereum PoS finality](https://ethereum.org/developers/docs/consensus-mechanisms/pos/) — stake-based attestations and checkpoint finalisation. Treat the two-thirds criterion as conditional on Ethereum's wider protocol.
- [NIST blockchain overview](https://csrc.nist.gov/pubs/ir/8202/final) — definitions of centralised versus decentralised ledgers and consensus mechanisms.

These sources motivate mathematical exercises, not a new Umicom consensus implementation. Compare safety, liveness, synchrony assumptions, byzantine fault limits, reconfiguration, identity and governance before describing any system as a DLT.
