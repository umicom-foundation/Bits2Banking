# Mathematics for AI — Unit 114: Calculate one-query causal attention by hand

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Familiarity with simple arithmetic is enough.

## What will you learn?

A query is a vector which scores retained keys. Within one attention head, raw score is the dot product of query and key divided by sqrt(head width). Softmax turns scores into nonnegative weights summing to one.

## A fully worked example

Use head width 2; query q=[1,0], keys k0=[1,0] and k1=[0,1]. Scaled scores are 1/sqrt(2) ≈0.7071 and 0. Let the associated values be v0=[2,0], v1=[0,4]. Their softmax weights are approximately [0.6698,0.3302]; output is [1.3396,1.3208].

**Helpful symbols:** `×` means multiplication, `÷` means division, `[rows, columns]` states a tensor shape, and a token row is one position in a text sequence. Each byte count and score is specific to the example, not a measured production model.

## Practise the calculation

**Question:** If both scaled scores are equal, what weight does each of the two keys receive?

<details>
<summary>Show the worked answer</summary>

Softmax gives 0.5 to each key, regardless of the common score.

</details>

## Connect the idea to native C23

The Framework tape owns numerical attention; this independent hand calculation is for qualification and learning only.

The actual mathematical implementation remains in Umicom Framework. The connected [native Transformer learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html) applies this principle to a bounded real-model experiment.

## Continue learning

[Previous unit](113-count-multilayer-qkv-tensor-shapes.md) · [Next unit](115-keep-softmax-stable-by-subtracting-the-maximum.md) · [Complete mathematics route](../../courses/maths-for-ai/incremental-attention-mathematics.html)

*Service to Many Leads to Greatness.*
