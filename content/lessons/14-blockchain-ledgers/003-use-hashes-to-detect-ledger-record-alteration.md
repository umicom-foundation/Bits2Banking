# Blockchain Lesson 003 — Use hashes to detect ledger-record alteration

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **use hashes to detect ledger-record alteration** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A cryptographic hash converts an arbitrary byte string into a fixed-length digest. A hash chain includes the previous digest in the next record’s committed fields, so altering an earlier record breaks later commitments unless all affected links are recomputed. The expected final digest must be obtained from an independent trusted source.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For a four-record history, imagine digests H0, H1=SHA256(domain||H0||R1), H2=SHA256(domain||H1||R2), and H3=SHA256(domain||H2||R3). If R2 changes, recomputing H2 produces a different digest and H3 no longer matches the original trusted tip.

## Limitations and misconceptions

SHA-256 does not prove who authored R2 and does not prevent an administrator from rebuilding an entire chain and supplying a replacement tip. Hashing guessable private information can leak its contents.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Why is storing a chain and its only expected tip in the same untrusted location insufficient?

<details><summary>Reveal the worked answer</summary>

An attacker could alter the records, recompute all links and replace the tip. Independently authenticated anchoring is required to detect whole-history substitution.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Previous](002-compare-databases-replicated-ledgers-and-blockchains.md) | [Next](004-differentiate-encryption-hashes-macs-and-signatures.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
