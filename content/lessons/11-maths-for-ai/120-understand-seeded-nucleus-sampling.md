# Mathematics for AI — Unit 120: Understand seeded nucleus sampling

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

Temperature rescales logits before softmax. Top-K retains up to K highest-scoring eligible tokens; nucleus top-p retains the smallest ordered prefix whose cumulative probability crosses threshold p. A deterministic seed makes repeated sampling reproducible.

## A fully worked example

Suppose four already-normalised eligible tokens have probabilities [0.55,0.25,0.15,0.05], ordered highest first. With top-p=0.80, the first two reach 0.80 and constitute the nucleus. With top-p=0.90, three tokens are needed (sum 0.95).

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** With probabilities [0.4,0.3,0.2,0.1] and p=0.65, how many candidates remain?

<details>
<summary>Show the worked answer</summary>

Two: 0.4+0.3=0.7 is the first cumulative sum at least 0.65.

</details>

## Connect the idea to native C23

Use the existing `UmiAiTrainingSampleLogitsNucleus`; a second sampling implementation would break reproducible parity.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](119-measure-logit-parity-with-an-absolute-tolerance.md) · [Next unit](121-separate-projection-work-from-attention-work.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
