# Mathematics for AI — Unit 123: Count full-window rollovers correctly

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

In the pending-token convention, the first generated token is sampled from the existing prompt. Each later pull commits the previously sampled token. A full cache replacement is required only when such a commit would evict an earlier token.

## A fully worked example

For full initial context C=4 and G=6 generated samples, there are G−1=5 pending-token transitions and every one is a rollover. For initial prompt P=2, C=4, G=6, the first C−P=2 transitions are ordinary appends; the remaining 5−2=3 transitions are rollovers.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** For P=3, C=7 and G=10, how many ordinary appends and rollovers occur?

<details>
<summary>Show the worked answer</summary>

There are nine transitions. Four can grow from three to seven retained tokens. The remaining five require full-window rollovers.

</details>

## Connect the idea to native C23

Learned absolute positional embeddings forbid silent K/V reuse across these replacements. Upper-layer history adds further reasons to re-evaluate.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](122-distinguish-byte-tokens-from-utf8-characters.md) · [Next unit](124-compare-release-timings-with-uncertainty.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
