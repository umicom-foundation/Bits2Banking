# Lesson 136 — Stream tokens without a multi-layer KV cache

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Implement incremental user-visible delivery without claiming faster arithmetic.

## 1. Understand the engineering problem

Streaming describes *when the caller receives output*: one token at a time rather than after a whole response. It is not the same as incremental attention computation. The stacked decoder currently has a correct canonical full-context path, while multi-layer cache equivalence after eviction remains unproved. The new session therefore provides a real streaming interface while still recomputing all layers for each token.

## 2. Follow a concrete example

Suppose a model has context four, two layers and the user requests six output tokens. The session performs six complete inference calls. The logical work counters are `4 × 6 = 24` full-context token rows and `24 × 2 = 48` Transformer token-layer rows. These numbers come from the model shape and successful pull count. They do not include matrix dimensions, softmax work, allocation overhead, clock time or operating-system scheduling. A GUI may still feel more responsive because the first token arrives before the sixth.

## 3. Implement through the Framework

A caller initialises a session pointer to `NULL`, invokes `UmiAiTrainingStackedGenerationSessionCreate`, repeatedly calls `UmiAiTrainingStackedGenerationSessionNext`, and finally destroys the session. Successful pulls increment its output counter and roll the retained context. An invalid call does not advance the random generator or replace the caller's token variable. `Inspect` reports the genuine count of successful pulls, alongside calculated work units and pinned checkpoint identity.

## 4. Check the boundaries

Destroying the session is an explicit cancellation operation. It frees its own context and RNG state without destroying the borrowed decoder. No background worker or automatic restart is introduced. A real application must serialise decoder calls and must keep the decoder alive until the session is destroyed. This educational API emits at most 64 tokens; longer tasks need separately designed resource and lifetime policies.

## Practice

**Question:** A six-token run reports 48 layer-token rows. Does this establish 48 floating-point operations or a particular latency?

<details>
<summary>Reveal the worked answer</summary>

No. A token-layer row stands for processing one token through one Transformer block. Each block may perform many matrix and attention operations; timings must be measured separately.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
