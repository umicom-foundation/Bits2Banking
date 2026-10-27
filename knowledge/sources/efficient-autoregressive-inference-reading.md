# Research reading: efficient autoregressive inference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

The following open research papers provide the mathematical and architectural foundations for the lessons. Their experimental results apply to the systems studied by their authors and are not benchmarks of the Umicom Framework native training tape.

| Topic | Primary source | Contribution to the course |
|---|---|---|
| Online softmax | Milakov and Gimelshein (2018), [Online normalizer calculation for softmax](https://arxiv.org/abs/1805.02867) | Running maxima, stable normalisation and fewer memory accesses. |
| Multi-query attention | Shazeer (2019), [Fast Transformer Decoding: One Write-Head is All You Need](https://arxiv.org/abs/1911.02150) | Sharing keys and values across query heads. |
| Grouped-query attention | Ainslie et al. (2023), [GQA: Training Generalized Multi-Query Transformer Models from Multi-Head Checkpoints](https://aclanthology.org/2023.emnlp-main.298/) | Intermediate K/V head sharing and checkpoint uptraining. |
| Memory management | Kwon et al. (2023), [Efficient Memory Management for Large Language Model Serving with PagedAttention](https://arxiv.org/abs/2309.06180) | Logical-to-physical KV blocks and serving efficiency. |
| Rotary position embeddings | Su et al. (2021), [RoFormer: Enhanced Transformer with Rotary Position Embedding](https://arxiv.org/abs/2104.09864) | Rotation-based positional mathematics. |
| IO-aware attention | Dao et al. (2022), [FlashAttention: Fast and Memory-Efficient Exact Attention with IO-Awareness](https://arxiv.org/abs/2205.14135) | Attention tiling and avoiding expensive intermediate transfers. |
| Speculative decoding | Leviathan, Kalman and Matias (2023), [Fast Inference from Transformers via Speculative Decoding](https://proceedings.mlr.press/v202/leviathan23a.html) | Verifying draft tokens while preserving target-model output distribution under the specified algorithm. |

## Reading questions

1. Which proposals alter the model's parameterisation, and which change only the execution strategy for a given model?
2. Which techniques improve memory capacity, which reduce memory traffic, and which may reduce sequential target-model forward passes?
3. Which results require full checkpoint-level or whole-session numerical qualification before being used with another model?

## Numerical and compatibility boundaries

The accompanying Framework kernel is a standalone FP32 forward-only computation using the current educational multi-head layout. It does not implement GQA, MQA, RoPE, paged KV storage, cache quantisation or speculative sampling. Such techniques require model and deployment contracts beyond a change to one attention function.

*Service to Many Leads to Greatness.*
