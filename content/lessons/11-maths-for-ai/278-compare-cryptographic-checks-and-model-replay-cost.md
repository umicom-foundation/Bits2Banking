# Mathematics for AI — Unit 278: Compare cryptographic checks and model replay cost

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

The cost of verifying a MAC scales roughly with message length; replaying training includes neural forward/backward computation and optimiser state. Measure them separately.

## Concept and mechanism

The cost of verifying a MAC scales roughly with message length; replaying training includes neural forward/backward computation and optimiser state. Measure them separately.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

Suppose MAC verification takes 0.2 ms and challenge replay takes 25,000 ms. Ratio = 25,000/0.2=125,000. These are synthetic illustrative values, not measured Umicom timings.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** If an illustrative verification takes 0.5 ms and a full replay takes 2,000 ms, what is replay/MAC ratio?

<details><summary>Reveal the worked answer</summary>

2,000/0.5=4,000. This ratio alone does not measure the verifier’s cheating-detection rate.

</details>

## Reading and source

- [Proof of Learning: An Incentive-Compatible Blockchain Consensus Mechanism](https://arxiv.org/abs/2007.15145)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
