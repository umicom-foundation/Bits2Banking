# Research sources: query attention and cache validity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

This bibliography accompanies the native decoder integration course. Published research describes algorithms and measurement methods, but it does not establish performance or correctness of any particular Umicom build.

| Topic | Research source | Course use |
|---|---|---|
| Transformer attention | Vaswani et al., [Attention Is All You Need](https://arxiv.org/abs/1706.03762), 2017 | Multi-head scaled dot-product attention and layer composition. |
| Stable softmax | Milakov and Gimelshein, [Online Normalizer Calculation for Softmax](https://arxiv.org/abs/1805.02867), 2018 | Numerically stable normalisation and possible streaming approaches. |
| KV head sharing | Shazeer, [Fast Transformer Decoding: One Write-Head is All You Need](https://arxiv.org/abs/1911.02150), 2019 | Multi-query attention as a distinct head topology. |
| Grouped-query attention | Ainslie et al., [GQA: Training Generalized Multi-Query Transformer Models from Multi-Head Checkpoints](https://aclanthology.org/2023.emnlp-main.298/), 2023 | Explicit head mapping and checkpoint conversion. |
| IO-aware attention | Dao et al., [FlashAttention](https://arxiv.org/abs/2205.14135), 2022 | Memory traffic, tiling and meaningful performance boundaries. |
| KV paging | Kwon et al., [Efficient Memory Management for Large Language Model Serving with PagedAttention](https://arxiv.org/abs/2309.06180), 2023 | Logical versus physical KV block management. |

## Technical interpretation

A small educational decoder with learnt absolute positions needs canonical cache rebuilding when an eviction changes surviving token indices and hidden states. The current native one-query arithmetic must be qualified against the actual decoder before extending model architecture. The head-sharing papers describe different parameterisations, not automatic flags for pre-existing multi-head checkpoints.

## Reading exercises

1. Explain the difference between computing one attention query and changing the number of stored K/V heads.
2. Identify the exact memory and timing boundary measured by each research result.
3. Describe why a projection cache belongs to a particular source checkpoint, input prefix and positional semantics.
