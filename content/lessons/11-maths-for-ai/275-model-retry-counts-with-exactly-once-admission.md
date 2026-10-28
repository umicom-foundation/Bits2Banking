# Mathematics for AI — Unit 275: Model retry counts with exactly-once admission

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

At-least-once delivery can produce multiple identical frames; completed tickets must only count unique accepted contributions.

## Concept and mechanism

At-least-once delivery can produce multiple identical frames; completed tickets must only count unique accepted contributions.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

Workers A, B and C send one distinct result each; B retries twice. There are five delivered messages but only three accepted unique contributions. If each claimed 100 samples, total distinct sample count should be 300, not 500.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** Four workers each provide 60 unique samples and two workers each retry once. What unique count enters the mean?

<details><summary>Reveal the worked answer</summary>

4×60=240 samples, not 360; retries change message count but not unique training evidence.

</details>

## Reading and source

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
