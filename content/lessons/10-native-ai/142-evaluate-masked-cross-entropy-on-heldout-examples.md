# Lesson 142 — Evaluate masked cross-entropy on held-out examples

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Combine read-only losses by supervised target count rather than by document count.

## 1. Understand the engineering problem

Training examples can contain different numbers of assistant-response tokens. If their loss masks select different numbers of targets, averaging one mean loss per example gives the wrong aggregate. The desired quantity is mean cross-entropy per *selected* token. The stacked decoder already provides selected-token evaluation through the training tape, so the new evaluator reuses that owner rather than implementing a competing softmax.

## 2. Follow a concrete example

Example A supervises one target and has mean loss 0.2. Example B supervises three targets and has mean loss 0.8. The correct combined average is `(1 × 0.2 + 3 × 0.8) / (1 + 3) = 2.6 / 4 = 0.65`. Simply averaging `(0.2+0.8)/2 = 0.5` falsely treats the one-token example as equally influential as the three-token example. Both examples must use the same model, and each must be held out from training.

## 3. Implement through the Framework

`UmiAiTrainingStackedEvaluationRun` accepts a bounded collection of `UmiAiTrainingStackedEvaluationCase` values. Each case contains token IDs, targets, a binary loss mask, the fixed context length and a caller-supplied original-source digest. The service validates mask values and only requires target IDs at selected positions to be valid. It calls `UmiAiTrainingStackedDecoderEvaluateSelected` for each example and calculates the weighted aggregate in double precision.

## 4. Check the boundaries

This service cannot determine whether a dataset was legally obtained, accurately transcribed, properly redacted or genuinely unseen during training. Use existing source-admission and reviewed-corpus controls before constructing evaluation windows. The SHA-256 returned for the ordered cases identifies supplied bytes but is not a licence certificate or signature.

## Practice

**Question:** If two examples select two and six tokens respectively, which example contributes more to token-weighted mean loss?

<details>
<summary>Reveal the worked answer</summary>

The six-target example contributes three times as much weight as the two-target example. Each target counts once; the document count does not determine the denominator.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
