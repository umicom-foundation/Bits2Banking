# Lesson 138 — Pin stacked checkpoint identity before inference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Distinguish model-content integrity from publisher authentication.

## 1. Understand the engineering problem

A decoder may keep the same configuration after its weights have changed. For instance, two models can each have vocabulary 260, context four and two layers, but different trained parameters. Checking dimensions alone does not identify a model. The Framework's stacked checkpoint encoder already supplies a canonical portable byte representation, which provides a suitable input for exact content identity.

## 2. Follow a concrete example

Imagine opening an assistant session and then training the borrowed model before requesting its next token. Its step count and checkpoint bytes can change. The session's original prompt, seed and sampling policy would now refer to a different numerical function. The new identity component captures model configuration, completed training steps, checkpoint length and SHA-256 of the actual encoded bytes. `Verify` repeats that capture and refuses stale sessions. This is more precise than comparing a pointer or model name.

## 3. Implement through the Framework

`UmiAiTrainingStackedModelIdentityCapture` and `...Verify` are Framework-owned APIs. The generation session uses them at creation, before sampling and before publishing a result. The model remains borrowed; the session does not copy the model's entire weights for separate inference. Every failed identity check leaves the caller's token/output record untouched. In particular, a model with the same tensor shapes but a different training seed does not silently pass.

## 4. Check the boundaries

SHA-256 is an unkeyed content digest. Anyone who controls both a model and its claimed digest can make them match. Authenticating a publisher, approving usage rights and validating signed release evidence remain distinct Framework security duties. Do not present an identity match as a trusted financial-model deployment decision.

## Practice

**Question:** If two checkpoints have the same layer count and vocabulary size, must they have the same SHA-256?

<details>
<summary>Reveal the worked answer</summary>

No. The digest covers exact encoded checkpoint bytes, including weight values and training state. Equal shapes are compatible dimensions, not identical model contents.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
