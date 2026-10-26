# Mathematics for AI — Unit 37: Quality Thresholds and Honest Trade-offs

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Start with two measurements

Suppose a teaching model is evaluated on exactly the same ten held-out token targets, before and after adaptation. Its initial mean cross-entropy is 2.20 and its final mean is 2.05. Subtract to find the change:

`lossChange = after − before = 2.05 − 2.20 = −0.15`.

The negative sign indicates that the measured loss decreased. If we require a reduction of at least 0.10, this requirement passes because `2.20−2.05=0.15`.

## Accuracy is another requirement

Suppose the model correctly predicts six tokens before adaptation and five afterwards. Top-one accuracy changes from `6÷10=0.60` to `5÷10=0.50`. If the gate requires final accuracy at least 0.55, that requirement fails, **even though loss improved**.

Two metrics can move in different directions because probability calibration and exact top-token choices are not identical questions. A credible acceptance rule must state its independent thresholds before inspecting a candidate.

## Difference between a quality decision and an API error

The Framework returns `UMI_STATUS_OK` when it has validly compared two evaluations, even if the candidate fails one or more thresholds. In that case the report contains `accepted=0`. A malformed evaluation count or NaN threshold instead produces a status error and leaves the output unchanged.

This distinction is useful in other engineering areas. A correctly processed payment-risk check may refuse a transaction without the risk engine itself malfunctioning. Similarly, a valid fine-tuning quality check may reject a model.

## Compare like with like

Before and after evaluation must use the same held-out sample population and the same selected-target count. Otherwise simple differences can reflect changed test data rather than changed model quality. The digest of the approved ordered dataset is part of the supporting evidence.

## Practise

A model's loss improves from 1.30 to 1.10 and accuracy improves from 0.42 to 0.47. A policy requires loss reduction at least 0.15 and final accuracy at least 0.50. Which gate fails?

<details><summary>Show the decision</summary>

Loss reduction is `1.30−1.10=0.20`, which passes. Final accuracy `0.47` is below `0.50`, so acceptance fails. The two criteria must both pass.

</details>

**Continue:** [quality admission lesson](../10-native-ai/102-qualify-model-results-before-promotion.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
