# Lesson 141 — Count inference work without inventing speedups

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Separate logical token-layer work from elapsed time and memory traffic.

## 1. Understand the engineering problem

When discussing performance, engineers often use different denominators without noticing. Token count, token-layer rows, matrix multiply–accumulates, process CPU time, wall-clock duration and peak memory are different quantities. The new stacked session exposes an intentionally narrow workload counter: the number of full-context token rows requested and the same number multiplied by Transformer layer count.

## 2. Follow a concrete example

With context length eight, three layers and ten generated tokens, the session requests `8 × 10 = 80` complete-context token rows. It also requests `80 × 3 = 240` layer-token rows. This says nothing directly about the work of attention softmax, the `C×C` projections, per-layer feed-forward widths, or token-embedding lookup. A model with twice as many channels can do much more arithmetic while keeping the same row counters.

## 3. Implement through the Framework

`UmiAiTrainingStackedGenerationSessionInspect` derives counts from the model configuration and successful calls. They are deterministic and suitable for checking whether a session performed the expected amount of work. They are **not** measurements of CPU instructions or seconds. For genuine comparisons, use a qualified benchmark with equal model, prompt, compiler settings, sampling seed and workload, then record warm-up, repetitions and variability separately.

## 4. Check the boundaries

Multi-layer KV caching is especially delicate. A retained upper-layer key may depend on hidden states that already incorporated evicted tokens. RoPE alone does not guarantee a new rolling-window reference would compute the same value. Never advertise throughput gains from a proposed cache until numerical invariants and timings have both been demonstrated.

## Practice

**Question:** A context-four, layer-five model emits seven tokens. How many token-layer rows are requested?

<details>
<summary>Reveal the worked answer</summary>

It requests `4 × 7 × 5 = 140` token-layer rows. That is distinct from the 28 full-context rows and is not an elapsed-time measurement.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
