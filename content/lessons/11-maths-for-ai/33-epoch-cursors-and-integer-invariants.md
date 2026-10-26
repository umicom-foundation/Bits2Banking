# Mathematics for AI — Unit 33: Epoch Cursors and Integer Invariants

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Start with familiar counting

A teacher has three exercises and asks a learner to complete each one once. After all three are complete, the learner starts another round, or **epoch**. A computer trainer applies the same idea to approved examples. An epoch is one complete visit of the training examples, usually in a deterministically selected order.

## Name the quantities

Let `T` be the number of eligible training examples, `E` the number of fully completed epochs, `O` the number of examples already trained in the current epoch, and `S0` the adapter's step count before the run started.

**Expected step identity:** `S = S0 + (E × T) + O`.

Every symbol has a purpose. `S` is the completed adapter step count now. Multiplying `E×T` accounts for all examples in finished epochs. Adding `O` accounts for the partly completed current epoch.

Suppose we start with `S0=7`, train `T=4` examples per epoch, finish `E=2` epochs and consume `O=1` more example. Then `S=7+2×4+1=16`. An imported snapshot claiming 17 steps while still naming offset one is inconsistent.

## Boundaries matter

The cursor obeys `0 ≤ O ≤ T` while an epoch is in progress. If `O=T`, the trainer must complete the epoch's held-out evaluation before beginning the next one; otherwise the same final training example could be repeated. If the run has already completed all configured epochs, no further training step is valid.

Unsigned integer overflow also matters. A 64-bit step counter cannot wrap around silently and pretend a new run has begun. Before adding `E×T+O`, check multiplication and addition against the integer's maximum representable value.

## Apply the mathematics to C23

The Framework's continuation service validates the cursor and model step count **before** selecting the next example. It delegates example ordering to `UmiAiTrainingSupervisedDatasetOrder`, avoiding any second random-number or shuffle implementation.

## Practise

A run begins at step 12, uses 5 examples per epoch, has completed 3 epochs and is 2 examples into the next one. Calculate `S`.

<details><summary>Show the worked answer</summary>

`S = 12 + 3×5 + 2 = 29`. The next update should be counted as step 30 after it succeeds, not before.

</details>

**Continue:** [native restart lesson](../10-native-ai/97-resume-deterministic-sgd-mid-epoch.md).

---

*Service to Many Leads to Greatness. Educational C23 examples; not a production financial or model-training certification.*
