# Restore and continue deterministic SGD

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Continuation means the same parameters, not another initial seed

Suppose a two-layer model completes five updates before its application closes. To continue from update six, save a complete stacked checkpoint after the fifth update. Restoring should recreate the same parameter values and completed-step counter, not recreate the initial model from its seed.

The Framework exposes `UmiAiTrainingStackedCheckpointInspect` and `UmiAiTrainingStackedCheckpointDecode`. The decoder validates the exact record length, schema, tensor shapes, finite FP32 values and SHA-256 before publishing a newly owned model. The restored model uses the *same existing* tape and Transformer mathematics as a freshly constructed stack.

## Prove continuation with two paths

Train one model for five steps and save a snapshot. Decode it into an independent second model. Now perform eight more updates on both models, presenting the same token windows in the same order with the same learning rate. Compare all vocabulary logits and the new checkpoint bytes. Under the same build, the expected result is identical for this deterministic stateless-SGD path.

A mismatch is actionable. Investigate changed dataset order, missing tensors, an incorrect completed-step field, uninitialised state or floating-point environment differences. Do not widen tolerances to hide a structural error.

## Important recovery boundary

This example proves **model-weight** continuation in one configuration. Reproducing a complete experiment interrupted mid-epoch additionally needs its dataset identity, shuffle seed, current epoch and next record index. Recovering AdamW requires its first and second moments. No checkpoint should be marked as production-ready without both integrity and independent approval.

## Practice

Model A trains for five steps, is snapshotted, and then takes eight more. What completed-step count should a restored model show after the same eight steps?

<details><summary>Worked answer</summary>

Thirteen updates. The snapshot must preserve five completed steps and the resumed model advances exactly eight more, without counting the restore operation itself as training.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
