# Mathematics of stacked model inference — learning path

**Mathematics for AI · Sammy Hegab · Umicom Foundation**

These units extend the introductory [mathematics curriculum](index.md).
They explain each calculation used by the corresponding native C23 inference,
held-out evaluation and reproducibility components. There is no requirement
for university mathematics; verify each result with the worked practice.

- [Unit 55 — Logit rankings and the most likely token](55-logit-rankings-and-the-most-likely-token.md)
- [Unit 56 — Temperature and probability concentration](56-temperature-and-probability-concentration.md)
- [Unit 57 — Top-K versus top-p nucleus membership](57-topk-versus-topp-nucleus-membership.md)
- [Unit 58 — Left-padding and token position indices](58-left-padding-and-token-position-indices.md)
- [Unit 59 — Count full-context token-layer work](59-count-full-context-token-layer-work.md)
- [Unit 60 — Weighted selected-token loss and perplexity](60-weighted-selected-token-loss-and-perplexity.md)
- [Unit 61 — Hash ordered tokens independently of the CPU word size](61-hash-ordered-tokens-portably.md)
- [Unit 62 — Absolute loss thresholds versus accuracy thresholds](62-absolute-loss-thresholds-versus-accuracy.md)

## Earlier foundations

Revisit [probability, softmax and loss](05-probability-softmax-and-loss.md),
[attention and KV work](08-attention-and-kv-work.md),
[gradient descent](10-gradient-descent-and-learning-rate.md), and
[token-weighted cross-entropy](29-token-weighted-loss.md)
when an idea is unfamiliar. For complete C23 examples, use the
[native stacked inference lessons](../10-native-ai/stacked-inference-learning-path.md).
