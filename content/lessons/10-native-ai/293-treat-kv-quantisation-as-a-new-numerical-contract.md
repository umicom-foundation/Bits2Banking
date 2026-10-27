# Lesson 293 — Treat KV quantisation as a new numerical contract

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 172.

## Learning objective

Reducing stored precision saves bytes, but requires explicit rounding rules and end-to-end quality checks.

## Understand the mechanism

A compact K/V representation uses fewer bits per stored scalar. A simple symmetric int8 scheme computes a positive scale from the block's maximum absolute value and rounds each value to a signed integer. Dequantisation reconstructs only an approximation, so attention scores and final logits can change. Real methods differ by scale granularity, treatment of outliers, signed ranges and calibration.

Do not mix a quantised cache with the existing FP32 session and silently claim it is numerically identical. Choose a separate cache representation and identify its precision in the checkpoint/runtime contract. Measure memory and actual decode latency; smaller allocations can be offset by dequantisation overhead. For accuracy, use held-out loss/perplexity, full logits and task outcomes. Published KVQuant work illustrates why key/value distributions and outliers matter, but its GPU results are not transferable to the bounded native educational model.

## Fully worked example

For a scalar x = 0.4 and scale s = 0.01, the stored integer round(0.4/0.01) = 40; dequantisation gives 0.4. For x = 0.403, the same scale stores round(40.3) = 40 and reconstructs 0.4, with error −0.003. Some values incur larger errors near saturation.

## Native C23 laboratory

Make a 16-scalar K/V vector with known extremes. Evaluate FP32 bytes versus int8 payload plus scales, and compare the recovered dot products. Clearly label the quantised path as a new model-inference representation.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 172](../11-maths-for-ai/172-compare-mha-and-gqa-cache-capacity.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Does cutting a KV tensor from FP32 to int8 guarantee a fourfold reduction of runtime memory?

<details><summary>Reveal the worked answer</summary>

No. Tensor metadata, scale values, padding, alignment and other model allocations remain; dequantisation can also add temporary buffers.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](292-budget-multihead-versus-grouped-query-kv-memory.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
