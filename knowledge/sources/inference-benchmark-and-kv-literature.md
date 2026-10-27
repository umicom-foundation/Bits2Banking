# Research Readings — Inference Benchmarking and KV-Cache Engineering

**Bits to Banking · Umicom Foundation**  
**Curated by:** Sammy Hegab  
**Course connections:** LLM Lessons 281–296 and Mathematics Units 161–172.

The following independent papers and documentation describe established inference concepts. A paper's reported results belong to its stated model, workload and hardware; they do not demonstrate that Umicom's bounded C23 educational decoder has attained the same properties.

| Source | Technical value | Further reading |
|---|---|---|
| Dao et al., FlashAttention (2022) | Illustrates why reducing external-memory traffic, not only multiplication counts, matters. | https://arxiv.org/abs/2205.14135 |
| Ainslie et al., GQA (2023) | Defines grouped-query attention and the role of fewer K/V heads. | https://arxiv.org/abs/2305.13245 |
| Kwon et al., PagedAttention/vLLM (2023) | Explains paged K/V ownership and serving throughput. | https://arxiv.org/abs/2309.06180 |
| Hooper et al., KVQuant (2024) | Studies low-precision K/V representations and outliers. | https://arxiv.org/abs/2401.18079 |
| vLLM documentation | Documents production implementations of batching, prefix caching and KV memory management. | https://docs.vllm.ai/en/latest/ |
| Benchmarking Terminology for LLM Serving (Internet-Draft, 2026) | Clarifies TTFT, inter-token latency and TPOT definitions. The draft is work in progress, not an adopted standard. | https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/ |
| Benchmarking Methodology for LLM Serving (Internet-Draft, 2026) | Proposes reporting conventions and workload measurement methodology; remains a draft. | https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-methodology/ |
| TokenPowerBench (2025) | Studies phase-aligned energy measurements for model inference. | https://arxiv.org/abs/2512.03024 |

## Concepts linked by the reading

The memory-capacity equation for a dense K/V cache is `2 × layers × tokens × K/V heads × channels per head × bytes per scalar`. Page allocation, quantisation and shared prefixes change the physical representation and should be measured independently. A lower projection count alone does not imply lower elapsed latency or energy usage.

## Source ethics

A publicly readable research page is a reference for study, not automatically authorised input for model training. Training permission, dataset licences and original-source provenance require their own documented assessment.
