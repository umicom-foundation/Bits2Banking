# Mathematics for AI — Unit 121: Separate projection work from attention work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

A token-layer row count tracks one kind of matrix-projection work. Attention-query rows measure another. Neither is automatically equal to the number of floating-point operations or to elapsed seconds.

## A fully worked example

For context 6, layers 2, prompt 2 and 7 sampled tokens: full-context reference row budget = 6×2×7 = 84. The prefix proposal executes four single-row projection steps = 4×2 = 8 layer-rows plus three full-context traces (initial and two rollovers) = 3×6×2 = 36. The composed attention runs 36 full-context query-layer rows plus 2×(3+4+5+6)=36 more, totalling 72.

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** Does 8 newly projected token-layer rows imply exactly eight total attention queries?

<details>
<summary>Show the worked answer</summary>

No. The existing full causal-attention operator computes earlier placeholder query rows, so its query-row count is larger.

</details>

## Connect the idea to native C23

Report projected work, attention work, full-context traces and timing separately; the current path is not a guaranteed speedup.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](120-understand-seeded-nucleus-sampling.md) · [Next unit](122-distinguish-byte-tokens-from-utf8-characters.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
