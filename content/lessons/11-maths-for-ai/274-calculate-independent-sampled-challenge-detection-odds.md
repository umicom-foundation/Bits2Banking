# Mathematics for AI — Unit 274: Calculate independent sampled-challenge detection odds

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

If each audit independently detects a fabricated update with probability p, the probability of no detection over n independent audits is (1-p)^n. Independence is a substantive assumption.

## Concept and mechanism

If each audit independently detects a fabricated update with probability p, the probability of no detection over n independent audits is (1-p)^n. Independence is a substantive assumption.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

At p=0.2 and n=5, non-detection probability = 0.8^5=0.32768; probability of at least one detection = 0.67232 (67.232%). This concerns behavioural verification, not HMAC forgery probability.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** Under the stated independent model, what is the probability of at least one detection when p=0.5 and n=3?

<details><summary>Reveal the worked answer</summary>

1-(1-0.5)^3=1-0.125=0.875 or 87.5%.

</details>

## Reading and source

- [Proof of Learning: An Incentive-Compatible Blockchain Consensus Mechanism](https://arxiv.org/abs/2007.15145)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
