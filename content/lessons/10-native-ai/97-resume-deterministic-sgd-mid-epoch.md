# Lesson 97 — Resume Deterministic SGD in the Middle of an Epoch

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning objectives

Understand seeded permutations, global example indices, a committed training step and the difference between a cursor value and updated model weights. Learn why both must be checkpointed as one logical unit.

## 1. Work through a small training schedule

Imagine four **approved training examples** with global indices `[0,2,4,6]`. Our deterministic dataset service chooses one permutation for each epoch. The first epoch might visit `[4,0,6,2]`; the next may be different because the epoch number is part of the seed. The exact order belongs to the Framework dataset service, not to a home-grown shuffle in Umicom Studio.

Suppose a run finishes the first two examples in epoch zero. Its cursor is `(completedEpochs=0, nextExampleOffset=2)`. The next training call must retrieve the **third entry** from the same epoch's deterministic permutation. Starting a new shuffle or skipping to another epoch would be a different training run.

## 2. Confirm the step-count equation

Let `T` be the number of training examples in each epoch, `E` the completed whole epochs, `O` the next-example offset and `S0` the adapter's step count when this run started. Then:

`expectedCurrentAdapterSteps = S0 + E×T + O`

For `S0=5`, `T=4`, `E=2`, `O=3`, we expect `5 + 2×4 + 3 = 16` completed adapter steps. This equation is a simple but valuable corruption check. It catches impossible combinations of counter and cursor before another weight update.

## 3. One update is a precise commit boundary

`UmiAiTrainingSupervisedContinuationTrainNext` uses the existing Framework dataset order, fetches one owned supervised window and delegates the numerical update to `UmiAiTrainingDecoderProjectionAdapterTrainStep`. Only when this succeeds does it advance the cursor. Previous successful SGD steps are **not rolled back** if a later call fails.

Once all examples in an epoch are consumed, `TrainNext` refuses another step until `...FinishEpoch` performs scheduled held-out evaluation and begins the next epoch. This separate transition prevents accidentally double-training the last example when an evaluation fails.

## 4. Why the model and cursor must travel together

Suppose an old adapter snapshot contains the weights after 10 updates but its cursor says 11. If restored together without validation, the next step will skip one example. Reversing that mismatch repeats an example. The Framework continuation snapshot combines the current adapter weights and cursor into one bounded, integrity-checked record, and restore checks their step counts agree.

This is exact continuation **only for this stateless SGD policy**, using the same approved frozen decoder, same reviewed dataset and same compiler/numerical behaviour expectations. It is not a guarantee of bit-identical results on every CPU implementation.

## Practice

A run begins at step 20, has 3 training examples per epoch and has completed 2 full epochs plus 1 example. Its expected step count is `20 + 2×3 + 1 = 27`. If the checkpoint says 28, stop and investigate rather than silently adjusting the cursor.

Continue to [failure handling](98-handle-training-failures-and-incomplete-epochs.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
