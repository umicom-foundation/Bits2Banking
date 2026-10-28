# Blockchain Lesson 005 — Trace transactions, balances and double spending

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **trace transactions, balances and double spending** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A transaction defines a state change and must be validated under deterministic rules. UTXO-style ledgers spend explicitly referenced unspent outputs; account-style ledgers update balances and nonces. Both face conflicting or duplicate submissions, and agreement on ordering is essential for preventing double spending in distributed systems.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

An unspent output worth 10 units is referenced by transfers to two recipients, each claiming 10. Both individually look affordable, but after the first is accepted the output is spent and the second must be rejected. In an account-based system a monotonically checked nonce can prevent the same account operation from being processed twice.

## Limitations and misconceptions

A signature on two conflicting transactions does not choose which one wins; it only confirms an authorised signing key. Validation and consensus on history remain necessary.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Why can both conflicting transactions have mathematically valid signatures and yet only one be applied?

<details><summary>Reveal the worked answer</summary>

A signature validates each transaction’s authorisation claim. The ledger state and accepted order determine which spendable output remains available.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](004-differentiate-encryption-hashes-macs-and-signatures.md) | [Next](006-explain-blocks-merkle-trees-and-inclusion-proofs.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
