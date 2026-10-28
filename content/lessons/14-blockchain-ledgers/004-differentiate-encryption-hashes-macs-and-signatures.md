# Blockchain Lesson 004 — Differentiate encryption, hashes, MACs and signatures

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **differentiate encryption, hashes, macs and signatures** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A hash is an unkeyed commitment to bytes; a MAC authenticates a message to parties sharing a secret; a digital signature uses a private signing key and a publicly verifiable public key. Encryption instead addresses confidentiality. Identity registry and role-based authorisation are separate decisions even after a cryptographic check succeeds.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Worker A signs a 32-byte checkpoint hash using its private signing key. A verifier checks the signature with the published, trusted public key; it must still confirm that worker A is authorised for the job. A HMAC with a shared secret can establish that a key holder sent a message but cannot offer independent public attribution between multiple holders.

## Limitations and misconceptions

A valid signature does not prove that AI training took place or that a bank payment is permitted. Never include private keys in a public demonstration.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Can a public SHA-256 digest alone identify which worker generated a model delta?

<details><summary>Reveal the worked answer</summary>

No. Anyone can hash the same bytes. Use trusted key binding and verified authentication, then apply independent policy and training-quality checks.

</details>

## Primary research or standard

- [RFC 8032: EdDSA digital signatures](https://www.rfc-editor.org/rfc/rfc8032.html)

## Continue learning

[Previous](003-use-hashes-to-detect-ledger-record-alteration.md) | [Next](005-trace-transactions-balances-and-double-spending.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
