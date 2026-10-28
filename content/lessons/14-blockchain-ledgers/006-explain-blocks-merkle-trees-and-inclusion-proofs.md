# Blockchain Lesson 006 — Explain blocks, Merkle trees and inclusion proofs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **explain blocks, merkle trees and inclusion proofs** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A block groups records and commonly contains a commitment to its predecessor and to the transactions it contains. A binary Merkle tree hashes transaction leaves and then pairs of child hashes until one root remains. An inclusion proof gives the sibling hashes required to recompute the root, not a proof that the transaction obeys financial policy.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

With four leaves A,B,C,D, compute P=H(H(A)||H(B)), Q=H(H(C)||H(D)) and root=H(P||Q), using proper domain separation. An inclusion proof for C consists of the sibling leaf hash H(D) and subtree hash P: two 32-byte hashes, or 64 bytes, before direction flags and framing.

## Limitations and misconceptions

A Merkle root commits to an ordered set of bytes, not the truth of each entry. Duplicate-leaf treatment, odd leaf counts, domain tags and byte order must be specified to interoperate.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** How many sibling digests are needed to prove inclusion in a balanced tree with eight leaves?

<details><summary>Reveal the worked answer</summary>

Three: one sibling at each of the three binary levels because log₂(8)=3. The inclusion proof also needs the position/orientation of those siblings.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](005-trace-transactions-balances-and-double-spending.md) | [Next](007-understand-peer-networking-forks-and-finality.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
