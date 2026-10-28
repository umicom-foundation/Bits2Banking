# Research Lesson 034 — Study permissionless proof-of-work as a security-economic baseline

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **study permissionless proof-of-work as a security-economic baseline** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A PoW chain uses resource cost to make historical reorganisation costly. Its hash predicate is objective and cheap to check, unlike the usefulness of a neural update.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

At 12 toy leading-zero bits the expected hash workload is 4096 attempts. A single successful digest does not train anything.

## Limitations and misconceptions

Mining-effort accounting is not the same as verifying scientific model improvement.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Why is SHA-256 a poor standalone proof of useful learning?

<details><summary>Reveal the worked answer</summary>

It authenticates neither execution nor generalisation: the output hash is consistent with fabricated or harmful model updates.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](033-review-blockchain-consensus-assumptions-before-designing-ai-incentives.md) | [Next](035-study-proof-of-stake-slashing-and-worker-rewards-as-different-markets.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
