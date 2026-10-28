# Research Lesson 038 — Compare audit logging with DLT under financial privacy constraints

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **compare audit logging with dlt under financial privacy constraints** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Financial and education deployments may require controlled retention, access rights and correction procedures. Public immutability can conflict with sensitive records or deletion requests. Ledger governance must be a measurable requirement.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Compare a private audit chain that commits only to checkpoint digests with a public ledger containing detailed patient or banking transactions. The former has a smaller exposure surface, but still needs independent anchoring and access control.

## Limitations and misconceptions

Do not interpret public availability as lawful ML-training permission.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Why is on-chain storage of personal training data usually inappropriate?

<details><summary>Reveal the worked answer</summary>

It is replicated, difficult to remove and can disclose sensitive facts; use authorised off-chain storage and minimal commitments.

</details>

## Primary research or standard

- [UK ICO: AI and data protection guidance](https://ico.org.uk/for-organisations/uk-gdpr-guidance-and-resources/artificial-intelligence/)

## Continue learning

[Previous](037-develop-a-replay-verification-cost-model-for-learning-receipts.md) | [Next](039-model-ledger-throughput-versus-training-improvement.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
