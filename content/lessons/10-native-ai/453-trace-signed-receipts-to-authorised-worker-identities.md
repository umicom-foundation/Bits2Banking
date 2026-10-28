# LLM Lesson 453 — Trace signed receipts to authorised worker identities

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **trace signed receipts to authorised worker identities** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Authentication binds a message to approved key material. The Framework identity registry and authorisation service must separately evaluate worker enablement, roles and dataset permissions. A ledger receipt should record only a minimal scoped identity commitment; keys and secret provider values stay outside public payloads.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Worker W is registered but disabled. Its key still produces a valid HMAC from an old backup. A policy check should reject new work even though the cryptographic MAC matches; the audit can record that rejection without accepting its model delta.

## Limitations and misconceptions

Key possession and employment or data access rights are different claims.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Should a valid HMAC override a disabled-worker policy?

<details><summary>Reveal the worked answer</summary>

No. Deny-by-default authorisation and revocation must be checked independently of message authentication.

</details>

## Primary research or standard

- [RFC 2104: HMAC message authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Previous](452-describe-smart-contracts-and-outside-world-oracles.md) | [Next](454-protect-against-duplicate-work-receipts-and-replay.md) | [Course route](../../courses/llm-from-scratch/federated-audit-and-ledgers.html)

*Service to Many Leads to Greatness.*
