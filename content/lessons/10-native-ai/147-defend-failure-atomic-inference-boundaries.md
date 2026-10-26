# Lesson 147 — Defend inference boundaries with failure-atomic APIs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Keep caller buffers and model state unchanged after invalid requests.

## 1. Understand the engineering problem

A robust native library must refuse malformed requests without leaving half-written outputs or advancing generation state. That property is called failure atomicity. It matters in AI systems just as it matters in banking software: incomplete data must never masquerade as a complete and approved result. An unsafe code path can appear to work in happy-path demonstrations while failing when capacities or identities change.

## 2. Follow a concrete example

Imagine a caller requests three tokens but supplies capacity for only two. `UmiAiTrainingStackedGenerateNucleus` must reject the request before writing the token array, output count or optional statistics. If a prompt includes token 999 while the vocabulary has only 260 entries, Create must refuse the entire prompt—even if the offending token would have fallen outside the retained four-position context. If a borrowed model has been trained since a session started, later pulls must refuse its stale checkpoint identity.

## 3. Implement through the Framework

The tests cover invalid top-p values, invalid output count, null pointers, insufficient capacity, malformed loss masks, missing supervised targets, wrong model shape, changed checkpoint digests and stale sessions. Separate execution tests check reproducibility. The Framework's model and arrays remain caller-owned according to their documented lifetime contracts, while sessions and temporary logits are owned by the relevant Framework services.

## 4. Check the boundaries

Passing these tests is not a guarantee that C23 code contains no memory defect. Repeat under native Windows UCRT64 and compatible Linux builds; use AddressSanitizer and UndefinedBehaviourSanitizer where appropriate. The isolated contract tests from a teaching environment cannot replace numerical tests linked against the actual Umicom training tape and Transformer implementation.

## Practice

**Question:** Why must a capacity failure leave the requested token count unchanged?

<details>
<summary>Reveal the worked answer</summary>

The count is part of the published result. Changing it after a failed request could make downstream code believe a complete sequence was generated or expose uninitialised output values.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
