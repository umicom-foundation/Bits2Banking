# Lesson 145 — Compare candidate and reference models fairly

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Separate numerical acceptance criteria from actual release authorisation.

## 1. Understand the engineering problem

A fine-tuned candidate should be compared with its reference model using exactly the same held-out cases and context rules. Comparing different prompt lengths, tokenisations, source partitions or model shapes can manufacture an apparent improvement. The new Framework selection service evaluates both stacked models using the same evaluator and verifies that their declared decoder dimensions are compatible.

## 2. Follow a concrete example

Suppose reference loss is 0.80 and candidate loss is 0.83. If the policy allows an absolute loss increase of at most 0.02, the candidate fails the loss condition because `0.83 − 0.80 = 0.03`. If the candidate has top-one accuracy 0.62 and the policy requires at least 0.60, its accuracy condition passes. Overall admission still fails because **both** conditions must pass. This is an evaluation result, not a software error.

## 3. Implement through the Framework

`UmiAiTrainingStackedModelSelectionCompare` accepts a reference model, candidate model, one held-out case array and an explicit policy. It checks matching shape, runs read-only evaluation for both and returns separate `lossAccepted`, `accuracyAccepted` and `candidateAccepted` fields. Invalid policies—such as negative loss tolerance or accuracy greater than one—are rejected without overwriting the caller's report. A failed numerical threshold returns status OK with `candidateAccepted=0`.

## 4. Check the boundaries

The service is deliberately **not** an autonomous deployment gate. It does not approve a signing key, grant model execution permissions or decide whether the model may place trades or payments. Framework security and explicit human review remain separate. Use independent quality criteria for generated code, model hallucinations, privacy and appropriate domain behaviour.

## Practice

**Question:** When accuracy passes but maximum allowed loss regression fails, should the candidate be accepted?

<details>
<summary>Reveal the worked answer</summary>

No. The comparison requires both threshold conditions to pass. A valid rejected candidate is represented with `candidateAccepted=0` and a successful API status.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
