# Lesson 143 — Calculate top-one accuracy on selected targets

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Score exact next-token predictions using the same verified logits as evaluation loss.

## 1. Understand the engineering problem

Cross-entropy considers how much probability the model assigns to the correct target. Top-one accuracy asks a different question: for each supervised position, does the single highest-scoring vocabulary ID equal the target ID? It is possible to have a better cross-entropy without changing the top prediction, or to change top-one accuracy while the average loss changes only slightly.

## 2. Follow a concrete example

Suppose the loss mask for a four-position sequence is `[0,1,1,0]`. Only positions 1 and 2 count. At position 1, the model's highest logit belongs to ID 45 and the target is 45: one match. At position 2, the model favours ID 80 while the target is 81: a miss. The top-one accuracy is `1 / 2 = 0.5`, or 50%. The ignored positions contribute neither matches nor misses, even if their unmasked logits are confidently wrong.

## 3. Implement through the Framework

The evaluator calls the established `UmiAiTrainingStackedDecoderLogits` and scans the vocabulary only for selected rows. Equal logits break ties toward the lower ID, consistent with the model's greedy convention. A non-finite inspected logit is an invalid numerical state rather than a guess. The report includes selected target count, match count and the resulting fraction. It does not sample random tokens to measure top-one predictions.

## 4. Check the boundaries

The complete training loss can include EOS as a supervised target, even though the generation sampler excludes the four reserved IDs. Keep these two policies distinct. A high top-one score on a tiny reviewed dataset does not demonstrate that the model writes correct source code, answers customer questions reliably or follows security boundaries.

## Practice

**Question:** What accuracy results from three exact predictions among five selected targets?

<details>
<summary>Reveal the worked answer</summary>

The fraction is `3 / 5 = 0.6`, or 60%. Ignored rows are not added to the denominator.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
