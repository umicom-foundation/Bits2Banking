# Lesson 146 — Produce reproducible generation evidence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Bind output IDs to the exact checkpoint, prompt, sampler policy and seed.

## 1. Understand the engineering problem

A transcript without model identity is difficult to reproduce. Even identical text may have been generated using different weights or prompt positions. The native Framework's stacked evidence API makes reproducibility an explicit test: it receives claimed output token IDs, regenerates them using the canonical session, compares every ID, and only then publishes aggregate identifiers.

## 2. Follow a concrete example

Consider a prompt with two IDs and a run of six generated IDs. The evidence record contains the prompt-token count, output-token count, sampler temperature, top-K/top-p, initial RNG seed and model checkpoint identity. It also contains independent SHA-256 digests for ordered prompt IDs, ordered output IDs and the sampling declaration. Token IDs are encoded as fixed-width little-endian numbers before hashing so the identity does not depend on whether a host uses 32-bit or 64-bit `size_t`. The record contains no raw prompt text.

## 3. Implement through the Framework

`UmiAiTrainingStackedGenerationEvidenceBuild` recomputes the entire output. If even one claimed token differs from the regenerated token, the call returns an invalid-state result without publishing a report. `...EvidenceVerify` repeats the check using the stored policy and seed and compares the digests and model work fields. These APIs never compile, execute or trust generated code; they do not write files or contact an external model.

## 4. Check the boundaries

Unkeyed hashes are not digital signatures. A malicious party who can replace a checkpoint, output and evidence can compute matching new digests. Reproducibility does not establish ethical training-data sourcing, copyright permission, model safety or organisational approval. Those claims require other evidence and controls.

## Practice

**Question:** If a replay generates five matching IDs and a different sixth ID, should evidence for all six be published?

<details>
<summary>Reveal the worked answer</summary>

No. The record covers the complete declared stream; one mismatched token makes the claimed result invalid. A partial sequence cannot be mislabelled as a successful exact replay.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
