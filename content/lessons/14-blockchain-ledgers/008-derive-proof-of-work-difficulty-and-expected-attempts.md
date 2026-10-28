# Blockchain Lesson 008 — Derive proof-of-work difficulty and expected attempts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **derive proof-of-work difficulty and expected attempts** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Proof-of-work asks participants to find a block header whose hash satisfies a target condition. A verifier checks the completed hash cheaply. This asymmetry provides Sybil resistance in a permissionless setting under economic and network assumptions. It is not a method for calculating neural-network gradients.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For an illustrative toy difficulty of twelve leading zero bits, a uniformly distributed hash succeeds with probability 1/4096 per independent trial. Expected trials = 4096. A miner could succeed first try or need much longer; the expected count is not a per-run guarantee.

## Limitations and misconceptions

Real Bitcoin difficulty uses numeric targets and adjusting consensus rules, not only a fixed count of leading zero bits. Mining energy and security economics must be evaluated independently from model-training usefulness.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** If a toy target is tightened from 12 to 13 leading zero bits, how does expected work change?

<details><summary>Reveal the worked answer</summary>

The success probability halves from 1/4096 to 1/8192, so expected independent trials double from 4096 to 8192.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](007-understand-peer-networking-forks-and-finality.md) | [Next](009-explain-proof-of-stake-and-economically-enforced-finality.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
