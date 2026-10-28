# LLM Lesson 449 — Estimate proof-of-work security and verification costs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **estimate proof-of-work security and verification costs** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A useful distinction is the cost of producing one acceptable PoW solution and the cost of checking it. In a uniform hash toy model, d leading zero bits mean probability 2^(-d) per attempt and 2^d expected attempts. Useful ML training does not share that cheap, deterministic verification relation.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For d=12, expected trials=4096 and one successful hash is verified with one hash computation. Replaying a claimed 100-step neural-training run might require substantial computation; a SHA-256 of the final weights cannot certify those steps.

## Limitations and misconceptions

PoW hash trials are not ML gradients and do not train an LLM.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Why does PoW-style cheap verification fail to carry over automatically to stochastic model updates?

<details><summary>Reveal the worked answer</summary>

Training usefulness depends on data, state, optimisation and statistical evaluation; hashing its output only checks bytes.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](448-distinguish-replication-from-byzantine-agreement.md) | [Next](450-explain-proof-of-stake-validator-duties-and-finality.md) | [Course route](../../courses/llm-from-scratch/federated-audit-and-ledgers.html)

*Service to Many Leads to Greatness.*
