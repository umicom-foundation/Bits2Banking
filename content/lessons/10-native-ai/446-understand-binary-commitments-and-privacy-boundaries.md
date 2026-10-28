# LLM Lesson 446 — Understand binary commitments and privacy boundaries

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **understand binary commitments and privacy boundaries** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Publishing a hash of a confidential predictable record can reveal it to an adversary who guesses candidate plaintexts and hashes them. Domain separation prevents accidental cross-protocol hash reuse; high-entropy salts or controlled keyed commitments may help, but key governance and privacy review are essential.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

If a private field is chosen from only ten likely values, an observer can hash all ten under a public deterministic scheme and compare digests. A 256-bit output does not create 256 bits of secrecy for low-entropy input.

## Limitations and misconceptions

Do not put raw client trades, datasets, worker personal details or gradients into public ledger transactions.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Why is SHA-256 of a predictable customer identifier not guaranteed to anonymise it?

<details><summary>Reveal the worked answer</summary>

A small input space is cheaply enumerated; a public hash preserves a guessable link to the underlying identifier.

</details>

## Primary research or standard

- [UK ICO: AI and data protection guidance](https://ico.org.uk/for-organisations/uk-gdpr-guidance-and-resources/artificial-intelligence/)

## Continue learning

[Previous](445-separate-ledger-events-from-model-training-and-evaluation.md) | [Next](447-introduce-merkle-proofs-as-compact-inclusion-evidence.md) | [Course route](../../courses/llm-from-scratch/federated-audit-and-ledgers.html)

*Service to Many Leads to Greatness.*
