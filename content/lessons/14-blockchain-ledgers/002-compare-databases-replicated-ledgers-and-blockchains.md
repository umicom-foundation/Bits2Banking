# Blockchain Lesson 002 — Compare databases, replicated ledgers and blockchains

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **compare databases, replicated ledgers and blockchains** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A central ledger has one administrative authority. A replicated database has several copies but may retain one authority and leader. A distributed ledger coordinates records across independent nodes; a blockchain is a particular design that links ordered groups of transactions by cryptographic commitments. These are not synonyms. A hash chain running on one laptop is not consensus.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Three machines mirror the same two events. Replica A is current at sequence 2; B is current at 1; C is offline at 0. Merely having three copies does not establish who is entitled to commit sequence 3. That requires a documented replication and authority rule.

## Limitations and misconceptions

The number of copies does not measure decentralisation; ownership, trust, fault tolerance and independent validation do. Do not call an ordinary backup a blockchain.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Does adding a second read-only replica to a single-authority account ledger create a permissionless blockchain?

<details><summary>Reveal the worked answer</summary>

No. A replica improves redundancy or read capacity, but its existence does not establish open membership, independent consensus or proof of work/stake.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Previous](001-understand-why-people-maintain-ledgers.md) | [Next](003-use-hashes-to-detect-ledger-record-alteration.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
