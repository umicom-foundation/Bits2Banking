# Blockchain Lesson 001 — Understand why people maintain ledgers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **understand why people maintain ledgers** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A ledger is an ordered record of economic or operational changes. In a bank account, the balance is a derived state rather than a physical pile of coins. A double-entry book records paired effects; an access-controlled database may be the simplest correct ledger. In distributed learning a ledger can instead record research decisions, so no customer balance is involved.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Start with a synthetic cash balance of £100. Record a £30 debit and a £15 credit, with IDs T1 and T2. The final balance is 100 − 30 + 15 = £85. Replaying a duplicate T1 incorrectly produces £55. Give each event a unique identity and a controlled replay policy.

## Limitations and misconceptions

A single trusted database can serve this example; blockchain is not required. An ordered log is evidence of recorded decisions, not proof that the underlying transaction was lawful.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** If event T2 is replayed twice, what balance results and which control failed?

<details><summary>Reveal the worked answer</summary>

£100 − £30 + £15 + £15 = £100. Idempotent event processing or duplicate-ID rejection failed.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Next](002-compare-databases-replicated-ledgers-and-blockchains.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
