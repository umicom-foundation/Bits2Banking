# Merkle proofs and ledger integrity — source reading notes

**Authors:** Sammy Hegab / Umicom Foundation · **Licence:** MIT

The following are independently published technical references, not permissions to redistribute their full text or training data.

1. [NIST IR 8202 — Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final). Defines the broad ledger, cryptographic and consensus terminology used in introductory modules. It does not describe the Umicom-specific count-bound Merkle encoding.
2. [Bitcoin whitepaper](https://bitcoin.org/bitcoin.pdf). Read the simplified-payment-verification section and distinguish block-header proof of work from the path proving a transaction appears in a block.
3. [Ethereum Proof of Stake](https://ethereum.org/developers/docs/consensus-mechanisms/pos/). Read the checkpoint and finality explanation; participation, stake weighting and slashing are protocol-specific.
4. [Hyperledger Fabric ordering service](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html). Compare Raft crash-fault ordering and the BFT option, along with transaction endorsement, ordering and validation.
5. [Umicom Framework source](https://github.com/umicom-foundation/umicom-framework). The canonical SHA-256 and record-chain sources are the code-level baseline; an opt-in Merkle component layers on the original digest implementation.

## Reproducibility questions

Does the proof bind the exact leaf count and ordering? Is the root independently anchored? What does a verifier accept as an authenticated identity? What exact transaction-state or learning-quality property, if any, has actually been checked? These questions distinguish byte-level integrity from an authorised ledger transition and statistically beneficial learning.
