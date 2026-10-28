# Mathematics for AI — Unit 277: Compute verified sample-weighted aggregation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

FedAvg weights compatible contributions by distinct sample count. A MAC does not change the numeric weighting formula.

## Concept and mechanism

FedAvg weights compatible contributions by distinct sample count. A MAC does not change the numeric weighting formula.

## Guided reasoning

1. Identify the meaning and units of every quantity.
2. Write the arithmetic relationship before substitution.
3. Calculate without premature rounding.
4. Classify the result as a protocol identity, estimate or observation.

## Worked example

Three workers contribute (100,0.05), (250,-0.01), (150,0.08). Weighted mean delta = (5-2.5+12)/500=14.5/500=0.029.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The displayed quantities are worked numerical examples, not observed network timings, model-quality evidence or cryptographic guarantees. Recompute them when context, precision or threat model changes.

## Test your understanding

**Question:** With two workers holding 20 and 80 distinct samples and deltas 0.20 and 0.05, compute the weighted mean.

<details><summary>Reveal the worked answer</summary>

(20×0.20+80×0.05)/100=(4+4)/100=0.08.

</details>

## Reading and source

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Course study route](../../courses/maths-for-ai/hmac-and-trust-mathematics.html)

*Service to Many Leads to Greatness.*
