# Numerical qualification and incremental inference — source guide

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Primary implementation references

- Umicom Framework, `include/umicom/ai/training/stacked_decoder.h`: authoritative bounded stacked-decoder contract.
- Umicom Framework, `include/umicom/ai/training/stacked_projection_trace.h`: observes canonical per-layer K/V projections and logits.
- Umicom Framework, `include/umicom/ai/training/stacked_kv_step.h`: new-token incremental proposals and workload counters.
- Umicom Framework, `include/umicom/ai/training/stacked_kv_store.h`: shape-checked, checkpoint-bound cache ownership and full replacement at absolute-position rollover.
- Umicom Framework, `include/umicom/ai/training/inference_parity.h`: finite FP32 vector comparisons.
- Umicom Framework, `include/umicom/ai/training/stacked_inference_qualification.h`: complete reference/step/cache diagnostic composition.

## Foundational research

- Vaswani et al. (2017), *Attention Is All You Need*, arXiv:1706.03762. Describes the Transformer attention mechanism and scaled dot-product calculations.
- Dao et al. (2022), *FlashAttention: Fast and Memory-Efficient Exact Attention with IO-Awareness*, arXiv:2205.14135. Discusses memory-traffic-aware attention optimisation; the bounded educational CPU kernel is not FlashAttention.
- Ainslie et al. (2023), *GQA: Training Generalized Multi-Query Transformer Models from Multi-Head Checkpoints*, arXiv:2305.13245. Explains an alternative KV-head layout; the stacked educational model uses its existing head layout.

## Reading order

Study the canonical decoder, projection trace, KV store and incremental-proposal contracts before using the qualification API. Then reproduce the element counts in Mathematics Units 173–184. Treat rights to train on an outside document as a separate question from the right to cite published research.
