# Mathematics Unit 285 — Estimate toy proof-of-work success probability

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **estimate toy proof-of-work success probability** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

With a uniform ideal hash, requiring d leading zero bits succeeds with probability 2^(-d) per independent attempt. The expected number of attempts is 2^d.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

For d=16, p=1/65,536 and expected trials=65,536. The probability of success within n attempts is 1−(1−p)^n, not n×p when n is large.

## Limitations and misconceptions

These probabilities describe an educational toy predicate, not all real chain difficulty algorithms.

### Interpretation

This arithmetic is a deterministic teaching calculation, not a benchmark or a guarantee about runtime performance. If using it for engineering, record the units, precision, network assumptions and complete payload definitions.

## Exercise — test your understanding

**Question:** How does expected work change from d=16 to d=18?

<details><summary>Reveal the worked answer</summary>

It increases by 2^(18−16)=4, from 65,536 to 262,144 expected attempts.

</details>

## Primary research or standard

- [Satoshi Nakamoto, Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)

## Continue learning

[Previous](284-quantify-double-spend-accounting-errors.md) | [Next](286-calculate-simple-stake-vote-thresholds.md) | [Course route](../../courses/maths-for-ai/ledger-and-consensus-mathematics.html)

*Service to Many Leads to Greatness.*
