# Verify tensor shapes through a Transformer stack

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Shapes are the first correctness test

Most neural numerical bugs are dimension errors or unintended broadcasting. A layer stack requires each block to preserve the hidden width. In a single-sequence educational example, start with four tokens, eight channels, and two attention heads. The input and output of every block are `[4,8]`. Each head processes `8/2 = 4` channels. A 12-feature feed-forward sublayer first expands `[4,8]` to `[4,12]`, then contracts it back to `[4,8]`.

A learned token table for a 16-token vocabulary has shape `[16,8]`, and a learned position table for four positions has shape `[4,8]`. The vocabulary projection has shape `[8,16]`. Consequently the logits are `[4,16]`—64 scores, not 64 probabilities.

## Inspect before allocating

`UmiAiTrainingStackedDecoderPlan` delegates parameter and memory arithmetic to `UmiAiTrainingModelScalingEstimateBuild`, the existing Framework scaling service. The stacked model additionally validates the live tape's conservative tensor/context/layer bounds. A candidate may fit a theoretical memory estimate yet exceed a concrete tensor or computational-graph capacity.

| Tensor | Shape | Why |
|---|---|---|
| Token embeddings | `[16,8]` | 16 IDs, each mapped to 8 numbers |
| Block Q/K/V projection | `[8,8]` | Hidden width is unchanged |
| Feed-forward up | `[8,12]` | Expand features |
| Feed-forward down | `[12,8]` | Restore hidden width |
| Final logits | `[4,16]` | One score per token and vocabulary ID |

The current model has one sequence per call. Extending to independent sequences requires explicit sequence masks and validated attention isolation; concatenating unrelated documents as one causal stream changes the training problem.

## Practice

For context length six, channels twelve, three attention heads and hidden width twenty-four, calculate the head width and final logits shape for vocabulary size 200.

<details><summary>Worked answer</summary>

Head width is `12/3 = 4` channels. With six token positions and 200 possible next-token IDs, logits have shape `[6,200]`, containing 1,200 floating-point values. Verify that the actual Framework implementation admits the shape; mathematical validity alone does not guarantee implementation capacity.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
