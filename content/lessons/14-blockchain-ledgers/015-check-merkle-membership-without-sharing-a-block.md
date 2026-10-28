# Blockchain Technology and Distributed Ledgers — Lesson 015: Check membership without downloading every block record

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **check membership without downloading every block record** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A light client that already trusts a root can verify a particular record using the record digest and the sibling hashes on its path. At each level, the index determines whether the sibling is on the left or right. This proves inclusion in that root, not that the sender is honest, the transaction is valid, or the enclosing block is final.

## Step-by-step worked example

For 1,024 leaves, a single path has ten 32-byte siblings: 320 bytes of sibling payload. The full leaf digest list occupies 32,768 bytes.

## Practical task

What external fact must the client know before trusting the proof?

### Worked answer and reasoning

The expected root and its publication authority must be verified independently of the path sender.

## Threat model and qualification limits

SPV/light-client security differs significantly across proof-of-work, proof-of-stake and permissioned networks. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Ethereum proof of stake](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

## Continue learning

- [Browser lesson](../../courses/blockchain-ledgers/lessons/015-check-merkle-membership-without-sharing-a-block.html)
- [Course study route](../../courses/blockchain-ledgers/proof-evidence-and-consensus.html)
- [Previous lesson](014-handle-an-odd-number-of-records.md)
- [Next lesson](016-understand-append-only-histories-and-consistency.md)

*Service to Many Leads to Greatness.*
