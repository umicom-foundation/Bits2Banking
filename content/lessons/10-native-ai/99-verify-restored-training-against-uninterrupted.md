# Lesson 99 — Verify Restarted Training Against an Uninterrupted Run

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Build a meaningful regression plan, compare immutable frozen-model bytes, and inspect both exact training replay and held-out quality. Learn what equality does and does not prove.

## 1. Arrange two fair experiments

Create one approved dataset and one frozen native decoder. Make two initial adapters with exactly the same rank, projection-selection flags and initialization seed, or create one adapter snapshot and restore an exact twin. Both paths must start at the same adapter step, dataset SHA-256 and training plan.

**Path A:** train all approved examples and complete all epochs without restarting. **Path B:** train only one example, export one continuation snapshot, destroy that adapter, restore into a newly owned adapter, and train the remaining examples. Neither path is permitted to change the frozen decoder or reorder the source dataset.

## 2. Compare the correct objects

A high-confidence local restart regression compares the final portable adapter snapshots byte-for-byte. This includes every selected projection's trainable weight values, all role IDs, the exact frozen decoder identity and the committed adapter step. It also compares the final cursor and held-out aggregate metrics under the same build.

The test should separately encode the frozen decoder checkpoint **before** and **after** training; these bytes must remain unchanged. Since adapter training is meant to leave the original model untouched, a changed decoder checkpoint is a defect, not evidence that the adapter learned more.

## 3. Check one example of a held-out quality gate

Suppose the baseline held-out cross-entropy is 2.30 and the adapted model has 2.05, using the same 100 selected target tokens. The loss difference is `2.05−2.30 = −0.25`. If we require an improvement of at least 0.20, that criterion passes.

But if baseline top-one accuracy was 0.52 and adapted accuracy is 0.49, a separately required minimum accuracy of 0.50 **fails**. A responsible quality gate reports the complete decision rather than publishing the favourable loss figure alone.

The Framework's `UmiAiTrainingSupervisedQualityEvaluate` reports observed deltas and policy decisions. A quality acceptance is **not** a model release authorisation or a test of real-world language understanding.

## 4. Think about numerical comparisons

Two runs on one CPU with the same compiler and deterministic policy should reproduce precisely the same selected order and, subject to the established FP32 implementation, may produce byte-identical checkpoint outputs. That is the acceptance target of this local exercise.

Comparisons across different compilers or accelerators may need predeclared numerical tolerances. Never change the tolerance after seeing a failure simply to make the test pass. Record the machine, toolchain and model identity for any performance claim separately.

## Practice

**Question:** Why isn't a lower training loss enough? **Answer:** The model might memorise the training examples. The independent held-out evaluation measures different, source-isolated examples; both split integrity and the metric definition must be verified.

**Next:** [Run a real native demonstration](100-run-a-native-checkpoint-and-restart-demo.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
